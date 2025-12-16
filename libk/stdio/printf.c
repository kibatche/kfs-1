#include <stdio.h>
#include <string.h>
#include <itoa.h>



/**
 * @brief Imprime selon le format choisi (int, unsigned int, hexadécimal minuscule, héxadémal majuscule, char[], char)
 * l'argument sous forme de tableau de caractères.
 *
 * @param s 
 * @param args 
 * @return int 
 */
static int print(const char *s, va_list *args)
{
    const char *str = NULL;
    switch (*(s + 1))
    {
    case 'd':
        str = itoa(va_arg(*args, int));
        return write(1, str, strlen(str));
        break;
    case 'u':
        str = uitoa(va_arg(*args, unsigned int));
        return write(1, str, strlen(str));
        break;
    case 'x':
        str = uitoa_base(va_arg(*args, unsigned int), 16, 0);
        return write(1, str, strlen(str));
        break;
    case 'X':
        str = uitoa_base(va_arg(*args, unsigned int), 16, 1);
        return write(1, str, strlen(str));
        break;
    case 's':
        str = va_arg(*args, char *);
        if (str)
            return write(1, str, strlen(str));
        return write(1, "(null)", 6);
        break;
    case 'c':
        return putchar(va_arg(*args, int));
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
            res += print(s++, &args);
        else
            res += putchar(*s);
        s++;
    }
    va_end(args);
    return res;
}

