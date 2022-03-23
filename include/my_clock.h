/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** my_clock.h
*/

#ifndef MY_CLOCK_H
    #define MY_CLOCK_H
    #include <SFML/System.h>

typedef struct {
    sfClock *clock;
    sfInt64 elapsed;
    sfBool is_paused;
} p_clock_t;

p_clock_t *p_clock_create(void);
sfInt64 get_elapsed_time(p_clock_t *clock);
sfBool clock_is_paused(p_clock_t *clock);
void clock_destroy(p_clock_t *clock);
void pause_clock(p_clock_t *clock);
void resume_clock(p_clock_t *clock);
void restart_clock(p_clock_t *clock);

#endif
