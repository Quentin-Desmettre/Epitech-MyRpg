/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** cine_ev.c
*/

#include "rpg.h"

void cinematic_ev(window_t *win, sfEvent ev)
{
    if (ev.type == sfEvtKeyReleased && ev.key.code == sfKeyEscape)
        set_next_win_state(win, GAME);
}
