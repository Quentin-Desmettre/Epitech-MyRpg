/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/fight.h"

void fall(sfFloatRect *rect, fight_t *fight)
{
    if (touch_solid(*rect, fight) == 0) {
        sfRectangleShape_setPosition(fight->player,
        (sfVector2f){rect->left, rect->top});
        fight->fall += 1;
    } else {
        while (touch_solid(*rect, fight) == 1) {
            rect->top += fight->fall < 0 ? 1: -1;
        }
        sfRectangleShape_setPosition(fight->player,
        (sfVector2f){rect->left, rect->top});
        fight->fall = 0;
    }
}

void side_move(sfFloatRect *rect, fight_t *fight, int left)
{
    if (touch_solid(*rect, fight) == 0) {
        sfRectangleShape_setPosition(fight->player,
        (sfVector2f){rect->left, rect->top});
    } else {
        while (touch_solid(*rect, fight) == 1)
            rect->left += left;
        sfRectangleShape_setPosition(fight->player,
        (sfVector2f){rect->left, rect->top});
    }
}

void jump(sfFloatRect *rect, fight_t *fight)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace) || sfKeyboard_isKeyPressed(sfKeyZ)) {
        rect->top += 1;
        if (touch_solid(*rect, fight) == 1)
            fight->fall = -25;
        rect->top -= 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) && fight->fall < 15) {
        fight->fall = 15;
    }
}

void move_pl_fight(fight_t *fight)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(fight->player);
    rect.top += fight->fall;
    fall(&rect, fight);
    jump(&rect, fight);
    if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyD)) {
        rect.left += sfKeyboard_isKeyPressed(sfKeyQ) ? -5 : 5;
        side_move(&rect, fight, sfKeyboard_isKeyPressed(sfKeyQ) ? 1 : -1);
    }
}
