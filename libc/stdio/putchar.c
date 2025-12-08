#include <stdio.h>

int putchar(int c)
{
    unsigned char uc = (unsigned char)c;
    return write(1, &uc, 1);
}
