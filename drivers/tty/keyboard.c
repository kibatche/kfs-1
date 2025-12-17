#include <tty.h>
#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

/* Keyboard mappings. */
const char kbdus[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9',
    '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};
const char kbdus_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
    '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9',
    '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};
const char kbdus_caps[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']',
    '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
    0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9',
    '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

/* Pressed keys. */
bool capslock_on = false;
bool shift_on = false;

static void handle_extended_key(unsigned char scancode, const bool is_pressed)
{
    (void)is_pressed;
    switch (scancode)
    {
    case SCANCODE_ARROW_UP:
        move_cursor(0, -1);
        break;
    case SCANCODE_ARROW_DOWN:
        move_cursor(0, 1);
        break;
    case SCANCODE_ARROW_LEFT:
        move_cursor(-1, 0);
        break;
    case SCANCODE_ARROW_RIGHT:
        move_cursor(1, 0);
        break;
    default:
        return;
    }
}

/**
* Handle key (store caps lock state, display character or move cursor).
*/
static void handle_key(unsigned char scancode, const bool is_pressed, const bool is_extended_key)
{
    if (scancode == SCANCODE_BACKSPACE)
    {
        // TODO
        ;
    }
    else if (scancode == SCANCODE_CAPSLOCK)
    {
        capslock_on = !(capslock_on && is_pressed);
    }
    else if (
        (scancode == SCANCODE_LSHIFT) || (scancode == SCANCODE_RSHIFT) \
        || ((scancode ^ KEY_PRESSED_MASK) == SCANCODE_LSHIFT) || ((scancode ^ KEY_PRESSED_MASK) == SCANCODE_RSHIFT)
    )
    {
        shift_on = is_pressed;
    }
    else if (is_pressed)
    {
        if (is_extended_key)
        {
            handle_extended_key(scancode, is_pressed);
        }
        else if ((scancode == SCANCODE_F1) || (scancode == SCANCODE_F2))
        {
            // TODO
            ;
        }
        else
        {
            char key;

            if (capslock_on && !shift_on)
                key = kbdus_caps[scancode];
            else if (shift_on && !capslock_on)
                key = kbdus_shift[scancode];
            else
                key = kbdus[scancode];

            if (key)
                terminal_putchar(key);
        }
    }
}

/**
* Handle incoming scancodes.
*/
void process_scancodes(void)
{
    const unsigned char status_flags = inb(PS2_STATUS_REGISTER);
    const unsigned char input_buffer_status = status_flags & PS2_INPUT_STATUS_OFFSET;
    const bool buffer_is_full = (input_buffer_status == 1);

    if (buffer_is_full)
    {
        unsigned char scancode = inb(PS2_IO_PORT_DATA);
        const bool is_extended_key = (scancode == KEY_ESCAPE_SEQ);

        if (is_extended_key)
            scancode = inb(PS2_IO_PORT_DATA);

        const bool is_pressed = ((scancode & KEY_PRESSED_MASK) == 0);
        handle_key(scancode, is_pressed, is_extended_key);
    }
}
