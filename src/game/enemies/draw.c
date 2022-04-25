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

void check_vector_change(enemy_t *en, sfVector2f win_s)
{
    if (sfClock_getElapsedTime(en->decide_clock).microseconds > en->rnd_wait &&
    en->mov_vector.x == 0 && en->mov_vector.y == 0) {
        sfClock_restart(en->decide_clock);
        en->mov_vector = rand_dir();
        update_vector(&en->mov_vector, en->enemy, win_s);
        en->rnd_mve = my_rand(3000000, 5000000);
        en->rnd_wait = my_rand(1000000, 3000000);
    }
    if (sfClock_getElapsedTime(en->decide_clock).microseconds > en->rnd_mve) {
        en->mov_vector.x = 0;
        en->mov_vector.y = 0;
        sfClock_restart(en->decide_clock);
    }
}

void move_enemy(enemy_t *en, ray_c *data, game_t *g, window_t *win)
{
    level_t *l = g->level;

    if (dist_between(en->enemy->sprite, g->player->sprite) < data->cell / 2.0)
        launch_combat();
    if (check_rush(en, data, g, win))
        return;
    check_vector_change(en, win_size(win));
    if (sfClock_getElapsedTime(en->enemy->move_clock).microseconds > 33333 &&
    (en->mov_vector.x || en->mov_vector.y)) {
        sfSprite_move(en->enemy->sprite, en->mov_vector);
        sfClock_restart(en->enemy->move_clock);
        if (is_pnj_colliding(data, en->enemy, l)) {
            sfSprite_move(en->enemy->sprite,
            (sfVector2f){-en->mov_vector.x, -en->mov_vector.y});
            en->mov_vector = rotate_dir(en->mov_vector);
        }
        en->enemy->dir = dir_from_v2f(en->mov_vector);
    }
}

void update_enemy(enemy_t *en, sfVector2f pl_size, ray_c *data, window_t *win)
{
    move_enemy(en, data, win->menus[GAME], win);
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

void draw_enemies(game_t *game, ray_c *data, window_t *win)
{
    list_t *list = game->enemies;
    list_t const * const begin = game->enemies;
    sfVector2f pl_size = get_sprite_size(game->player->sprite);

    if (!list)
        return;
    do {
        if (!game->is_flashing)
            update_enemy(list->data, pl_size, data, win);
        sfRenderTexture_drawSprite(data->tex_light,
        ((enemy_t *)(list->data))->enemy->sprite, NULL);
        list = list->next;
    } while (list != begin);
}
