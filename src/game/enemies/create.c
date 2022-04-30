/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "player.h"

void destroy_enemy(void *enemy)
{
    enemy_t *e = enemy;
    destroy_clock(e->decide_clock);
    destroy_npc(e->enemy);
    for (unsigned i = 0; i < e->size.y; i++)
        free(e->map[i]);
    free(e->map);
    destroy_splash_particles(e->splash);
    free(e);
}

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

static sfVector2f rnd_point(game_t *g, ray_c *data, npc_t *npc)
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

static void init_enemy_movement(enemy_t *en, game_t *game, ray_c *data)
{
    en->enemy->dir = IDLE;
    en->decide_clock = create_clock();
    en->mov_vector = rand_dir();
    update_vector(&en->mov_vector, en->enemy, (sfVector2f){0, data->cell * 15});
    en->rnd_mve = my_rand(3000000, 5000000);
    en->rnd_wait = my_rand(1000000, 3000000);
    en->is_in_rush = 0;
    en->size = (sfVector2u){(game->level->size.y + 2) * 2,
    (game->level->size.x + 2) * 2};
    en->map = wa_to_ia(game, en->size);
}

void create_enemy(game_t *game, ray_c *data)
{
    enemy_t *en = malloc(sizeof(enemy_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    const sfIntRect *pl_rects[5] = {pl_rect_top, pl_rect_down, pl_rect_left,
    pl_rect_right, pl_rect_idle};
    sfVector2f pos;
    sfFloatRect rect;

    en->enemy = npc_create("tnicgv", "./assets/party.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, ENEMY_GRP, -6);
    sfSprite_setOrigin(en->enemy->sprite, (sfVector2f){32, 32});
    pos = rnd_point(game, data, en->enemy);
    sfSprite_setPosition(en->enemy->sprite, pos);
    rect = get_npc_hitbox(en->enemy);
    en->splash = create_splash_particles((sfVector2f){pos.x,
    pos.y + data->cell * 0.45}, (sfVector2f){rect.height * 0.1,
    rect.height * 0.1}, max_dur_splash);
    init_enemy_movement(en, game, data);
    append_node(&game->enemies, en);
}
