/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** srand.c
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void my_srand(void)
{
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned seed;

    if (fd < 0 || read(fd, &seed, sizeof(unsigned)) != sizeof(unsigned))
        return srand((unsigned)(unsigned long)(&seed));
    close(fd);
    srand(seed);
}
