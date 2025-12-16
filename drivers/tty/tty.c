#include <tty.h>
#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

#define VGA_INDEX_BYTE_PORT 0x3D4
#define VGA_DATA_BYTE_PORT 0x3D5

/**
 * variables globales pour le terminal et les differents calculs
**/
size_t col_pos;
size_t row_pos;
uint8_t terminal_color;
uint16_t *terminal_buff = (uint16_t *)VGA_MEMORY;

unsigned char inb(unsigned short port)
{
    unsigned char result;

    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return (result);
}

void outb(unsigned char data, unsigned short port)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void update_cursor(size_t x, size_t y)
{
    uint16_t pos = x + (y * VGA_WIDTH);

    outb(0x0F, VGA_INDEX_BYTE_PORT);
    outb((uint8_t) (pos & 0xFF), VGA_DATA_BYTE_PORT);
    outb(0x0E, VGA_INDEX_BYTE_PORT);
    outb((uint8_t) ((pos >> 8) & 0xFF), VGA_DATA_BYTE_PORT);
}

static void update_terminal()
{
    for (size_t row = 0; row < (VGA_HEIGHT); row++)
    {
        memcpy(&terminal_buff[row], &terminal_buff[row + 1], VGA_WIDTH);
    }
}

void handle_screen_limits(bool is_newline)
{
    if (is_newline)
    {
        col_pos = 0;
        row_pos += 1;
        if (row_pos >= VGA_HEIGHT)
        {
            update_terminal();
        }
    }
    else
    {
        col_pos += 1;
        if (col_pos == VGA_WIDTH)
        {
            col_pos = 0;
            row_pos += 1;
            if (row_pos + 1 >= VGA_HEIGHT)
            {
                update_terminal();
            }
        }
    }
}

void terminal_set_color(uint8_t color)
{
    terminal_color = color;
}

void terminal_reset_color()
{
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

int terminal_putchar(char c)
{
    bool is_newline = (c == '\n');

    if (!is_newline)
    {
        const size_t idx = col_pos + (row_pos * VGA_WIDTH);
        terminal_buff[idx] = vga_entry(c, terminal_color);
    }
    handle_screen_limits(is_newline);
    update_cursor(col_pos, row_pos);
    return (1);
 }

size_t terminal_write(const char *str, size_t len)
{
    size_t i = 0;

    while (str[i] && i < len)
    {
        terminal_putchar(str[i++]);
    }
    return (i);
}

void terminal_init(void)
{
    col_pos = 0;
    row_pos = 0;
    terminal_reset_color();
}
