/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** my_clock.c
*/

#include "my_clock.h"
#include <stdlib.h>
#include "libmy.h"

void destroy_clocks(void)
{
    list_t **cl = clocks();

    while (*cl)
        remove_node(cl, 0, clock_destroy);
}

p_clock_t *p_clock_create(void)
{
    p_clock_t *p = malloc(sizeof(p_clock_t));

    p->clock = sfClock_create();
    p->is_paused = 0;
    p->elapsed = 0;
    return p;
}

sfInt64 get_elapsed_time(p_clock_t *clock)
{
    sfInt64 t = clock->elapsed;

    if (!clock->is_paused)
        t += sfClock_getElapsedTime(clock->clock).microseconds;
    return t;
}

sfBool clock_is_paused(p_clock_t *clock)
{
    return clock->is_paused;
}

void clock_destroy(void *clock)
{
    p_clock_t *c = clock;
    sfClock_destroy(c->clock);
    free(clock);
}
