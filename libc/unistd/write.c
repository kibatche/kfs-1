#include <unistd.h>

/**
 * Because our kernel is not totally finished
 * we do not have a mecanism such as File descriptor.
 * But because we need money asap, we've implmented it partially
 * and hope to trick the user by letting them put a fd and finally output the string into the VGA buffer.
 *
**/
int write(int fd, const void *buf, size_t len)
{
    (void)fd;//<= the clever trick
    return terminal_write((const char *)buf, len);
}
