#include <string.h>

/**
 * @brief Compare b1 et b2 pendant len octets et retourne la différence.
 * 
 * @param dst 
 * @param src 
 * @param len 
 * @return void* 
 */
int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	unsigned char	*b1_cpy;
	unsigned char	*b2_cpy;

	b1_cpy = (unsigned char *)b1;
	b2_cpy = (unsigned char *)b2;
	if (len == 0)
		return (0);
	while (--len && *b1_cpy == *b2_cpy)
	{
		b1_cpy++;
		b2_cpy++;
	}
	return ((int)(*b1_cpy - *b2_cpy));
}
