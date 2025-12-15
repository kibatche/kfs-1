#include <stdio.h>

/**
 * @brief Cette fonction imprime un tableau de char sur la sortie standard
 * 
 * @param s 
 * @return int 
 */
int puts(const char *s)
{
    if (s)
        return write(1, s, strlen(s));
    return -1;
}
