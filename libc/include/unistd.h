#ifndef UNISTD_H
# define UNISTD_H

// Not the best design, but for now we have not a
// syscall routine (eg, ring isolation) to avoid
// this (In my opinion)

//kernel header
#include <tty.h>

//gcc header
#include <stddef.h>

int write(int fd, const void *buf, size_t count);

#endif
