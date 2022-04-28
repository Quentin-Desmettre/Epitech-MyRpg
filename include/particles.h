/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** particles.h
*/

#ifndef PARTICLES_H
    #define PARTICLES_H

    #include "my_clock.h"
    #include <SFML/Graphics.h>
    #include "libmy.h"
    #define NB_PARTICLES 24

static const sfInt64 max_dur_splash = 650000;
static const sfInt64 max_dur_circ = 1000000;

typedef struct {
    p_clock_t *duration;
    p_clock_t *delta_t;
    sfRectangleShape *sprite;
    sfVector2f max_size;
    sfInt64 max_dur;
    sfVector2f vector;
    int has_child;
    int has_parent;
} particle_t;

typedef struct {
    list_t *particles;
    p_clock_t *anim_dur;
    sfVector2f creation_pos;
    sfVector2f max_size;
} splash_particles_t;

typedef struct {
    particle_t *particles[NB_PARTICLES];
} circular_splash_t;

particle_t *create_splash_particle(sfInt64 max_dur,
sfVector2f max_size, int is_left, sfVector2f pos);
void check_for_new_splash(splash_particles_t *particles,
sfInt64 dur, int is_in_rush);
splash_particles_t *create_splash_particles(sfVector2f pos,
sfVector2f max, sfInt64 dur);
void draw_splash_particles(splash_particles_t *particles,
sfRenderTexture *rtex, int is_in_rush, int update);
void destroy_splash_particles(splash_particles_t *s);
void move_splash_particles(splash_particles_t *s, sfVector2f offset);
void free_particle(void *p);
circular_splash_t *create_circular_splash(sfVector2f pos, sfVector2f max_size);
int draw_circular_splash(circular_splash_t **circu, sfRenderTexture *rtex);
void anim_splash_particle(list_t **particles, particle_t *p);

#endif
