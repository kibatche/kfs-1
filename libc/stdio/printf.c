#include <stdio.h>

int printf(const char *s, ...)
{
    va_list args;
    int res;
    
    if (s == NULL)
        return -1;
    while (*s)
    {
        if (*s == '%')
        {
            va_start(args, s);
            res = puts(va_arg(args, const char *));
        }
        else
            putchar(*s);
        s++;
    }
    va_end(args);
    return res;
}

