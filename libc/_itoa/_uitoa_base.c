#include <_itoa.h>

/**
 * @brief Cette fonction intervertit les caractères dans une string, ex. "24" devient "42"
 * 
 * @param str 
 * @param i 
 */
static void	_swap(char *str, size_t i)
{
	size_t	size;

	str[i] = 0;
	size = strlen(str);
	i = -1;
	while (++i < --size)
	{
		str[i] ^= str[size];
		str[size] ^= str[i];
		str[i] ^= str[size];
	}
}

/**
 * @brief Cette fonction convertit un nombre non signé en une base donnée, avec les lettres en majuscule ou non.
 * 
 * @param n 
 * @param base 
 * @param capslock 
 * @return const char* 
 */
const char	*_uitoa_base(unsigned int n, int base, int capslock)
{
    int i = 0;
    static char s_local[12];//variable locale
    char *s = s_local;// variable retournée
    
    // mise à 0 du buffer statique.
    bzero(s, 12);
    if (n == 0)// cas spécial
        return "0";
    while (n)
    {
	    if (n % base < 10)
            s[i++] = n % base + '0';
        else if (capslock != 0)
            s[i++] = n % base + 'A' - 10;
        else    
            s[i++] = n % base + 'a' - 10;
        n = n / base;
    }
    _swap(s, i);
    return (s);
}



