/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/

#include <stdio.h>
#include "rpg.h"

void set_light(ray_c *data)
{
    data->state.shader = 0;
    data->state.blendMode = sfBlendAlpha;
    data->state.transform = sfTransform_Identity;
    data->light->array = sfVertexArray_create();
    data->light->circle = sfCircleShape_create();
    data->light->vertex.color = sfWhite;
    sfCircleShape_setFillColor(data->light->circle, sfRed);
    sfCircleShape_setRadius(data->light->circle, 12.5);
    sfCircleShape_setOrigin(data->light->circle, (sfVector2f){12.5, 12.5});
    sfVertexArray_setPrimitiveType(data->light->array, sfTriangleFan);
    data->angles = malloc(sizeof(dir_t) * MAP_S * MAP_S);
    data->buffer = malloc(sizeof(dir_t) * MAP_S * MAP_S);
    data->light->index = 0;
    for (int i = 0; i < MAP_S; i++)
        for (int j = 0; j < MAP_H; j++)
            find_angles(i, j, data);
    wall_light(data);
}

void set_room_map(ray_c *data)
{
    data->tex_light = sfRenderTexture_create(1920 * 2, 1080 * 2, 0);
    data->wall_tex =  sfTexture_createFromFile(
    "./assets/floor_wall/wall_lvl.png", 0);
    data->floor_tex = sfTexture_createFromFile(
    "./assets/floor_wall/floor_lvl1.png", 0);
    data->floor = sfSprite_create();
    data->wall = sfSprite_create();
    sfSprite_setScale(data->wall, (sfVector2f){1, 0.5});
    data->noise_sp = sfSprite_create();
    data->noise = sfTexture_createFromFile("./assets/noise.png", 0);
    sfSprite_setTexture(data->noise_sp, data->noise, 0);
    sfSprite_setScale(data->noise_sp, (sfVector2f){2.75, 2.75});
    sfSprite_setColor(data->noise_sp, (sfColor){255, 255, 255, 20});
    sfSprite_setTexture(data->floor, data->floor_tex, 0);
    sfSprite_setTexture(data->wall, data->wall_tex, 0);
    data->off_view = (coo_t){0, 0};
}

char choose_item(int i, int j, char c, game_t *game)
{
    int random = rand() % 200;
    item_t *tmp = 0;

    if (c == 'X')
        return '1';
    if (random == 0) {
        tmp = malloc(sizeof(item_t));
        tmp->type = 0;
        tmp->pos = (coo_t){i, j};
        append_node(&game->items, tmp);
    }
    if (random == 1) {
        tmp = malloc(sizeof(item_t));
        tmp->type = 1;
        tmp->pos = (coo_t){i, j};
        append_node(&game->items, tmp);
    }
    return '0';
}

int set_game_light(ray_c *new, game_t *map)
{
    if (new == 0)
        return 0;
    new->map = malloc(sizeof(char *) * (MAP_S + 1));
    new->light = malloc(sizeof(light_t));
    if (new->map == 0 || new->light == 0)
        return 0;
    for (int i = 0; i < MAP_S; i++) {
        new->map[i] = malloc(sizeof(char) * (MAP_H + 1));
        if (new->map[i] == 0)
            return 0;
        for (int j = 0; j < MAP_H; j++)
            new->map[i][j] = '0';
        new->map[i][MAP_H] = '\0';
    }
    for (int i = 0; i < map->level->size.y + 2; i++)
        for (int j = 0; j < map->level->size.x + 2; j++)
            new->map[i][j] = choose_item(i, j, map->level->room[j][i], map);
    new->map[MAP_S] = 0;
    set_light(new);
    set_room_map(new);
    return 1;
}

void dest_light(ray_c *data)
{
    sfVertexArray_destroy(data->light->array);
    sfCircleShape_destroy(data->light->circle);
    sfSprite_destroy(data->floor);
    sfSprite_destroy(data->wall);
    sfTexture_destroy(data->floor_tex);
    sfTexture_destroy(data->noise);
    sfSprite_destroy(data->noise_sp);
    sfTexture_destroy(data->wall_tex);
    for (int i = 0; data->map[i] != 0; i++)
        free(data->map[i]);
    free(data->map);
    free(data->angles);
    free(data->buffer);
    free(data->light);
    free(data);
}