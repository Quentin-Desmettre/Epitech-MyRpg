/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** srand.c
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "rpg.h"

sfVector2f win_size(window_t *win)
{
    return (sfVector2f){win->mode.width,
    win->mode.height};
}

sfInt32 my_rand(sfInt32 min, sfInt32 max)
{
    return rand() % (max - min + 1) + min;
}

sfVector2f rand_dir(void)
{
    sfVector2f v;

    v.x = 1 - rand() % 3;
    v.y = v.x ? 0 : rand() % 2;
    if (!v.x && !v.y)
        v.y = -1;
    return v;
}

void my_srand(void)
{
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned seed;

    if (fd < 0 || read(fd, &seed, sizeof(unsigned)) != sizeof(unsigned))
        return srand((unsigned)(unsigned long)(&seed));
    close(fd);
    srand(seed);
}
