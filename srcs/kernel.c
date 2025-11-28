#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#if defined(__linux__)
    #error "Utilisation d'un cross-compiler obligatoire"
#endif

#if !defined(__i386__)
    #error "Ce kernel doit etre compile en 32 bits."
#endif

/**
 * Taille du terminal
**/
#define VGA_WIDTH 80
#define VGA_HEIGTH 25
#define VGA_MEMORY 0xB8000

/**
 * variables globales pour le terminal et es differents calculs
**/

size_t terminal_row;
size_t terminal_col;
uint8_t terminal_color;
uint16_t *terminal_buff = (uint16_t *)VGA_MEMORY;

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

void putchar(char c)
{
    const size_t idx = terminal_row * VGA_WIDTH + terminal_col;
    terminal_buff[idx] = vga_entry(c, terminal_color);
    if (++terminal_col == VGA_WIDTH) {
	terminal_col  = 0;
	if (++terminal_row == VGA_HEIGTH) terminal_row = 0;
    }
 }

void putstr(char *str)
{
    size_t i = 0;
    while (str[i])
    {
	putchar(str[i]);
	i++;
    }
}

void init_terminal(void)
{
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_MAGENTA);

    for (size_t y = 0; y < VGA_HEIGTH; y++)
    {
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
	    const size_t idx = y * VGA_WIDTH + x;
	    terminal_buff[idx] = vga_entry(' ', terminal_col);
	}
    }
}

void set_terminal_color(uint8_t color)
{
    terminal_color = color;
}

void kernel_main(void)
{
    init_terminal();
    putstr("KKernelYo.\n");
}
