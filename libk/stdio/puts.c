#include <stdio.h>

/**
 * @brief Cette fonction imprime un tableau de char sur la sortie standard
 * 
 * @param s 
 * @return int 
 */
int puts(const char *s)
{
    int len = 0;
    char nl = '\n';
    if (s)
    {
        len = write(1, s, strlen(s));
        write(1, &nl, 1);
        return len + 1;
    }
    return -1;
}
