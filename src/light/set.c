/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "light.h"

void find_angles(int i, int j, all_t *data)
{
    if (data->map[i][j] != '1')
        return;
    for (int l = -1; l != 3; l += 2) {
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
            new->map[i][j] = (map->level->room[j][i] == 'X') ? '1' : '0';
        new->map[i][MAP_H] = '\0';
    }
    new->map[MAP_S] = 0;
    new->img_rpg = sfImage_createFromFile("./ground.png");
    new->state.shader = 0;
    new->state.blendMode = sfBlendAlpha;
    new->state.transform = sfTransform_Identity;
    set_light(new);
    return 1;
}
