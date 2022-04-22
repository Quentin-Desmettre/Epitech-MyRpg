/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "rpg.h"

void change_form(game_t *game, sfVector2u size_win, sfVector2i tmp, ray_c *data)
{
    sfSprite_setScale(game->player->sprite, (sfVector2f){1.2 / 1080 * size_win.y
    ,  1.2 / 1080 * size_win.y});
    data->offset = (size_win.x - ((size_win.y) / 600.0 * 800.0)) / 2.0;
    if (tmp.y > size_win.y && -data->off_view.y < size_win.y)
        data->off_view.y -= 5;
    else if (tmp.y < size_win.y && -data->off_view.y > 0)
        data->off_view.y += 5;
    if (tmp.x > (int)(size_win.x) - data->offset * 2 && -data->off_view.x
    < (int)(size_win.x) - data->offset * 2)
        data->off_view.x -= 5;
    else if (tmp.x < (int)(size_win.x) - data->offset * 2 && -data->off_view.x >
    0)
        data->off_view.x += 5;
    data->off_view.y;
    data->cell = size_win.y / (15);
    sfSprite_setScale(data->floor, (sfVector2f){data->cell / 64, data->cell
    / 64});
    sfSprite_setScale(data->wall, (sfVector2f){data->cell / 64, data->cell
    / 128});
}