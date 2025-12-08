#include <stdio.h>

int puts(const char *s)
{
    if (s)
        return write(1, s, strlen(s));
    return -1;
}
