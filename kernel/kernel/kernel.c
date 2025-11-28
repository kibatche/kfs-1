#include <tty.h>
#include <stdio.h>

void kernel_main(void)
{
    terminal_init();
    puts("KKernelYo.\n");
}
