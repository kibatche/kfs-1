#ifndef STRING_H
# define STRING_H

#include <stddef.h>

void    *memset(void *dst, int c, size_t len);
void    *memcpy(void *dst, const void *src, size_t len);
void    *memmove(void *dst, const void *src, size_t len);
void    *memchr(const void *b, int c, size_t len);
int     memcmp(const void *b1, const void *b2, size_t len);

char    *strchr(const char *s, int c);
int     strcmp(const char *s1, const char *s2);
char    *strcpy(char *dst, const char *src);
size_t  strlen(const char *s);

#endif

