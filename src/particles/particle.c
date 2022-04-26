/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** particle.c
*/

#include "rpg.h"
#include "my_clock.h"


    #include "my_clock.h"

typedef enum {rectangle, circle} particle_type_t;

typedef struct {
    float coefs[3];
    p_clock_t *duration;
    sfClock *delta_t;
    void *sprite;
    sfVector2f max_size;
    sfInt64 max_dur;
    int type;
    sfVector2f vector;
    float gravity;
    int has_child;
    int has_parent;
} particle_t;

    #define DX p->max_size.y * 0.01

void update_particle(particle_t *p);
void draw_particle(particle_t *p, sfRenderWindow *rtex);
particle_t *build_particle(sfInt64 max_dur, particle_type_t type,
sfVector2f max_size, float angle);
void rotate_vector(sfVector2f *vec, float degree);


void update_particle(particle_t *p)
{
    float elapsed = get_elapsed_time(p->duration);
    sfInt64 dx = sfClock_getElapsedTime(p->delta_t).microseconds;
    float a = p->coefs[0];
    float b = p->coefs[1];
    float c = p->coefs[2];
    float percent = 1 - elapsed / p->max_dur;
    sfVector2f new_size = {p->max_size.x * percent, p->max_size.y * percent};

    if (dx > 100000)
        sfClock_restart(p->delta_t);
    if (p->type == rectangle) {
        sfRectangleShape_setSize(p->sprite, new_size);
        sfRectangleShape_move(p->sprite, p->vector);
    } else {
        sfCircleShape_setRadius(p->sprite, new_size.x);
    }
}

void draw_particle(particle_t *p, sfRenderWindow *rtex)
{
    if (p->type == circle)
        sfRenderWindow_drawCircleShape(rtex, p->sprite, NULL);
    if (p->type == rectangle)
        sfRenderWindow_drawRectangleShape(rtex, p->sprite, NULL);
}

particle_t *build_particle(sfInt64 max_dur, particle_type_t type,
sfVector2f max_size, float angle)
{
    particle_t *p = malloc(sizeof(particle_t));

    p->duration = p_clock_create();
    p->sprite = (type == rectangle) ?
    sfRectangleShape_create() : sfCircleShape_create();
    p->max_size = max_size;
    p->max_dur = max_dur;
    p->delta_t = sfClock_create();
    p->type = type;
    if (type == rectangle) {
        sfRectangleShape_setSize(p->sprite, max_size);
        sfRectangleShape_setOrigin(p->sprite,
        (sfVector2f){max_size.x * 0.5, max_size.y * 0.5});
        sfRectangleShape_setFillColor(p->sprite, sfRed);
    } else {
        sfCircleShape_setRadius(p->sprite, max_size.x);
        sfCircleShape_setOrigin(p->sprite,
        (sfVector2f){max_size.x, max_size.x});
        sfCircleShape_setFillColor(p->sprite, sfBlue);
    }
    p->vector = (sfVector2f){5, 0};
    rotate_vector(&p->vector, angle);
    p->vector.y /= 1.1;
    p->has_child = 0;
    p->has_parent = 0;
    return p;
}


