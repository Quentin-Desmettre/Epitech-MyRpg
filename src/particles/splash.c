/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** splash.c
*/

#include "rpg.h"

splash_particles_t *create_splash_particles(sfVector2f pos,
sfVector2f max, sfInt64 dur)
{
    splash_particles_t *s = malloc(sizeof(splash_particles_t));
    list_t **list = &s->particles;

    s->particles = NULL;
    append_node(list, create_splash_particle(dur, max, 0, pos));
    append_node(list, create_splash_particle(dur, max, 1, pos));
    return s;
}

void draw_splash_particles(splash_particles_t *particles, sfRenderWindow *win,
sfVector2f particle_size)
{
    list_t **particle_l = &particles->particles;
    list_t *cur = *particle_l;
    particle_t *tmp;

    do {
        if (!cur)
            break;
        tmp = cur->data;
        anim_splash_particle(particle_l, tmp);
        if (get_elapsed_time(tmp->duration) < tmp->max_dur)
            sfRenderWindow_drawRectangleShape(win, tmp->sprite, NULL);
        else {
            remove_node(&cur, 0, free_particle);
            *particle_l = cur;
            continue;
        }
        cur = cur->next;
    } while (cur != *particle_l);
    check_for_new_splash(particle_l, max_dur_splash, particle_size);
}

void destroy_splash_particles(splash_particles_t *s)
{
    while (s->particles)
        remove_node(&s->particles, 0, free_particle);
    free(s);
}
