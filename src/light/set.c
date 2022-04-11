/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "rpg.h"

void find_angle_n(int i, int j, int l, all_t *data)
{
    for (int k = -1; k != 3; k += 2) {
        if (i + l < MAP_S && i + l >= 0 && j + k < MAP_H && j + k >= 0 &&
        data->map[i + l][j] == data->map[i][j + k]) {
            data->angles[data->light->index].coo = (sfVector2f)
            {(i + (l == 1)), (j + (k == 1))};
            data->angles[data->light->index].is_triple = 1;
            data->light->index++;
        }
    }
}

void find_angles(int i, int j, all_t *data)
{
    if (data->map[i][j] != '1')
        return;
    for (int l = -1; l != 3; l += 2)
        find_angle_n(i, j, l, data);
}

void wall_light(all_t *data)
{
    sfVector2f first = {18, 1000};
    sfVector2f center = {18, 9};

    for (float i = 0; i < 360; i += 2) {
        data->angles[data->light->index].coo = rotate(center, first, i);
        data->angles[data->light->index].is_triple = 0;
        data->light->index++;
    }
}

void set_light(all_t *data)
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

void set_room_map(all_t *data)
{
    data->tex_light = sfRenderTexture_create(1920, 1080, 0);
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
    sfSprite_setScale(data->noise_sp, (sfVector2f){1.875, 1.875});
    sfSprite_setColor(data->noise_sp, (sfColor){255, 255, 255, 20});
    sfSprite_setTexture(data->floor, data->floor_tex, 0);
    sfSprite_setTexture(data->wall, data->wall_tex, 0);
}

int set_game_light(all_t *new, game_t *map)
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
            new->map[i][j] = (map->level->room[j][i] == 'X') ? '1' : '0';
    new->map[MAP_S] = 0;
    set_light(new);
    set_room_map(new);
    return 1;
}
