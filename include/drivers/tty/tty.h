#ifndef TTY_H
# define TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vga.h>

unsigned char inb(unsigned short port);
void outb(unsigned char data, unsigned short port);
void update_cursor(size_t x, size_t y);
void handle_screen_limits(bool is_newline);
void terminal_set_color(uint8_t color);
void terminal_reset_color();
int terminal_putchar(char c);
size_t terminal_write(const char *str, size_t len);
void terminal_init(void);

#endif
