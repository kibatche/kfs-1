#ifndef TTY_H
# define TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vga.h>

#define VGA_PORT_INDEX 0x3D4
#define VGA_PORT_DATA 0x3D5
#define PS2_IO_PORT_DATA 0x60
#define PS2_STATUS_REGISTER 0x64
#define PS2_INPUT_STATUS_OFFSET 0x1

#define KEY_ESCAPE_SEQ 0xE0
#define ARROW_UP 0x48
#define ARROW_DOWN 0x50
#define ARROW_LEFT 0x4B
#define ARROW_RIGHT 0x4D

unsigned char inb(unsigned short port);
void outb(unsigned char data, unsigned short port);
void update_cursor(size_t x, size_t y);
void move_cursor(size_t offset_x, size_t offset_y);
void terminal_set_color(uint8_t color);
void terminal_reset_color();
int terminal_putchar(char c);
size_t terminal_write(const char *str, size_t len);
void terminal_init(void);

void process_scancodes(void);

#endif
