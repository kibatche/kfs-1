#include <tty.h>
#include <stdio.h>

extern uint16_t *terminal_buff;

void bonus_printf(void)
{
    int res = printf("%s %d %s\n", "Et le cordeau des trompettes marines", 12, "Un AUTRE TEST");
    printf("Nombre de caracteres ecrits : %d\n", res);
    // printf("%d %d %d\n", 42, 55, 68);
    // printf("Ceci est le nombre -2147483648 en int : %d\n", -2147483648);
    // printf("Ceci est le nombre 2147483647 en int : %d\n", 2147483647);
    // printf("Ceci est le nombre 4294967295 en unsigned int : %u\n", 4294967295);
    // printf("Ceci est le nombre 4294967295 en HEX : %X\n", 4294967295);
    // printf("Ceci est le nombre 4294967295 en hex : %x\n", 4294967295);
    // printf("Ceci est une chaine de caracteres : %s\n", "abcdefghijklmnopqrstuvwxy0123456789,;!?./%*");
    // printf("Ceci est une chaine de caracteres nulle: %s\n", NULL);
    // printf("Ceci est un caractere : %c\n", 'A');
}

void print_welcome_msg(void)
{
    terminal_set_color(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    printf("40\n");
    printf("41\n");
    printf("42\n");
    printf("43\n");
    printf("44\n");
    printf("45\n");
    printf("46\n");
    printf("47\n");
    printf("48\n");
    printf("49\n");
    printf("410\n");
    printf("411\n");
    printf("412\n");
    printf("413\n");
    printf("414\n");
    printf("415\n");
    printf("416\n");
    printf("417\n");
    printf("418\n");
    printf("419\n");
    printf("420\n");
    printf("421\n");
    printf("422\n");
    printf("423\n");
    printf("424\n");
    printf("425\n");
    printf("426\n");
    terminal_set_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

void kernel_main(void)
{
    terminal_init();
    print_welcome_msg();
}
