/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"

const sfTexture *draw_fight(window_t *win)
{
    sfVector2f w_size = win_size(win);
    fight_t *fight = win->menus[FIGHT];
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t info = c->saves[c->primary]->infos;

    sfRenderTexture_clear(fight->tex, sfColor_fromRGB(40, 40, 40));
    change_to_prop_c(fight->tex, fight->circle, win);
    change_to_prop(fight->tex, fight->player, win);
    for (int i = 0; i < DMG; i++)
        change_to_prop(fight->tex, fight->dmg[i], win);
    for (int i = 0; i < 20; i++)
        change_to_prop(fight->tex, fight->solid[i], win);
    sfRenderTexture_display(fight->tex);
    move_blocs(fight, win);
    draw_game_bar(fight->tex,
    (sfVector2f){w_size.x / 50, w_size.y / 20}, (sfVector2f){w_size.x / 6
    , w_size.y / 25}, (sfVector2f){info.health_percent, 0});
    dis_circle(fight, win);
    return sfRenderTexture_getTexture(fight->tex);
}

void fight_ev(window_t *win, sfEvent ev)
{
    if (ev.type == sfEvtClosed)
        set_next_win_state(win, EXIT);
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

int touch_dmg(sfFloatRect rect, fight_t *fight)
{
    sfFloatRect rect2;

    for (int i = 0; i < DMG; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(fight->dmg[i]);
        if (sfFloatRect_intersects(&rect, &rect2, NULL))
            return (1);
    }
    return (0);
}
