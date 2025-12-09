#include <stdio.h>
#include <string.h>
#include <_itoa.h>



/**
 * @brief Imprime selon le format choisi (int, unsigned int, hexadécimal minuscule, héxadémal majuscule, char[], char)
 * l'argument sous forme de tableau de caractères.
 *
 * @param s 
 * @param args 
 * @return int 
 */
static int print(const char *s, va_list args)
{
    switch(*(s + 1))
    {
    case 'd':
        return puts(_itoa(va_arg(args, int)));
        break;
    case 'u':
        return puts(_uitoa(va_arg(args, unsigned int)));
        break;
    case 'x':
        return puts(_uitoa_base(va_arg(args, unsigned int), 16, 0));
        break;
    case 'X':
        return puts(_uitoa_base(va_arg(args, unsigned int), 16, 1));
        break;
    case 's':
        char *str = va_arg(args, char *);
        if (str)
            return puts(str);
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

/**
 * @brief Cette fonction imprime un type (int, unsigned int, char *, c) selon la forme désirée.
 * 
 * @param s 
 * @param ... 
 * @return int 
 */
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
            print(s++, args);
        else
            putchar(*s);
        s++;
    }
    va_end(args);
    return res;
}

