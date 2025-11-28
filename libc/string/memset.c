#include <string.h>

void	*memset(void *dest, int c, size_t len)
{
	unsigned char	*cpy;

	cpy = (unsigned char *)dest;
	while (len--)
		*cpy++ = (unsigned char)c;
	return (dest);
}
