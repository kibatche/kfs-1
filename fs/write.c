#include <fs.h>

/**
 * @brief Imprime len octets sur la sortie standard le buffer buf 
 *
 * Parce que notre kernel n'est pas terminé - de loin - il n'y a pas de mécanisme de file descriptor.
 * La signature est laissée pour une utilisation future. 
 * @param fd 
 * @param buf 
 * @param len 
 * @return int 
 */
int write(int fd, const void *buf, size_t len)
{
    (void)fd;//<= the clever trick
    return terminal_write((const char *)buf, len);
}
