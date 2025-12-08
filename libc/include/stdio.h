#ifndef STDIO_H
# define STDIO_H

//libc headers
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int printf(const char *s, ...);
int putchar(int c);
int puts(const char *s);

#endif

