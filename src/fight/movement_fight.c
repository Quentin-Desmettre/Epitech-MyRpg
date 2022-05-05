/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"

void fall(sfFloatRect *rect, fight_t *fight, float time)
{
    float tmp;

    if (touch_solid(*rect, fight) == 0) {
        fight->fall += 0.6 * time;
    } else {
        while (touch_solid(*rect, fight) == 1) {
            tmp = up_solid(*rect, fight, fight->fall < 0);
            rect->top = tmp == -1 ? rect->left : tmp;
        }
        fight->fall = 0;
    }
}

void side_move(sfFloatRect *rect, fight_t *fight, int left)
{
    float tmp;

    if (rect->left < 0)
        rect->left = 0;
    if (rect->left >= (1340))
        rect->left = 1340;
    if (touch_solid(*rect, fight) != 0) {
        while (touch_solid(*rect, fight) == 1) {
            tmp = side_solid(*rect, fight, left);
            rect->left = tmp == -1 ? rect->left : tmp;
        }
    }
}

void jump(sfFloatRect *rect, fight_t *fight)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace) ||
    sfKeyboard_isKeyPressed(sfKeyZ)) {
        rect->top += 1;
        if (touch_solid(*rect, fight) == 1)
            fight->fall = -25;
        rect->top -= 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) && fight->fall < 15)
        fight->fall = 15;
}

void dmg_pl(fight_t *fight, window_t *win, sfFloatRect rect, float time)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t info = c->saves[c->primary]->infos;
    ray_c *data = win->menus[LIGHT];

    if (touch_dmg(rect, fight) == 1) {
        c->saves[c->primary]->infos.health_percent -= (0.15 + 0.15 * ((30.0 -
        info.stamina) / 30.0) + 0.15 * (data->lvl / 3.0)) * time;
    }
}

void move_pl_fight(fight_t *fight, window_t *win)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(fight->player);
    float time;

    time = sfClock_getElapsedTime(fight->player_clock).microseconds / 10000.0;
    rect.top += (fight->fall * 0.7 + 1) * time;
    fall(&rect, fight, time);
    jump(&rect, fight);
    sfClock_restart(fight->player_clock);
    dmg_pl(fight, win, rect, time);
    if (XOR(sfKeyboard_isKeyPressed(sfKeyQ), sfKeyboard_isKeyPressed(sfKeyD))) {
        rect.left += 5 * time * (sfKeyboard_isKeyPressed(sfKeyQ) ? -1 : 1);
        side_move(&rect, fight, (sfKeyboard_isKeyPressed(sfKeyQ) ? 1 : -1));
    }
    sfRectangleShape_setPosition(fight->player,(sfVector2f)
    {rect.left, rect.top});
}
