/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** events.c
*/

#include "rpg.h"

void quit_main_menu(void *win)
{
    set_next_win_state(win, EXIT);
}

void go_to_settings(void *win)
{
    set_next_win_state(win, SETTINGS);
}

void go_to_local_save(void *win)
{
    set_next_win_state(win, SELECT_SAVE);
}

void go_to_htp(void *win)
{
    window_t *w = win;
    set_htp(win, w->state);
}
