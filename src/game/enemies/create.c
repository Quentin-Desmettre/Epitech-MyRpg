/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "player.h"

sfVector2f rnd_point(game_t *g, ray_c *data, npc_t *npc)
{
    sfVector2f size = g->level->size;
    sfVector2u max = {(size.y + 1) * data->cell,
    (size.x + 1) * data->cell + data->cell / 2};
    sfVector2f map_pos;
    sfVector2f base_pos = sfSprite_getPosition(npc->sprite);

    do {
        map_pos.x = my_rand(data->cell, max.x);
        map_pos.y = my_rand(data->cell, max.y);
        sfSprite_setPosition(npc->sprite, map_pos);
    } while (is_pnj_colliding(data, npc, g->level));
    sfSprite_setPosition(npc->sprite, base_pos);
    return map_pos;
}

void create_enemy(game_t *game, ray_c *data)
{
    enemy_t *en = malloc(sizeof(enemy_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    static const sfIntRect *pl_rects[5] = {
        pl_rect_top, pl_rect_down, pl_rect_left, pl_rect_right, pl_rect_idle
    };

    en->enemy = npc_create("tnicg", "./assets/party.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, ENEMY_GRP);
    sfSprite_setOrigin(en->enemy->sprite, (sfVector2f){32, 32});
    sfSprite_setPosition(en->enemy->sprite, rnd_point(game, data, en->enemy));
    en->enemy->dir = IDLE;
    en->decide_clock = sfClock_create();
    en->mov_vector = rand_dir();
    en->rnd_mve = my_rand(3000000, 5000000);
    en->rnd_wait = my_rand(1000000, 3000000);
    en->is_in_rush = 0;
    append_node(&game->enemies, en);
}
