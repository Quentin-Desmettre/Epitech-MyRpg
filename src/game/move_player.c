/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** move_player.c
*/

#include "rpg.h"
#include "player.h"

int dir_from_v2f(sfVector2f vf)
{
    int dir = IDLE;

    if (vf.y < 0)
        dir = UP;
    else if (vf.y > 0)
        dir = DOWN;
    if (vf.x < 0)
        dir = LEFT;
    else if (vf.x > 0)
        dir = RIGHT;
    return dir;
}

sfVector2f get_vector(void)
{
    sfVector2f movement = {0, 0};

    if (sfKeyboard_isKeyPressed(sfKeyZ))
        movement.y = -1;
    if (sfKeyboard_isKeyPressed(sfKeyS) && !sfKeyboard_isKeyPressed(sfKeyZ))
        movement.y = 1;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        movement.x = -1;
    if (sfKeyboard_isKeyPressed(sfKeyD) && !sfKeyboard_isKeyPressed(sfKeyQ))
        movement.x = 1;
    return movement;
}

void move_along_vector(game_t *game, sfVector2f movement, window_t *win)
{
    float x_step = movement.x / 10.0;
    float y_step = movement.y / 10.0;

    for (float x = 0, max = fabs(movement.x); fabs(x) < max; x += x_step) {
        sfSprite_move(game->player->sprite, (sfVector2f){x_step, 0});
        if (is_pnj_colliding(win->menus[LIGHT], game->player, game->level)) {
            sfSprite_move(game->player->sprite, (sfVector2f){-(x + x_step), 0});
            break;
        }
    }
    for (float y = 0, max = fabs(movement.y); fabs(y) < max; y += y_step) {
        sfSprite_move(game->player->sprite, (sfVector2f){0, y_step});
        if (is_pnj_colliding(win->menus[LIGHT], game->player, game->level)) {
            sfSprite_move(game->player->sprite, (sfVector2f){0, -(y + y_step)});
            break;
        }
    }
}

sfClock *update_vector(sfVector2f *vector, npc_t *npc, sfVector2f win_size)
{
    sfClock *last_time = npc->move_clock;
    float pl_speed = npc->speed;
    float factor = 1;

    if (!last_time)
        last_time = sfClock_create();
    factor = sfClock_getElapsedTime(last_time).microseconds / 10000.0;
    vector->x *= factor * (pl_speed * 0.1 + 1);
    vector->y *= factor * (pl_speed * 0.1 + 1);
    vector->x = vector->x / 1920.0 * win_size.x;
    vector->y = vector->y / 1080.0 * win_size.y;
    sfClock_restart(last_time);
    return last_time;
}

void move_pl(window_t *win)
{
    game_t *game = win->menus[GAME];
    sfVector2f movement = get_vector();

    update_vector(&movement, game->player, WIN_SIZE(win));
    move_along_vector(game, movement, win);
    game->player->dir = dir_from_v2f(movement);
}
