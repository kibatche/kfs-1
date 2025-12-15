#include <string.h>

/**
 * @brief Mets len 0 dans le buffer b.
 * 
 * @param b 
 * @param len 
 */
void	bzero(void *b, size_t len)
{
	char	*cpy;

	cpy = (char *)b;
	while (len--)
		*cpy++ = 0;
}
