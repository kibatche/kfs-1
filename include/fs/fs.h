#ifndef FS_H
# define FS_H

#include <tty.h>
#include <stddef.h>

int write(int fd, const void *buf, size_t len);

#endif