/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "rpg.h"

void side_move_cam(float speed, sfVector2i tmp,
ray_c *data, sfVector2u size_win)
{
    if (tmp.x < -data->off_view.x + (int)size_win.x / 2) {
        data->off_view.x += speed;
        if (tmp.x > -data->off_view.x + (int)size_win.x / 2)
            data->off_view.x = -tmp.x + (int)size_win.x / 2;
    } else if (tmp.x > -data->off_view.x + (size_win.x / 2)) {
        data->off_view.x -= speed;
        data->off_view.x = (tmp.x < -data->off_view.x + (int)size_win.x / 2) ?
        -tmp.x + (int)size_win.x / 2 : data->off_view.x;
    }

    if (data->off_view.x > 0)
        data->off_view.x = 0;
    if (-data->off_view.x > 40 * data->cell - size_win.x)
        data->off_view.x = -(40 * data->cell - size_win.x);
}

void move_cam(game_t *game, sfVector2u size_win, sfVector2i tmp, ray_c *data)
{
    float factor = get_elapsed_time(data->time) / 10000.0;
    sfSprite_setScale(game->player->sprite, (sfVector2f){1.2 / 1080 * size_win.y
    , 1.2 / 1080 * size_win.y});
    float speed = factor * (game->player->speed * 0.2 + 1);

    if (tmp.y < -data->off_view.y + (int)size_win.y / 2) {
        data->off_view.y += speed;
        if (tmp.y > -data->off_view.y + (int)size_win.y / 2)
            data->off_view.y = -tmp.y + (int)size_win.y / 2;
    } else if (tmp.y > -data->off_view.y + (int)size_win.y / 2) {
        data->off_view.y -= speed;
        data->off_view.y = (tmp.y < -data->off_view.y + (int)size_win.y / 2) ?
        -tmp.y + (int)size_win.y / 2 : data->off_view.y;
    }
    if (data->off_view.y > 0)
        data->off_view.y = 0;
    if (-data->off_view.y > size_win.y)
        data->off_view.y = -(int)(size_win.y);
    side_move_cam(speed, tmp, data, size_win);
    restart_clock(data->time);
}

void change_form(game_t *game, sfVector2u size_win, sfVector2i tmp, ray_c *data)
{
    data->cell = size_win.y / (15);
    sfSprite_setScale(data->floor, (sfVector2f){data->cell / 64, data->cell
    / 64});
    sfSprite_setScale(data->wall, (sfVector2f){data->cell / 64, data->cell
    / 128});
    move_cam(game, size_win, tmp, data);
}

void change_room_y(game_t *game, ray_c *data, sfVector2f pos)
{
    if (pos.y < 0) {
        pos.y = (game->level->size.x + 2) * data->cell - data->cell * 1.5;
        data->off_view.y = -pos.y;
        sfSprite_setPosition(game->player->sprite, pos);
        new_room(game, data);
    } else if ((game->level->size.y + 2) * data->cell < pos.x) {
        pos.x = data->cell * 1.5;
        data->off_view.x = -pos.x + 500;
        sfSprite_setPosition(game->player->sprite, pos);
        new_room(game, data);
    }
}

void change_room(game_t *game, ray_c *data, sfVector2f pos)
{
    if (pos.x < 0) {
        pos.x = (game->level->size.y + 2) * data->cell - data->cell * 1.5;
        data->off_view.x = -pos.x;
        sfSprite_setPosition(game->player->sprite, pos);
        new_room(game, data);
    } else if ((game->level->size.x + 2) * data->cell < pos.y) {
        pos.y = data->cell * 1.5;
        data->off_view.y = -pos.y + 500;
        sfSprite_setPosition(game->player->sprite, pos);
        new_room(game, data);
    }
    change_room_y(game, data, pos);
}
