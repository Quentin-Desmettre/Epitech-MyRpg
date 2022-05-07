/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rush_to_player.c
*/

#include "rpg.h"

void move_enemy_v2f(enemy_t *e, sfVector2f vector)
{
    sfSprite_move(e->enemy->sprite, vector);
    move_splash_particles(e->splash, vector);
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
    game_t *g = window(NULL)->menus[GAME];
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
            move_enemy_v2f(e,
            (sfVector2f){-vectors[i - 1].x, -vectors[i - 1].y});
        move_enemy_v2f(e, vectors[i]);
        if (!is_pnj_colliding(data, e->enemy, l) &&
        !is_on_water(e->enemy, g->items, g->inventory->items_sprite[2]))
            return;
    }
}

void check_null_vector(enemy_t *e, sfSprite *player, window_t *win, level_t *l)
{
    ray_c *data = win->menus[LIGHT];
    game_t *g = win->menus[GAME];

    restart_clock(e->decide_clock);
    if (dist_between(e->enemy->sprite, player) < data->cell / 2.0)
        launch_combat(win);
    e->mov_vector = vector_to_objective(e, g, data, win_size(win));
    if (!(e->mov_vector.x || e->mov_vector.y)) {
        if (!other_are_rushing(g->enemies, e) && g->rush_music)
            sfMusic_stop(g->rush_music);
        cancel_rush_of(e, data, l);
    }
}

void rush_to_player(enemy_t *e, level_t *l, window_t *win, sfSprite *player)
{
    ray_c *data = win->menus[LIGHT];

    e->mov_vector = vector_to_objective(e, GET_GAME(win), data, win_size(win));
    if ((e->mov_vector.x == 0 && e->mov_vector.y == 0) ||
    get_elapsed_time(e->decide_clock) > 500000)
        check_null_vector(e, player, win, l);
    if (get_elapsed_time(e->enemy->move_clock) > 33333) {
        restart_clock(e->enemy->move_clock);
        e->enemy->dir = dir_from_v2f(e->mov_vector);
        sfSprite_move(e->enemy->sprite, e->mov_vector);
        move_splash_particles(e->splash, e->mov_vector);
    }
}
