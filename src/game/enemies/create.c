/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "player.h"

static int **wa_to_ia(game_t *game, sfVector2u rs)
{
    int **ia = malloc(sizeof(int *) * rs.y);

    for (unsigned line = 0; line < rs.y; line++) {
        ia[line] = malloc(sizeof(int) * rs.x);
        for (unsigned col = 0; col < rs.x; col++) {
            ia[line][col] = ((game->level->room[line / 2][col / 2] == 'X') ||
            (game->level->room[(line - 1) / 2][col / 2] == 'X')) ? -1 : 0;
        }
    }
    return ia;
}

static sfVector2f obj_to_v2f(int dir)
{
    sfVector2f dirs[4] = {
        {0, -1}, {0, 1},
        {-1, 0}, {1, 0}
    };
    if (dir < 0 || dir > 3)
        return (sfVector2f){0, 0};
    return dirs[dir];
}

sfVector2f vector_to_objective(enemy_t *e, level_t *l,
ray_c *data, sfVector2f win_s)
{
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u pos = get_logic_pos(e, graph_max, data->cell);
    sfVector2u positions[4] = {
        {pos.x - 1, pos.y}, {pos.x + 1, pos.y},
        {pos.x, pos.y - 1}, {pos.x, pos.y + 1}
    };
    int dir = -1;
    sfVector2f tmp;

    for (int i = 0; i < 4; i++) {
        if (positions[i].x < graph_max.y && positions[i].y < graph_max.x &&
        e->map[positions[i].x][positions[i].y] == -2) {
            dir = i;
        }
    }
    tmp = obj_to_v2f(dir);
    update_vector(&tmp, e->enemy, win_s);
    return tmp;
}

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

    en->enemy = npc_create("tnicgv", "./assets/party.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, ENEMY_GRP, 2);
    sfSprite_setOrigin(en->enemy->sprite, (sfVector2f){32, 32});
    sfSprite_setPosition(en->enemy->sprite, rnd_point(game, data, en->enemy));
    en->enemy->dir = IDLE;
    en->decide_clock = sfClock_create();
    en->mov_vector = rand_dir();
    en->rnd_mve = my_rand(3000000, 5000000);
    en->rnd_wait = my_rand(1000000, 3000000);
    en->is_in_rush = 0;
    en->size = (sfVector2u){(game->level->size.y + 2) * 2,
    (game->level->size.x + 2) * 2};
    en->map = wa_to_ia(game, en->size);
    append_node(&game->enemies, en);
}
