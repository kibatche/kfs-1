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
size_t cursor_x;
size_t cursor_y;
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

int terminal_putchar(char c)
{
    if (c == '\n')
    {
        cursor_y += 1;
    }
    else
    {
        cursor_x += 1;
        if (cursor_x == VGA_WIDTH)
        {
            cursor_x = 0;
            cursor_y += 1;
        }
        const size_t idx = cursor_x + (cursor_y * VGA_WIDTH);
        terminal_buff[idx] = vga_entry(c, terminal_color);
    }
    update_cursor(cursor_x, cursor_y);
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
    cursor_x = 0;
    cursor_y = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}
