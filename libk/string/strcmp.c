#include <string.h>

/**
 * @brief Compare s1 et s2 et retourne la différence.
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int	strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;

	i = 0;
	s1_cpy = (unsigned char *)s1;
	s2_cpy = (unsigned char *)s2;
	while (s1_cpy[i] && s2_cpy[i]
		&& s1_cpy[i] == s2_cpy[i])
		i++;
	return (s1_cpy[i] - s2_cpy[i]);
}
