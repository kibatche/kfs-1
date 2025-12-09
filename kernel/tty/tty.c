#include <tty.h>
#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

/**
 * variables globales pour le terminal et es differents calculs
**/

size_t terminal_row;
size_t terminal_col;
uint8_t terminal_color;
uint16_t *terminal_buff = (uint16_t *)VGA_MEMORY;

void terminal_init(void)
{
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    for (size_t y = 0; y < VGA_HEIGTH; y++)
    {
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
	    const size_t idx = y * VGA_WIDTH + x;
	    terminal_buff[idx] = vga_entry(' ', terminal_col);
	}
    }
}

int terminal_putchar(char c)
{
    const size_t idx = terminal_row * VGA_WIDTH + terminal_col;
    if (c != '\n')
    {
        terminal_buff[idx] = vga_entry(c, terminal_color);
        terminal_set_cursor(false);
    }
    else
       terminal_set_cursor(true);
    return 1;
 }

int terminal_write(const char *str, size_t len)
{
    int i = 0;
    while(str[i] && i < (int)len)
    {
        terminal_putchar(str[i]);
        i++;
    }
    return i;
}

void terminal_set_cursor(bool newline)
{
    if (newline == true)
    {
        terminal_col = 0;
        if (++terminal_row == VGA_HEIGTH)
            terminal_row = 0;
        return;
    }
    if (++terminal_col == VGA_WIDTH) {
	    terminal_col  = 0;
	    if (++terminal_row == VGA_HEIGTH)
            terminal_row = 0;
    }
}

void terminal_set_color(uint8_t color)
{
    terminal_color = color;
}

