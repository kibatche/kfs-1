#include <tty.h>
#include <stdio.h>

void kernel_main(void)
{
    terminal_init();
    printf("42\n");
}
