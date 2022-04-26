/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "rpg.h"

void draw_wall(ray_c *data, int i, int j, game_t *game)
{
    coo_t size = game->level->size;

    if (data->map[i][j] != '1') {
        sfSprite_setPosition(data->floor, (coo_t){i * data->cell, j * data->
        cell + data->cell / 2});
        return sfRenderTexture_drawSprite(data->tex_light, data->floor, 0);
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

void draw_items(game_t *game, ray_c *data, sfVector2u size_win)
{
    list_t *tmp = game->items;

    sfSprite_setScale(game->inventory->items_sprite[0]
    , (sfVector2f){0.5 / 1080 * size_win.y, 0.5 / 1080 * size_win.y});
    sfSprite_setScale(game->inventory->items_sprite[1]
    , (sfVector2f){0.5 / 1080 * size_win.y, 0.5 / 1080 * size_win.y});
    if (tmp == NULL)
        return;
    do {
        sfSprite_setPosition(game->inventory->
        items_sprite[((item_t *)(tmp->data))->type], (coo_t){((item_t *)
        (tmp->data))->pos.x * data->cell + data->cell / 7.0,
        ((item_t *)(tmp->data))->pos.y * data->cell});
        sfRenderTexture_drawSprite(data->tex_light, game->inventory->
        items_sprite[((item_t *)(tmp->data))->type], 0);
        tmp = tmp->next;
    } while (tmp != game->items);
}

void draw_room(ray_c *data, game_t *game, window_t *win)
{
    sfVector2u size_win = sfRenderWindow_getSize(win->win);
    coo_t size = game->level->size;

    sfRenderTexture_clear(data->tex_light, sfBlack);
    for (int i = 0; i < size.y + 2; i++) {
        for (int j = 0; j < size.x + 2; j++) {
            draw_wall(data, i, j, game);
        }
    }
    sfRenderTexture_drawSprite(data->tex_light, data->noise_sp, 0);
    draw_items(game, data, size_win);
    if (win->state == GAME)
        sfRenderTexture_drawSprite(data->tex_light, game->player->sprite, NULL);
    sfRenderTexture_display(data->tex_light);
}
