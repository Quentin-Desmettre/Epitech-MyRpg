/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create_splash.c
*/

#include "rpg.h"

particle_t *create_splash_particle(sfInt64 max_dur,
sfVector2f max_size, int is_left, sfVector2f pos)
{
    particle_t *p = malloc(sizeof(particle_t));

    p->duration = p_clock_create();
    p->sprite = sfRectangleShape_create();
    p->max_size = max_size;
    p->max_dur = max_dur;
    p->delta_t = sfClock_create();
    sfRectangleShape_setSize(p->sprite, max_size);
    sfRectangleShape_setOrigin(p->sprite,
    (sfVector2f){max_size.x * 0.5, max_size.y * 0.5});
    sfRectangleShape_setFillColor(p->sprite, sfRed);
    p->vector = (sfVector2f){5, 0};
    rotate_vector(&p->vector, is_left ? -120 : -60);
    sfRectangleShape_setPosition(p->sprite, pos);
    p->has_child = 0;
    p->has_parent = 0;
    return p;
}

void new_particle(particle_t *p, sfVector2f pos,
list_t **particles, int is_left)
{
    particle_t *new = create_splash_particle(p->max_dur,
    p->max_size, is_left, pos);
    new->vector.x /= 1.5;
    new->vector.y /= 1.7;
    new->has_parent = 1;
    append_node(particles, new);
}

void anim_splash_particle(list_t **particles, particle_t *p)
{
    sfVector2f pos;
    if (sfClock_getElapsedTime(p->delta_t).microseconds > 33333) {
        sfRectangleShape_move(p->sprite,
        (sfVector2f){p->vector.x, p->vector.y * 0.1});
        sfClock_restart(p->delta_t);
        p->vector.x /= 1.1;
        p->vector.y += 2;
        sfRectangleShape_scale(p->sprite, (sfVector2f){0.95, 0.95});
    }
    if (get_elapsed_time(p->duration) > 200000 && !p->has_child
    && get_elapsed_time(p->duration) < p->max_dur && !p->has_parent) {
        pos = sfRectangleShape_getPosition(p->sprite);
        new_particle(p, pos, particles, 0);
        new_particle(p, pos, particles, 1);
        p->has_child = 1;
    }
}

void check_for_new_splash(list_t **particles, sfInt64 dur, sfVector2f max)
{
    static sfClock *anim_dur = 0;
    particle_t *new;

    if (!anim_dur)
        anim_dur = sfClock_create();
    if (sfClock_getElapsedTime(anim_dur).microseconds > 100000) {
        sfClock_restart(anim_dur);
        new = create_splash_particle(dur, max, 0, (sfVector2f){400, 300});
        new->vector.x /= 1.5;
        new->vector.y /= 1.2;
        append_node(particles, new);

        new = create_splash_particle(dur, max, 1, (sfVector2f){400, 300});
        new->vector.x /= 1.5;
        new->vector.y /= 1.2;
        append_node(particles, new);
    }
}

void free_particle(void *p)
{
    particle_t *pa = p;

    sfClock_destroy(pa->delta_t);
    clock_destroy(pa->duration);
    sfRectangleShape_destroy(pa->sprite);
    free(pa);
}
