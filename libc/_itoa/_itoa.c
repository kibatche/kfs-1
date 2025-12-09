#include <_itoa.h>

static void	_swap(char *str, int i, int sign)
{
	int	size;

	if (sign)
		str[i++] = '-';
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

static int	_abs(long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

/**
 * @brief Cette fonction convertit un int en string. Le long est là pour éviter un overflow avec INT_MIN (define à implémenter ?)
 * 
 * @param n 
 * @return const char* 
 */
const char	*_itoa(long n)
{
    int i = 0;
    int sign = n < 0;
    static char s_local[12];
    char *s = s_local;
    
    bzero(s, 12);
    if (n == 0)
        return "0";
    while (_abs(n))
    {
	    if (_abs(n) % 10 < 10)
            s[i++] = _abs(n % 10) + '0';
        n = _abs(n / 10);
    }
    _swap(s, i, sign);
    return s;
}
