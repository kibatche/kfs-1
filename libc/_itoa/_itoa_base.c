#include <_itoa.h>

static void	_swap(char *str, int i, int sign)
{
	int	size;

	if (sign == -1)
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

static int	_abs(long long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

const char	*_itoa_base(long long n, int base, int caps)
{
    int i;
    int sign;
    char s_local[12];
    char *s = s_local;

    if (n == 0)
        return "0";
    sign = 1;
    i = 0;
    if (n < 0)
        sign *= -1;
    while (_abs(n))
    {
	if (_abs(n) % base < 10)
            s[i++] = _abs(n % 10) + '0';
        else if (caps != 0)
            s[i++] = _abs(n % 10) + 'A' - 10;
        else    
            s[i++] = _abs(n % 10) + 'a' - 10;
        n = _abs(n / 10);
    }
    _swap(s, i, sign);
    return (s);
}

