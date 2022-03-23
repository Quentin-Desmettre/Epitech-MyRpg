/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** time.c
*/

#include "my_clock.h"

void pause_clock(p_clock_t *clock)
{
    if (clock->is_paused)
        return;
    clock->is_paused = sfTrue;
    clock->elapsed += sfClock_getElapsedTime(clock->clock).microseconds;
}

void resume_clock(p_clock_t *clock)
{
    if (!clock->is_paused)
        return;
    clock->is_paused = sfFalse;
    sfClock_restart(clock->clock);
}

void restart_clock(p_clock_t *clock)
{
    clock->is_paused = sfFalse;
    clock->elapsed = 0;
    sfClock_restart(clock->clock);
}
