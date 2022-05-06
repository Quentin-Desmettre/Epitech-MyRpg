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
    if (movement.x && movement.y) {
        movement.x /= SQRT_2;
        movement.y /= SQRT_2;
    }
    return movement;
}

void move_along_vector(game_t *game, sfVector2f movement, window_t *win)
{
    float x_step = movement.x;
    float y_step = movement.y;

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

void update_vector(sfVector2f *vector, npc_t *npc, sfVector2f win_size)
{
    float pl_speed = npc->speed;

    vector->x *= (pl_speed * 0.4 + 4);
    vector->y *= (pl_speed * 0.4 + 4);
    vector->x *= win_size.y / 1080.0;
    vector->y *= win_size.y / 1080.0;
}

void move_pl(window_t *win)
{
    game_t *game = win->menus[GAME];
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t *infos = &c->saves[c->primary]->infos;
    sfVector2f movement = get_vector();

    if (get_elapsed_time(game->player->move_clock) > 33333) {
        update_path(game->path, game->level,
        win->menus[LIGHT], sfSprite_getPosition(game->player->sprite));
        restart_clock(game->player->move_clock);
        update_vector(&movement, game->player, win_size(win));
        move_along_vector(game, movement, win);
        game->player->dir = dir_from_v2f(movement);
    }
    if (get_elapsed_time(game->thirst_clock) > 2 SEC) {
        infos->thirst_percent -= THIRST / (float)(1 + infos->thirst_res / 5);
        restart_clock(game->thirst_clock);
        infos->thirst_percent < 0 ? infos->thirst_percent = 0 : 0;
        if (infos->thirst_percent == 0)
            infos->health_percent -= 5;
    }
}
