/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/rpg.h"

float side_solid(sfFloatRect rect, fight_t *fight, int left)
{
    sfFloatRect rect2;

    for (int i = 0; i < 20; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(fight->solid[i]);
        if (sfFloatRect_intersects(&rect, &rect2, NULL) && i != 0)
            return (left == 1 ? rect2.left + 200 : rect2.left - 100);
        if (sfFloatRect_intersects(&rect, &rect2, NULL) && i == 0)
            return (left == 1 ? rect2.left + 500 : rect2.left - 100);
    }
    return (-1);
}

float up_solid(sfFloatRect rect, fight_t *fight, int top)
{
    sfFloatRect rect2;

    for (int i = 0; i < 20; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(fight->solid[i]);
        if (sfFloatRect_intersects(&rect, &rect2, NULL))
            return (top == 1 ? rect2.top + 100 : rect2.top - 100);
    }
    return (-1);
}
