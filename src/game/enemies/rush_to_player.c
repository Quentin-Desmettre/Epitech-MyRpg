/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rush_to_player.c
*/

#include "rpg.h"

sfVector2f *alloc_v2f(float x, float y)
{
    sfVector2f *v = malloc(sizeof(sfVector2f));

    v->x = x;
    v->y = y;
    return v;
}

sfVector2f *is_intersect(sfVector2f p0, sfVector2f p1,
sfVector2f p2, sfVector2f p3)
{
    float s1_x = p1.x - p0.x;
    float s1_y = p1.y - p0.y;
    float s2_x = p3.x - p2.x;
    float s2_y = p3.y - p2.y;
    float s;
    float t;
    float divisor;

    divisor = (-s2_x * s1_y + s1_x * s2_y);
    if (divisor == 0)
        return NULL;
    s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / divisor;
    t = ( s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / divisor;
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        return alloc_v2f(p0.y + (t * s1_y), p0.y + (t * s1_y));
    return NULL;
}

sfVector2f *can_reach_player(sfVector2f e_pos, sfVector2f vector, npc_t *player)
{
    sfFloatRect bounds = get_npc_hitbox(player);
    sfVector2f a0 = e_pos;
    sfVector2f a1 = {e_pos.x + vector.x, e_pos.y + vector.y};
    sfVector2f b0[2] = {
        {bounds.left, bounds.top},
        {bounds.left + bounds.width, bounds.top + bounds.height}
    };
    sfVector2f b1[2] = {
        {bounds.left, bounds.top + bounds.height},
        {bounds.left + bounds.width, bounds.top}
    };
    sfVector2f *inter;

    if ((inter = is_intersect(a0, a1, b0[0], b1[1])) ||
        (inter = is_intersect(a0, a1, b0[0], b1[0])) ||
        (inter = is_intersect(a0, a1, b0[1], b1[0])) ||
        (inter = is_intersect(a0, a1, b0[1], b1[1])))
        return inter;
    return NULL;
}

void rotate_vector(sfVector2f *vec, float degree)
{
    sfVector2f new;

    degree = deg_to_rad(degree);
    new.x = cos(degree) * vec->x - sin(degree) * vec->y;
    new.y = sin(degree) * vec->x + cos(degree) * vec->y;
    vec->x = new.x;
    vec->y = new.y;
}

sfVector2f get_vision_vector(float const vis_dist, int const dir)
{
    sfVector2f vision = {0, 0};

    if (dir == LEFT)
        vision.x = -vis_dist;
    if (dir == RIGHT)
        vision.x = vis_dist;
    if (dir == UP)
        vision.y = -vis_dist;
    if (dir == DOWN || dir == IDLE)
        vision.y = vis_dist;
    rotate_vector(&vision, -VISION_ANGLE / 2.0);
    return vision;
}

int can_rush(enemy_t *e, ray_c *data, npc_t *player)
{
    float const vision_distance = data->cell * 4;
    float const increment = VISION_ANGLE / NB_RAY;
    sfVector2f e_pos = sfSprite_getPosition(e->enemy->sprite);
    sfVector2f vector = get_vision_vector(vision_distance, e->enemy->dir);
    sfVector2f *inter;

    for (int i = 0; i < NB_RAY; i++) {
        if ((inter = can_reach_player(e_pos, vector, player))) {
            free(inter);
            return 1;
        }
        rotate_vector(&vector, increment);
    }
    return 0;
}

float dist_between(sfSprite *a, sfSprite *b)
{
    sfVector2f pa = sfSprite_getPosition(a);
    sfVector2f pb = sfSprite_getPosition(b);
    float dist_x = fabs(pa.x - pb.x);
    float dist_y = fabs(pa.y - pb.y);

    return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

void cancel_rush_of(enemy_t *e, ray_c *data, level_t *l)
{
    sfVector2f vectors[4] = {
        {-data->cell / 2.0, 0}, {data->cell / 2.0, 0},
        {0, -data->cell / 2.0}, {0, data->cell / 2.0}
    };

    e->is_in_rush = 0;
    e->enemy->speed /= SPEED_ACC;
    if (!is_pnj_colliding(data, e->enemy, l))
        return;
    for (int i = 0; i < 4; i++) {
        if (i)
            sfSprite_move(e->enemy->sprite,
            (sfVector2f){-vectors[i - 1].x, -vectors[i - 1].y});
        sfSprite_move(e->enemy->sprite, vectors[i]);
        if (!is_pnj_colliding(data, e->enemy, l))
            return;
    }
}

void check_null_vector(enemy_t *e, sfSprite *player, window_t *win, level_t *l)
{
    ray_c *data = win->menus[LIGHT];
    sfClock_restart(e->decide_clock);
    if (dist_between(e->enemy->sprite, player) < data->cell / 2.0)
        launch_combat();
    e->goal = sfSprite_getPosition(player);
    update_path(e, l, data);
    e->mov_vector = vector_to_objective(e, l, data, win_size(win));
    if (!(e->mov_vector.x || e->mov_vector.y))
        cancel_rush_of(e, data, l);
}

void move_enemy_along(enemy_t *enemy,
sfVector2u graph_max, float cell, sfVector2u old)
{
    float x_inc = enemy->mov_vector.x / 10.0;
    float y_inc = enemy->mov_vector.y / 10.0;
    sfVector2u new;

    for (int i = 0; i < 10; i++) {
        sfSprite_move(enemy->enemy->sprite, (sfVector2f){x_inc, y_inc});
        new = get_logic_pos(enemy, graph_max, cell);
        if (new.x != old.x || new.y != old.y) {
            enemy->map[old.x][old.y] = 0;
            return;
        }
    }
}

void rush_to_player(enemy_t *e, level_t *l, window_t *win, sfSprite *player)
{
    ray_c *data = win->menus[LIGHT];
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u old = get_logic_pos(e, graph_max, data->cell);

    e->mov_vector = vector_to_objective(e, l, data, win_size(win));
    if ((e->mov_vector.x == 0 && e->mov_vector.y == 0) ||
    sfClock_getElapsedTime(e->decide_clock).microseconds > 500000)
        check_null_vector(e, player, win, l);
    if (sfClock_getElapsedTime(e->enemy->move_clock).microseconds > 33333) {
        sfClock_restart(e->enemy->move_clock);
        e->enemy->dir = dir_from_v2f(e->mov_vector);
        move_enemy_along(e, graph_max, data->cell, old);
    }
}
