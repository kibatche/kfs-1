#include <string.h>

/**
 * @brief Copie src dans dst. dst doit avoir assez d'espace pour contenir les données de src + le caractère '\0'.
 * 
 * @param dst 
 * @param src 
 * @return char* 
 */
char	*strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

