#include <string.h>

/**
 * @brief Place l'int c dans dans dst sur len octets.
 * 
 * @param dest 
 * @param c 
 * @param len 
 * @return void* 
 */
void	*memset(void *dest, int c, size_t len)
{
	unsigned char	*cpy;

	cpy = (unsigned char *)dest;
	while (len--)
		*cpy++ = (unsigned char)c;
	return (dest);
}
