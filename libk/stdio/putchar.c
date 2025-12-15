#include <stdio.h>

/**
 * @brief Cette fonction imprime un char sur la sortie standard
 * 
 * @param c 
 * @return int 
 */
int putchar(int c)
{
    unsigned char uc = (unsigned char)c;
    return write(1, &uc, 1);
}
