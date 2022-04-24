/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw.c
*/

#include "rpg.h"
#include "player.h"

sfVector2f rotate_dir(sfVector2f base)
{
    if (base.y) {
        base.y = 0;
        base.x = rand() % 2 ? -1 : 1;
    } else {
        base.x = 0;
        base.y = rand() % 2 ? -1 : 1;
    }
    return base;
}

void check_vector_change(enemy_t *en)
{
    if (sfClock_getElapsedTime(en->decide_clock).microseconds > en->rnd_wait &&
    en->mov_vector.x == 0 && en->mov_vector.y == 0) {
        sfClock_restart(en->decide_clock);
        en->mov_vector = rand_dir();
        en->rnd_mve = my_rand(3000000, 5000000);
        en->rnd_wait = my_rand(1000000, 3000000);
    }
    if (sfClock_getElapsedTime(en->decide_clock).microseconds > en->rnd_mve) {
        en->mov_vector.x = 0;
        en->mov_vector.y = 0;
        sfClock_restart(en->decide_clock);
    }
}

void move_enemy(enemy_t *en, ray_c *data, game_t *g)
{
    level_t *l = g->level;

    if (en->is_in_rush)
        return rush_to_player(en, g->level, data, g->player->sprite);
    check_vector_change(en);
    if (sfClock_getElapsedTime(en->enemy->move_clock).microseconds > 33333 &&
    (en->mov_vector.x || en->mov_vector.y)) {
        sfSprite_move(en->enemy->sprite, en->mov_vector);
        if (is_pnj_colliding(data, en->enemy, l)) {
            sfSprite_move(en->enemy->sprite,
            (sfVector2f){-en->mov_vector.x, -en->mov_vector.y});
            en->mov_vector = rotate_dir(en->mov_vector);
        }
        en->enemy->dir = dir_from_v2f(en->mov_vector);
    }
}

void update_enemy(enemy_t *en, sfVector2f pl_size, ray_c *data, game_t *game)
{
    move_enemy(en, data, game);
    if (en->mov_vector.x || en->mov_vector.y)
        anim_npc(en->enemy);
    else {
        en->enemy->frame = 0;
        sfSprite_setTextureRect(en->enemy->sprite,
        en->enemy->rects[en->enemy->dir][0]);
    }
    if (!V2F_EQ(get_sprite_size(en->enemy->sprite), pl_size))
        set_sprite_size(en->enemy->sprite, pl_size);
}

void draw_enemies(game_t *game, ray_c *data)
{
    list_t *list = game->enemies;
    list_t const * const begin = game->enemies;
    sfVector2f pl_size = get_sprite_size(game->player->sprite);

    if (!list)
        return;
    do {
        update_enemy(list->data, pl_size, data, game);
        sfRenderTexture_drawSprite(data->tex_light,
        ((enemy_t *)(list->data))->enemy->sprite, NULL);
        // sfVector2f pos = sfSprite_getPosition(((enemy_t *)(list->data))->enemy->sprite);
        // add_light(data, (sfVector2i){pos.x, pos.y}, 5, game->rtex);
        list = list->next;
    } while (list != begin);
}
