/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** rescale_all.c
*/

#include "rpg.h"

void rescale_all(window_t *win)
{
    sfVector2f size = {win->mode.width, win->mode.height};
    rescale_settings(win->menus[SETTINGS], win);
}
