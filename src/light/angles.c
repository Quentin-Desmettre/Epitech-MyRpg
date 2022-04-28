/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/

#include <stdio.h>
#include "rpg.h"

void find_angle_n(int i, int j, int l, ray_c *data)
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

void find_angles(int i, int j, ray_c *data)
{
    if (data->map[i][j] != '1')
        return;
    for (int l = -1; l != 3; l += 2)
        find_angle_n(i, j, l, data);
}

void wall_light(ray_c *data)
{
    sfVector2f first = {18, 1000};
    sfVector2f center = {18, 9};

    for (float i = 0; i < 360; i += 2) {
        data->angles[data->light->index].coo = rotate(center, first, i);
        data->angles[data->light->index].is_triple = 0;
        data->light->index++;
    }
}

void set_wall(ray_c *data)
{
    data->wall_tex[0] =  sfTexture_createFromFile(
    "./assets/floor_wall/wall_lvl.png", 0);
    data->floor_tex[0] = sfTexture_createFromFile(
    "./assets/floor_wall/floor_lvl1.png", 0);
    data->wall_tex[1] =  sfTexture_createFromFile(
    "./assets/floor_wall/concrete_wall.png", 0);
    data->floor_tex[1] = sfTexture_createFromFile(
    "./assets/floor_wall/concrete_floor.png", 0);
    data->wall_tex[2] =  sfTexture_createFromFile(
    "./assets/floor_wall/wall_office.png", 0);
    data->floor_tex[2] = sfTexture_createFromFile(
    "./assets/floor_wall/floor_office.png", 0);
}
