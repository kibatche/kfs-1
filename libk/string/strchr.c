#include <string.h>

/**
 * @brief Cherche l'int c dans la string s et retourne un pointeur sur le caractère trouvé, s'il est trouvé, sinon retourne NULL.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char	*strchr(const char *s, int c)
{
	char	c_py;
	char	*s_cpy;
	int		i;

	i = 0;
	s_cpy = (char *)s;
	c_py = (char)c;
	while (s_cpy[i])
	{
		if (s_cpy[i] == c_py)
			return (&s_cpy[i]);
		i++;
	}
	if (c_py == 0)
		return (&s_cpy[i]);
	return (NULL);
}
