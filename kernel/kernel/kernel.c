#include <tty.h>
#include <stdio.h>

void kernel_main(void)
{
    terminal_init();
    printf("%d\n", 42);
}
