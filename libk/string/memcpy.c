#include <string.h>

/**
 * @brief Copie len octets de src dans dst.
 * 
 * @param dst 
 * @param src 
 * @param len 
 * @return void* 
 */
void	*memcpy(void *dst, const void *src, size_t len)
{
	char		*dst_cpy;
	const char	*src_cpy;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_cpy = (char *)dst;
	src_cpy = (const char *)src;
	while (len--)
		*(dst_cpy++) = *(src_cpy++);
	return (dst);
}
