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
    sfFloatRect tmp1 = *rect;
    sfFloatRect tmp2 = *rect;

    tmp1.height = (tmp1.height / 3) * 2;
    tmp2.width /= 3;
    tmp2.left += tmp2.width;
    if (touch_solid(tmp1, fight) == 0 && touch_solid(tmp2, fight) == 0) {
        fight->fall += 0.6 * time;
    } else
        while (touch_solid(tmp1, fight) == 1 || touch_solid(tmp2, fight) == 1) {
            tmp = up_solid(tmp1, fight, fight->fall < 0);
            tmp1.top = tmp == -1 ? tmp1.top : tmp;
            tmp2.top = tmp1.top;
            tmp = up_solid(tmp2, fight, fight->fall < 0);
            tmp2.top = tmp == -1 ? tmp2.top : tmp;
            tmp1.top = tmp2.top;
            fight->fall = 0;
        }
    rect->top = tmp1.top;
}

void exeption_side_move(sfFloatRect *rect, sfFloatRect *tmp1
, sfFloatRect *tmp2, fight_t *fight)
{
    float tmp = 0;

    if (rect->left < 0)
        rect->left = 0;
    if (rect->left >= 1340)
        rect->left = 1340;
    if (touch_solid(*tmp1, fight) == 0 && touch_solid(*tmp2, fight) == 1) {
        tmp = up_solid(*rect, fight, 0);
        rect->top = tmp == -1 ? rect->top : tmp;
        tmp2->top = rect->top;
        tmp1->top = tmp2->top;
    }
}

void side_move(sfFloatRect *rect, fight_t *fight, int left)
{
    float tmp;
    sfFloatRect tmp1 = *rect;
    sfFloatRect tmp2 = *rect;

    tmp1.height = (tmp1.height / 3) * 2;
    tmp2.width /= 3;
    tmp2.left += tmp2.width;
    exeption_side_move(rect, &tmp1, &tmp2, fight);
    if (touch_solid(tmp1, fight) != 0 || touch_solid(tmp2, fight) != 0) {
        while (touch_solid(tmp1, fight) == 1 || touch_solid(tmp2, fight) == 1) {
            tmp = side_solid(tmp1, fight, left);
            tmp1.left = tmp == -1 ? tmp1.left : tmp;
            tmp2.left = tmp1.left + tmp2.width;
            tmp = side_solid(tmp2, fight, left);
            tmp2.left = tmp == -1 ? tmp2.left : tmp;
            tmp1.left = tmp2.left - tmp2.width;
        }
        rect->left = tmp1.left;
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
