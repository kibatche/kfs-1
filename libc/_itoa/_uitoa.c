#include <_itoa.h>

/**
 * @brief Cette fonction convertit un uint en string.
 * 
 * @param n 
 * @return const char* 
 */
const char *_uitoa(unsigned int n)
{
    return _uitoa_base(n, 10, 0);
}
