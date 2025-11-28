#include <string.h>

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
