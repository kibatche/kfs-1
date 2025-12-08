#include <stdio.h>
#include <string.h>
#include <_itoa.h>

/**
 * Imprime selon le type choisi (int, unsigned int, hexadécimal minuscule, héxadémal majuscule)
 * l'argument sous forme de tableau de caractères.
**/

static int print(const char *s, va_list args)
{
    switch(*(s + 1))
    {
    case 'd':
        return puts(_itoa_base(va_arg(args, int), 10, 0));
        break;
    case 'u':
        int a = va_arg(args, int);
        if (a < 0)
            return puts(_itoa_base(a + 1 + 4294967295, 10, 0));
        else
            return puts(_itoa_base(a, 10, 0));
        break;
    case 'x':
        int b = va_arg(args, int);
        if (b < 0)
            return puts(_itoa_base(b + 1 + 4294967295, 16, 0));
        else
            return puts(_itoa_base(b, 16, 0));
        break;
    case 'X':
        int c = va_arg(args, int);
        if (c < 0)
            return puts(_itoa_base(c + 1 + 4294967295, 16, 1));
        else
            return puts(_itoa_base(c, 16, 0));
        break;
    case 's':
        char *str = va_arg(args, char *);
        if (str)
            return puts(str);
        else
            return puts("(null)");
        break;
    case 'c':
        return putchar(va_arg(args, int));
        break;
    case '%':
        return putchar('%');
        break;
    default:
        return -1;
    }
}

int printf(const char *s, ...)
{
    va_list args;
    int res = -1;
    
    if (s == NULL)
        return -1;
    va_start(args, s);
    while (*s)
    {
        if (*s == '%')
            print(s, args);
        else
            putchar(*s);
        s++;
    }
    va_end(args);
    return res;
}

