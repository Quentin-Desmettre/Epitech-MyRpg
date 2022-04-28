/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** particle.c
*/

#include "rpg.h"
#include "my_clock.h"

static particle_t *create_circular_particle(sfInt64 max_dur,
sfVector2f max_size, float angle, sfVector2f pos)
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
    rotate_vector(&p->vector, angle);
    sfRectangleShape_setPosition(p->sprite, pos);
    p->has_child = 0;
    p->has_parent = 0;
    return p;
}

static void anim_circular_particle(particle_t *p)
{
    float elapsed = get_elapsed_time(p->duration);
    sfInt64 dx = get_elapsed_time(p->delta_t);
    float percent = 1 - elapsed / p->max_dur;
    sfVector2f new_size = {p->max_size.x * percent, p->max_size.y * percent};

    if (dx > 33333) {
        restart_clock(p->delta_t);
        sfRectangleShape_setSize(p->sprite, new_size);
        sfRectangleShape_move(p->sprite, p->vector);
    }
}

static void destroy_circular_splash(circular_splash_t *c)
{
    for (int i = 0; i < NB_PARTICLES; i++)
        free_particle(c->particles[i]);
    free(c);
}

circular_splash_t *create_circular_splash(sfVector2f pos, sfVector2f max_size)
{
    circular_splash_t *c = malloc(sizeof(circular_splash_t));
    float angle;

    for (int i = 0; i < NB_PARTICLES; i++) {
        angle = 360.0 / NB_PARTICLES * i;
        c->particles[i] =
        create_circular_particle(max_dur_circ, max_size, angle, pos);
    }
    return c;
}

int draw_circular_splash(circular_splash_t **circu, sfRenderTexture *rtex)
{
    circular_splash_t *c = *circu;
    particle_t *tmp = c->particles[0];

    if (get_elapsed_time(tmp->duration) > tmp->max_dur) {
        destroy_circular_splash(c);
        *circu = NULL;
        return 0;
    }
    for (int i = 0; i < NB_PARTICLES; i++) {
        anim_circular_particle(c->particles[i]);
        sfRenderTexture_drawRectangleShape(rtex, c->particles[i]->sprite, NULL);
    }
    return 1;
}
