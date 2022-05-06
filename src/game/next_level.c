/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"
#include "player.h"

void set_level(window_t *win, int level)
{
    ray_c *data = win->menus[LIGHT];
    game_t *game = win->menus[GAME];

    if (level >= 2)
        return;
    data->lvl = level;
    game->quest->desc_qst[0] = desc_qst[data->lvl + 3];
    if (level != 0)
        data->noise = get_texture_by_name(BLUE_NOISE);
    else
        data->noise = get_texture_by_name(NOISE_PNG);
    sfSprite_setTexture(data->floor, data->floor_tex[data->lvl], 0);
    sfSprite_setTexture(data->noise_sp, data->noise, 0);
    sfSprite_setTexture(data->wall, data->wall_tex[data->lvl], 0);
}

void next_level(window_t *win)
{
    ray_c *data = win->menus[LIGHT];
    game_t *game = win->menus[GAME];

    if (data->lvl >= 2) {
        end_game(0);
        return;
    }
    add_xp(win->menus[GAME], 10 + (data->lvl == 1 ? 5 : 0));
    data->lvl++;
    game->quest->desc_qst[0] = desc_qst[data->lvl + 3];
    data->noise = get_texture_by_name(BLUE_NOISE);
    sfSprite_setTexture(data->floor, data->floor_tex[data->lvl], 0);
    sfSprite_setTexture(data->noise_sp, data->noise, 0);
    sfSprite_setTexture(data->wall, data->wall_tex[data->lvl], 0);
}
