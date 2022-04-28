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
    s->creation_pos = pos;
    s->anim_dur = create_clock();
    s->max_size = max;
    return s;
}

void draw_splash_particles(splash_particles_t *particles,
sfRenderTexture *rtex, int is_in_rush, int update)
{
    list_t *cur = particles->particles;
    particle_t *tmp;

    do {
        if (!cur)
            break;
        tmp = cur->data;
        if (update)
            anim_splash_particle(&(particles->particles), tmp);
        if (get_elapsed_time(tmp->duration) < tmp->max_dur || !update)
            sfRenderTexture_drawRectangleShape(rtex, tmp->sprite, NULL);
        else {
            remove_node(&cur, 0, free_particle);
            particles->particles = cur;
        }
        cur = cur ? cur->next : NULL;
    } while (cur != particles->particles);
    if (update)
        check_for_new_splash(particles, max_dur_splash, is_in_rush);
}

void move_splash_particles(splash_particles_t *s, sfVector2f offset)
{
    s->creation_pos.x += offset.x;
    s->creation_pos.y += offset.y;
}

void destroy_splash_particles(splash_particles_t *s)
{
    while (s->particles)
        remove_node(&s->particles, 0, free_particle);
    free(s);
}
