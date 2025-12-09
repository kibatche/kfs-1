#ifndef _ITOA_H
# define _ITOA_H

#include <string.h>

const char *_itoa(long n);
const char *_uitoa(unsigned int n);
const char *_uitoa_base(unsigned int n, int base, int capslock);

#endif
