#ifndef _ITOA_H
# define _ITOA_H

#include <string.h>

const char *itoa(long n);
const char *uitoa(unsigned int n);
const char *uitoa_base(unsigned int n, int base, int capslock);

#endif
