/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** enemy.c
*/

#include "rpg.h"
#include "player.h"

sfBool v2f_eq(sfVector2f a, sfVector2f b)
{
    return (a.x == b.x && a.y == b.y);
}

void update_enemy(enemy_t *en, sfVector2f pl_size)
{
    anim_npc(en->enemy);
    if (!v2f_eq(get_sprite_size(en->enemy->sprite), pl_size))
        set_sprite_size(en->enemy->sprite, pl_size);
}

void draw_enemy(ray_c *data, enemy_t *en, game_t *game)
{
    sfVector2f pos;

    sfRenderTexture_drawSprite(data->tex_light, en->enemy->sprite, NULL);
    pos = sfSprite_getPosition(en->enemy->sprite);
    add_light(data, (sfVector2i){pos.x, pos.y}, 0, game->rtex);
}

void draw_enemies(game_t *game, ray_c *data)
{
    list_t *list = game->enemies;
    list_t const * const begin = game->enemies;
    sfVector2f pl_size = get_sprite_size(game->player->sprite);

    if (!list)
        return;
    do {
        update_enemy(list->data, pl_size);
        draw_enemy(data, list->data, game);
        list = list->next;
    } while (list != begin);
}

sfVector2f rnd_point(game_t *g, ray_c *data, npc_t *npc)
{
    sfVector2f size = g->level->size;
    sfVector2u max = {(size.y + 1) * data->cell,
    (size.x + 1) * data->cell + data->cell / 2};
    sfVector2f map_pos;
    sfVector2f base_pos = sfSprite_getPosition(npc->sprite);

    npc->group = ENEMY_LOADING_GRP;
    do {
        map_pos.x = rand() % (max.x);
        map_pos.y = rand() % (max.y);
        sfSprite_setPosition(npc->sprite, map_pos);
    } while (is_pnj_colliding(data, npc, g->level));
    npc->group = ENEMY_GRP;
    sfSprite_setPosition(npc->sprite, base_pos);
    return map_pos;
}

void create_enemy(game_t *game, ray_c *data)
{
    enemy_t *enemy = malloc(sizeof(enemy_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    static const sfIntRect *pl_rects[5] = {
        pl_rect_top,
        pl_rect_down,
        pl_rect_left,
        pl_rect_right,
        pl_rect_idle
    };

    enemy->enemy = npc_create("tnicg", "./assets/party.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, ENEMY_GRP);
    sfSprite_setOrigin(enemy->enemy->sprite, (sfVector2f){32, 32});
    sfSprite_setPosition(enemy->enemy->sprite,
    rnd_point(game, data, enemy->enemy));
    enemy->goal_pos = rnd_point(game, data, enemy->enemy);
    enemy->enemy->dir = IDLE;
    enemy->goal_pos = (sfVector2f){0, 0};
    append_node(&game->enemies, enemy);
}
