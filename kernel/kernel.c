#include <tty.h>
#include <keyboard.h>
#include <stdio.h>

void print_welcome_msg(void)
{
    terminal_set_color(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    printf("42\n");
    terminal_set_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

void kernel_main(void)
{
    terminal_init();
    print_welcome_msg();

    while (1)
    {
        process_scancodes();
    }
}
