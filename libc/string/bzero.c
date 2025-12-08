#include <string.h>

void	bzero(void *b, size_t len)
{
	char	*cpy;

	cpy = (char *)b;
	while (len--)
		*cpy++ = 0;
}
