#include <_itoa.h>

const char *_itoa(long long n)
{
    return _itoa_base(n, 10, 0);
}
