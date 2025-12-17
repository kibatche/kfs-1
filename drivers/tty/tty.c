#include <tty.h>
#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

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

    outb(0x0F, VGA_PORT_INDEX);
    outb((uint8_t) (pos & 0xFF), VGA_PORT_DATA);
    outb(0x0E, VGA_PORT_INDEX);
    outb((uint8_t) ((pos >> 8) & 0xFF), VGA_PORT_DATA);
}


void move_cursor(size_t offset_x, size_t offset_y)
{
    size_t new_col_pos = col_pos + offset_x;
    size_t new_row_pos = row_pos + offset_y;

    if (new_col_pos <= 0)
    {
        --new_row_pos;
        col_pos = VGA_WIDTH + new_col_pos;
    }
    else if (new_col_pos >= VGA_WIDTH)
    {
        ++new_row_pos;
        col_pos = new_col_pos - VGA_WIDTH;
    }
    else
    {
        col_pos = new_col_pos;
    }
    
    if (new_row_pos < VGA_HEIGHT)
    {
        row_pos = new_row_pos;
    }
    
    if (new_row_pos == VGA_HEIGHT)
    {
        row_pos = VGA_HEIGHT - 1;
        terminal_update();
    }
    
    update_cursor(col_pos, row_pos);
}

void terminal_update()
{
    for (size_t row = 0; row < VGA_HEIGHT - 1; row++)
    {
        memcpy(&terminal_buff[row * VGA_WIDTH], &terminal_buff[(row + 1) * VGA_WIDTH], VGA_WIDTH * sizeof(uint16_t));
    }

    for (size_t i = 0; i < VGA_WIDTH; i++)
    {
        terminal_buff[((VGA_HEIGHT - 1) * VGA_WIDTH) + i] = vga_entry(' ', terminal_color);
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

void terminal_set_blank_spaces()
{
    for (size_t i = 0; i < VGA_WIDTH;i++)
    {
        for (size_t j = 0; j < VGA_HEIGHT; j++)
        {
            terminal_buff[i + (j * VGA_WIDTH);] = vga_entry(' ', terminal_color);
        }
    }
}

int terminal_putchar(char c)
{
    const bool is_newline = (c == '\n');

    if (is_newline)
    {
        col_pos = 0;
        move_cursor(0, 1);
        return (0);
    }
    const size_t idx = col_pos + (row_pos * VGA_WIDTH);
    terminal_buff[idx] = vga_entry(c, terminal_color);
    move_cursor(1, 0);
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
