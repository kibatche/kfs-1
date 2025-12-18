#ifndef TTY_H
# define TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vga.h>

#define VGA_PORT_INDEX 0x3D4
#define VGA_PORT_DATA 0x3D5

// maximum allowed terminal
#define MAX_TERM 2

typedef struct tty
{
    size_t col_pos;
    size_t row_pos;
    uint8_t terminal_color;
    uint16_t *terminal_buff;
    uint16_t saved_term_content[VGA_WIDTH * VGA_HEIGHT];
}               tty;

unsigned char inb(unsigned short port);
void outb(unsigned char data, unsigned short port);

void terminal_init(void);

void terminal_set_color(uint8_t color);
void terminal_reset_color(void);

int terminal_putchar(char c);
size_t terminal_write(const char *str, size_t len);

void terminal_switch(size_t term_number);

void move_cursor(int offset_x, int offset_y);

#endif
