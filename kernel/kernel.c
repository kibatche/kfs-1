#include <tty.h>
#include <stdio.h>

void kernel_main(void)
{
    terminal_init();
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