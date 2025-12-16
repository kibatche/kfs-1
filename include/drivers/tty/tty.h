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
void terminal_init(void);
int terminal_putchar(char c);
size_t terminal_write(const char *str, size_t len);

#endif
