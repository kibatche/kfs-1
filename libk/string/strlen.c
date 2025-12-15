#include <string.h>

/**
 * @brief Retourne la taille de s
 * 
 * @param s 
 * @return size_t 
 */
size_t	strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
