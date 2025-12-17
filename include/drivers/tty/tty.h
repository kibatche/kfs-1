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
#define KEY_PRESSED_MASK 0x80
#define SCANCODE_CAPSLOCK 0x3a
#define SCANCODE_LSHIFT 0x2A
#define SCANCODE_RSHIFT 0x36
#define SCANCODE_BACKSPACE 0X0e
#define SCANCODE_ARROW_UP 0x48
#define SCANCODE_ARROW_DOWN 0x50
#define SCANCODE_ARROW_LEFT 0x4B
#define SCANCODE_ARROW_RIGHT 0x4D
#define SCANCODE_F1 0x3b
#define SCANCODE_F2 0x3c

unsigned char inb(unsigned short port);
void outb(unsigned char data, unsigned short port);
void update_cursor(int x, int y);
void move_cursor(int offset_x, int offset_y);
void terminal_set_color(uint8_t color);
void terminal_set_blank_spaces();
void terminal_reset_color();
int terminal_putchar(char c);
size_t terminal_write(const char *str, size_t len);
void terminal_init(void);

void process_scancodes(void);

#endif
