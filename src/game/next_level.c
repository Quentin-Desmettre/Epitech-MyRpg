/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"
#include "player.h"

void next_level(ray_c *data)
{
    if (data->lvl >= 2)
        return;
    data->lvl++;
    sfTexture_destroy(data->noise);
    data->noise = sfTexture_createFromFile("assets/noise_b.png", 0);
    sfSprite_setTexture(data->floor, data->floor_tex[data->lvl], 0);
    sfSprite_setTexture(data->noise_sp, data->noise, 0);
    sfSprite_setTexture(data->wall, data->wall_tex[data->lvl], 0);
}
