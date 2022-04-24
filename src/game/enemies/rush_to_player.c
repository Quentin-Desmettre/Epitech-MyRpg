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
    float dist = sqrt(pow(dist_x, 2) + pow(dist_y, 2));

    return dist;
}

void cancel_rush_of(enemy_t *e, ray_c *data, level_t *l)
{
    e->is_in_rush = 0;
    sfVector2f vectors[4] = {
        {-data->cell / 2.0, 0}, {data->cell / 2.0, 0},
        {0, -data->cell / 2.0}, {0, data->cell / 2.0}
    };
    for (int i = 0; i < 4; i++) {
        if (i)
            sfSprite_move(e->enemy->sprite,
            (sfVector2f){-vectors[i - 1].x, -vectors[i - 1].y});
        sfSprite_move(e->enemy->sprite, vectors[i]);
        if (!is_pnj_colliding(data, e->enemy, l))
            break;
    }
}

void check_null_vector(enemy_t *e, sfSprite *player, ray_c *data, level_t *l)
{
    sfClock_restart(e->decide_clock);
    if (dist_between(e->enemy->sprite, player) < data->cell / 2.0) {
        printf("HEHEHEHA\n");
        sfSleep((sfTime){500000});
        exit(0);
    }
    e->goal = sfSprite_getPosition(player);
    update_path(e, l, data);
    e->mov_vector = vector_to_objective(e, l, data);
    if (!(e->mov_vector.x || e->mov_vector.y))
        cancel_rush_of(e, data, l);
}

void rush_to_player(enemy_t *e, level_t *l, ray_c *data, sfSprite *player)
{
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u old = get_logic_pos(e, graph_max, data->cell);
    sfVector2u new;

    e->mov_vector = vector_to_objective(e, l, data);
    if ((e->mov_vector.x == 0 && e->mov_vector.y == 0) ||
    sfClock_getElapsedTime(e->decide_clock).microseconds > 500000)
        check_null_vector(e, player, data, l);
    if (sfClock_getElapsedTime(e->enemy->move_clock).microseconds > 33333) {
        sfClock_restart(e->enemy->move_clock);
        e->enemy->dir = dir_from_v2f(e->mov_vector);
        sfSprite_move(e->enemy->sprite, e->mov_vector);
        new = get_logic_pos(e, graph_max, data->cell);
        if (new.x != old.x || new.y != old.y)
            e->map[old.x][old.y] = 0;
    }
}
