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
    data->noise = get_texture_by_name(BLUE_NOISE);
    sfSprite_setTexture(data->floor, data->floor_tex[data->lvl], 0);
    sfSprite_setTexture(data->noise_sp, data->noise, 0);
    sfSprite_setTexture(data->wall, data->wall_tex[data->lvl], 0);
}
