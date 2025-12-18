#include <tty.h>
#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

/**
 * Global structs that contain information about terminals
 * Number of the active terminal
**/
tty terminals[MAX_TERM];
size_t active_term = 0;

/**
 * @brief Do the inb op on a given port
 * 
 * @param port 
 * @return unsigned char 
 */
unsigned char inb(unsigned short port)
{
    unsigned char result;

    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return (result);
}

/**
 * @brief Do the out op on a given port with the value data
 * 
 * @param port 
 * @return unsigned char 
 */
void outb(unsigned char data, unsigned short port)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

/**
 * @brief Update the cursor by adding x and/or y to its position
 * 
 * @param x 
 * @param y 
 */
static void update_cursor(int x, int y)
{
    uint16_t pos = x + (y * VGA_WIDTH);

    outb(0x0F, VGA_PORT_INDEX);
    outb((uint8_t) (pos & 0xFF), VGA_PORT_DATA);
    outb(0x0E, VGA_PORT_INDEX);
    outb((uint8_t) ((pos >> 8) & 0xFF), VGA_PORT_DATA);
}

/**
 * @brief Update the terminal when scrolling
 * 
 */
static void terminal_update()
{
    for (size_t row = 0; row < VGA_HEIGHT - 1; row++)
    {
        memcpy(&terminals[active_term].terminal_buff[row * VGA_WIDTH], \
            &terminals[active_term].terminal_buff[(row + 1) * VGA_WIDTH], \
            VGA_WIDTH * sizeof(uint16_t));
    }

    for (size_t i = 0; i < VGA_WIDTH; i++)
    {
        terminals[active_term].terminal_buff[((VGA_HEIGHT - 1) * VGA_WIDTH) + i] = vga_entry(' ', terminals[active_term].terminal_color);
    }
}

/**
 * @brief put a char c in the VGA_MEMORY
 * 
 * @param c 
 * @return int 
 */
int terminal_putchar(char c)
{
    const bool is_newline = (c == '\n');

    if (is_newline)
    {
        terminals[active_term].col_pos = 0;
        move_cursor(0, 1);
        return (0);
    }
    const size_t idx = terminals[active_term].col_pos + (terminals[active_term].row_pos * VGA_WIDTH);
    terminals[active_term].terminal_buff[idx] = vga_entry(c, terminals[active_term].terminal_color);
    move_cursor(1, 0);
    return (1);
}

/**
 * @brief Set blank space on the terminal
 * 
 * @param term 
 */
static void terminal_set_blank_spaces(tty *term)
{
    for (int i = 0; i < VGA_WIDTH; i++)
    {
        for (int j = 0; j < VGA_HEIGHT; j++)
        {
            term->terminal_buff[i + (j * VGA_WIDTH)] = vga_entry(' ', term->terminal_color);
            term->saved_term_content[i + (j * VGA_WIDTH)] = vga_entry(' ', term->terminal_color);
        }
    }
}

/**
 * @brief Save the content of the active terminal before switching to another one
 * 
 */
static void terminal_save_content()
{
    for (size_t i  = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
    {
        terminals[active_term].saved_term_content[i] = terminals[active_term].terminal_buff[i];
    }
}

/**
 * @brief Put the saved content from a terminal to the VGA video memory
 * after switching
 *
 */
static void terminal_put_saved_content()
{
    for (size_t i  = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
    {
        terminals[active_term].terminal_buff[i] = terminals[active_term].saved_term_content[i];
    }
}

/**
 * @brief Switch to terminal number term_number + 1
 * 
 * @param term_number 
 */
void terminal_switch(size_t term_number)
{
    if (term_number != active_term && term_number + 1 <= MAX_TERM)
    {
        terminal_save_content();
        active_term = term_number;
        terminal_put_saved_content();
        update_cursor(terminals[active_term].col_pos, terminals[active_term].row_pos);
    }
}

/**
 * @brief Move the cursor to a given offset x and y
 * 
 * @param offset_x 
 * @param offset_y 
 */
void move_cursor(int offset_x, int offset_y)
{
    int new_col_pos = terminals[active_term].col_pos + offset_x;
    int new_row_pos = terminals[active_term].row_pos + offset_y;

    if (new_col_pos < 0)
    {
        --new_row_pos;
        terminals[active_term].col_pos = VGA_WIDTH + new_col_pos;
    }
    else if (new_col_pos >= VGA_WIDTH)
    {
        ++new_row_pos;
        terminals[active_term].col_pos = new_col_pos - VGA_WIDTH;
    }
    else
    {
        terminals[active_term].col_pos = new_col_pos;
    }

    if ((new_row_pos >= 0) && (new_row_pos < VGA_HEIGHT))
    {
        terminals[active_term].row_pos = new_row_pos;
    }
    
    if (new_row_pos == VGA_HEIGHT)
    {
        terminals[active_term].row_pos = VGA_HEIGHT - 1;
        terminal_update();
    }

    update_cursor(terminals[active_term].col_pos, terminals[active_term].row_pos);
}

/**
 * @brief Set the terminal color to color
 * 
 * @param color 
 */
void terminal_set_color(uint8_t color)
{
    terminals[active_term].terminal_color = color;
}

/**
 * @brief Reset the terminal color to white letter on black background
 * 
 */
void terminal_reset_color()
{
    terminals[active_term].terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

/**
 * @brief Write a string to the terminal
 * 
 * @param str 
 * @param len 
 * @return size_t 
 */
size_t terminal_write(const char *str, size_t len)
{
    size_t i = 0;

    while (str[i] && i < len)
    {
        terminal_putchar(str[i++]);
    }
    return (i);
}

/**
 * @brief Init terminals before using them
 * 
 */
void terminal_init(void)
{
    for (size_t i = 0; i < MAX_TERM; i++)
    {
        terminals[i].col_pos = 0;
        terminals[i].row_pos = 0;
        terminals[i].terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        terminals[i].terminal_buff = (uint16_t *)VGA_MEMORY;
        terminal_set_blank_spaces(&terminals[i]);
    }
}
