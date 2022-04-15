/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "rpg.h"
#define ABS(x) ((x) < 0 ? -(x) : (x))

void draw_wall(all_t *data, int i, int j, game_t *game)
{
    coo_t size = game->level->size;

    if (data->map[i][j] != '1') {
        sfSprite_setPosition(data->floor, (coo_t){i * data->cell, j * data->
        cell + data->cell / 2});
        sfRenderTexture_drawSprite(data->tex_light, data->floor, 0);
        return;
    }
    if (size.x + 2 > j + 1 && data->map[i][j + 1] != '1') {
        sfSprite_setTextureRect(data->wall, (sfIntRect){64, 0, 64, 64});
        if (size.y + 2 > i + 1 && data->map[i + 1][j] != '1')
            sfSprite_setTextureRect(data->wall, (sfIntRect){128, 0, 64, 64});
        if (0 < i - 1 && data->map[i - 1][j] != '1')
            sfSprite_setTextureRect(data->wall, (sfIntRect){0, 0, 64, 64});
        if (size.y + 2 > i + 1 && data->map[i + 1][j] != '1' && 0 < i - 1 &&
        data->map[i - 1][j] != '1')
            sfSprite_setTextureRect(data->wall, (sfIntRect){192, 0, 64, 64});
        sfSprite_setPosition(data->wall, (coo_t){i * data->cell, (j + 1) * data
        ->cell});
        sfRenderTexture_drawSprite(data->tex_light, data->wall, 0);
    }
}

void draw_room(all_t *data, game_t *game)
{
    coo_t size = game->level->size;
    sfRenderTexture_clear(data->tex_light, sfBlack);
    for (int i = 0; i < size.y + 2; i++) {
        for (int j = 0; j < size.x + 2; j++) {
            draw_wall(data, i, j, game);
        }
    }
    sfRenderTexture_drawSprite(data->tex_light, data->noise_sp, 0);
    sfRenderTexture_drawSprite(data->tex_light, game->player->sprite, NULL);
    sfRenderTexture_display(data->tex_light);
}