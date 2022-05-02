/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** window.c
*/

#include "rpg.h"

window_t *window(window_t *ptr)
{
    static window_t *w = NULL;

    if (ptr)
        w = ptr;
    return w;
}
