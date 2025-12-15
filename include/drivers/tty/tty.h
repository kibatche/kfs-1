#ifndef TTY_H
# define TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vga.h>

void terminal_init(void);
void terminal_set_color(uint8_t color);
void terminal_set_cursor(bool newline);
int terminal_putchar(char c);
int terminal_write(const char *str, size_t len);

#endif
