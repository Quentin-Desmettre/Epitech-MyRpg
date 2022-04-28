/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create_splash.c
*/

#include "rpg.h"
#include "particles.h"

particle_t *create_splash_particle(sfInt64 max_dur,
sfVector2f max_size, int is_left, sfVector2f pos)
{
    particle_t *p = malloc(sizeof(particle_t));

    p->duration = create_clock();
    p->sprite = sfRectangleShape_create();
    p->max_size = max_size;
    p->max_dur = max_dur;
    p->delta_t = create_clock();
    sfRectangleShape_setSize(p->sprite, max_size);
    sfRectangleShape_setOrigin(p->sprite,
    (sfVector2f){max_size.x * 0.5, max_size.y * 0.5});
    sfRectangleShape_setFillColor(p->sprite, sfRed);
    p->vector = (sfVector2f){5, 0};
    rotate_vector(&p->vector, is_left ?
    my_rand(-130, -110) : my_rand(-70, -50));
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
    float elapsed = get_elapsed_time(p->duration);
    float percent = 1 - elapsed / p->max_dur;
    sfVector2f new_size = {p->max_size.x * percent, p->max_size.y * percent};

    if (get_elapsed_time(p->delta_t) > 33333) {
        sfRectangleShape_move(p->sprite,
        (sfVector2f){p->vector.x, p->vector.y * 0.1});
        restart_clock(p->delta_t);
        p->vector.x /= 1.1;
        p->vector.y += 2;
        sfRectangleShape_setSize(p->sprite, new_size);
    }
    if (get_elapsed_time(p->duration) > 200000 && !p->has_child
    && get_elapsed_time(p->duration) < p->max_dur && !p->has_parent) {
        pos = sfRectangleShape_getPosition(p->sprite);
        new_particle(p, pos, particles, 0);
        new_particle(p, pos, particles, 1);
        p->has_child = 1;
    }
}

void check_for_new_splash(splash_particles_t *particles,
sfInt64 dur, int is_in_rush)
{
    particle_t *new;

    if (get_elapsed_time(particles->anim_dur) >
    my_rand(100000, 500000) * (1 - is_in_rush * 0.6) &&
    !clock_is_paused(particles->anim_dur)) {
        restart_clock(particles->anim_dur);
        new = create_splash_particle(dur, particles->max_size,
        0, particles->creation_pos);
        new->vector.x /= 1.5;
        new->vector.y /= 1.2;
        append_node(&(particles->particles), new);

        new = create_splash_particle(dur, particles->max_size,
        1, particles->creation_pos);
        new->vector.x /= 1.5;
        new->vector.y /= 1.2;
        append_node(&(particles->particles), new);
    }
}

void free_particle(void *p)
{
    particle_t *pa = p;

    destroy_clock(pa->delta_t);
    destroy_clock(pa->duration);
    sfRectangleShape_destroy(pa->sprite);
    free(pa);
}
