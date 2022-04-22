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
    if (tmp.x < -data->off_view.x + (int)size_win.x / 2 - data->offset) {
        data->off_view.x += speed;
        if (tmp.x > -data->off_view.x + (int)size_win.x / 2 - data->offset)
            data->off_view.x = -tmp.x + (int)size_win.x / 2 - data->offset;
    } else if (tmp.x > -data->off_view.x + (size_win.x / 2) - data->offset) {
        data->off_view.x -= speed;
        if (tmp.x < -data->off_view.x + (int)size_win.x / 2 - data->offset)
            data->off_view.x = -tmp.x + (int)size_win.x / 2 - data->offset;
    }
}

void move_cam(game_t *game, sfVector2u size_win, sfVector2i tmp, ray_c *data)
{
    int factor = sfClock_getElapsedTime(data->time).microseconds / 10000.0;
    sfSprite_setScale(game->player->sprite, (sfVector2f){1.2 / 1080 * size_win.y
    , 1.2 / 1080 * size_win.y});
    float speed = factor * (game->player->speed * 0.1 + 1);

    if (tmp.y < -data->off_view.y + (int)size_win.y / 2) {
        data->off_view.y += speed;
        if (tmp.y > -data->off_view.y + (int)size_win.y / 2)
            data->off_view.y = -tmp.y + (int)size_win.y / 2;
    } else if (tmp.y > -data->off_view.y + (int)size_win.y / 2) {
        data->off_view.y -= speed;
        if (tmp.y < -data->off_view.y + (int)size_win.y / 2)
            data->off_view.y = -tmp.y + (int)size_win.y / 2;
    }
    side_move_cam(speed, tmp, data, size_win);
    sfClock_restart(data->time);
}

void change_form(game_t *game, sfVector2u size_win, sfVector2i tmp, ray_c *data)
{
    data->offset = (size_win.x - ((size_win.y) / 600.0 * 800.0)) / 2.0;
    data->cell = size_win.y / (15);
    sfSprite_setScale(data->floor, (sfVector2f){data->cell / 64, data->cell
    / 64});
    sfSprite_setScale(data->wall, (sfVector2f){data->cell / 64, data->cell
    / 128});
    move_cam(game, size_win, tmp, data);
}
