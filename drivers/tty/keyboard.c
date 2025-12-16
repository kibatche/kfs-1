#include <tty.h>
#include <stdio.h>
#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

/**
 * Keyboard mappings.
 */
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

void handle_special_keys(unsigned char scancode)
{
    switch (scancode)
    {
    case ARROW_UP:
        move_cursor(0, -1);
        break;
    case ARROW_DOWN:
        move_cursor(0, 1);
        break;
    case ARROW_LEFT:
        move_cursor(-1, 0);
        break;
    case ARROW_RIGHT:
        move_cursor(1, 0);
        break;
    default:
        return;
    }
}

/**
 * Handle pressed keys (display character or move cursor).
 */
void handle_key(void)
{
    const unsigned char status_flags = inb(PS2_STATUS_REGISTER);
    const unsigned char input_buffer_status = status_flags & PS2_INPUT_STATUS_OFFSET;
    const bool buffer_is_full = (input_buffer_status == 1);

    if (buffer_is_full)
    {
        unsigned char scancode = inb(PS2_IO_PORT_DATA);

        if (scancode == KEY_ESCAPE_SEQ)
        {
            scancode = inb(PS2_IO_PORT_DATA);
            handle_special_keys(scancode);
        }
        else
        {
            const char key = kbdus[scancode];

            if (key)
                terminal_putchar(key);
        }
    }
}
