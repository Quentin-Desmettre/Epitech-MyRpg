/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rotate_vector.c
*/

#include <SFML/Graphics.h>
#include "rpg.h"

void rotate_vector(sfVector2f *vec, float degree)
{
    sfVector2f new;

    degree = deg_to_rad(degree);
    new.x = cos(degree) * vec->x - sin(degree) * vec->y;
    new.y = sin(degree) * vec->x + cos(degree) * vec->y;
    vec->x = new.x;
    vec->y = new.y;
}
