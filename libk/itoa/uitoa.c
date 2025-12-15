#include <itoa.h>

/**
 * @brief Cette fonction convertit un uint en string.
 * 
 * @param n 
 * @return const char* 
 */
const char *uitoa(unsigned int n)
{
    return uitoa_base(n, 10, 0);
}
