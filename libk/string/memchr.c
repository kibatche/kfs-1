#include <string.h>

/**
 * @brief Chercher le int c dans le buffer b avec un taille de len. Retourne un pointeur sur le caracère trouvé si tel est le cas,
 * sinon retourne NULL
 * 
 * @param b 
 * @param c 
 * @param len 
 * @return void* 
 */
void	*memchr(const void *b, int c, size_t len)
{
	unsigned char	char_cpy;
	unsigned char	*b_cpy;

	b_cpy = (unsigned char *)b;
	char_cpy = (unsigned char)c;
	while (len--)
	{
		if (*b_cpy == char_cpy)
			return (b_cpy);
		b_cpy++;
	}
	return (NULL);
}
