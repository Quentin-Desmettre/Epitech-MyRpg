/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/rpg.h"

const sfTexture *draw_fight(window_t *win)
{
    fight_t *fight = win->menus[FIGHT];

    sfRenderTexture_clear(fight->tex, sfBlack);
    move_pl_fight(fight);
    move_blocs(fight, fight->time, win->win);
    sfRenderTexture_drawRectangleShape(fight->tex, fight->player, NULL);
    for (int i = 0; i < DMG; i++)
        sfRenderTexture_drawRectangleShape(fight->tex, fight->dmg[i], NULL);
    for (int i = 0; i < 20; i++)
        sfRenderTexture_drawRectangleShape(fight->tex, fight->solid[i], NULL);
    sfRenderTexture_display(fight->tex);
    return sfRenderTexture_getTexture(fight->tex);
}

int touch_solid(sfFloatRect rect, fight_t *fight)
{
    sfFloatRect rect2;
    for (int i = 0; i < 20; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(fight->solid[i]);
        if (sfFloatRect_intersects(&rect, &rect2, NULL))
            return (1);
    }
    return (0);
}
