/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rush_to_player.c
*/

#include "rpg.h"

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
    e->enemy->speed -= SPEED_ACC;
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
        move_splash_particles(enemy->splash, (sfVector2f){x_inc, y_inc});
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
