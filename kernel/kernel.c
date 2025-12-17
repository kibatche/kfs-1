#include <tty.h>
#include <stdio.h>

extern uint16_t *terminal_buff;

static void bonus_printf(void)
{
    printf("%s %d %s\n", "Et le cordeau des trompettes marines", 12, "Un AUTRE TEST");
    printf("%d %d %d\n", 42, 55, 68);
    printf("Ceci est le nombre -2147483648 en int : %d\n", -2147483648);
    printf("Ceci est le nombre 2147483647 en int : %d\n", 2147483647);
    printf("Ceci est le nombre 4294967295 en unsigned int : %u\n", 4294967295);
    printf("Ceci est le nombre 4294967295 en HEX : %X\n", 4294967295);
    printf("Ceci est le nombre 4294967295 en hex : %x\n", 4294967295);
    printf("Ceci est une chaine de caracteres : %s\n", "abcdefghijklmnopqrstuvwxy0123456789,;!?./%*");
    printf("Ceci est une chaine de caracteres nulle: %s\n", NULL);
    printf("Ceci est un caractere : %c\n", 'A');
}

static void print_welcome_msg(void)
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
