/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"

float side_solid(sfFloatRect rect, fight_t *fight, int left)
{
    sfFloatRect rect2;

    for (int i = 0; i < 20; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(fight->solid[i]);
        if (sfFloatRect_intersects(&rect, &rect2, NULL) && i != 0)
            return (left == 1 ? rect2.left + 200 : rect2.left - rect.width);
        if (sfFloatRect_intersects(&rect, &rect2, NULL) && i == 0)
            return (left == 1 ? rect2.left + 500 : rect2.left - rect.width);
    }
    return (-1);
}

float up_solid(sfFloatRect rect, fight_t *fight, int top)
{
    sfFloatRect rect2;

    for (int i = 0; i < 20; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(fight->solid[i]);
        if (sfFloatRect_intersects(&rect, &rect2, NULL))
            return (top == 1 ? rect2.top + 100 : rect2.top - rect.height);
    }
    return (-1);
}

void dmg_pl(fight_t *fight, window_t *win, sfFloatRect rect, float time)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t info = c->saves[c->primary]->infos;
    ray_c *data = win->menus[LIGHT];

    if (touch_dmg(rect, fight) == 1) {
        c->saves[c->primary]->infos.health_percent -= (0.15 + 0.15 * ((30.0 -
        info.defense) / 30.0) + 0.15 * (data->lvl / 3.0)) * time;
        if (c->saves[c->primary]->infos.health_percent <= 0)
            end_game(1);
    }
}
