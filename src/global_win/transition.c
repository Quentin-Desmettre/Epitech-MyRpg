/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** transition.c
*/

#include "rpg.h"

static void switch_color_dir(window_t *win, int *dir)
{
    if (win->next_state == SELECT_SAVE && win->state == CREATE_SAVE)
        destroy_create_save(&win->menus[CREATE_SAVE]);
    win->state = win->next_state;
    *dir = -1;
    if (win->state == EXIT) {
        while (win->close_sfx && sfSound_getStatus(win->close_sfx) != sfStopped)
            sfSleep((sfTime){100000});
        sfRenderWindow_close(win->win);
    }
    if (win->state == FIGHT)
        recreate_enemy(win->menus[GAME], win->menus[LIGHT]);
    if (win->state == SELECT_SAVE)
        load_saves(win->menus[SELECT_SAVE]);
    if (win->state == HOME)
        set_level(win, 0);
}

static void reset_lum(window_t *win, int *dir, sfColor *lum)
{
    *dir = 1;
    win->is_transition = false;
    *lum = (sfColor){255, 255, 255, 255};
}

static void update_lum(sfColor *lum, int *fac)
{
    lum->a -= *fac;
    lum->b -= *fac;
    lum->r -= *fac;
    lum->g -= *fac;
}

void update_transition(window_t *win, sfSprite *s)
{
    static int dir = 1;
    int fac = dir * 24;
    static sfColor lum = {255, 255, 255, 255};

    if (win->is_transition && get_elapsed_time(win->lum_clock) > 33333) {
        if (lum.a == 39)
            switch_color_dir(win, &dir);
        update_lum(&lum, &fac);
        sfSprite_setColor(s, lum);
        if (dir == -1 && lum.a == 255)
            reset_lum(win, &dir, &lum);
        restart_clock(win->lum_clock);
    }
    sfSprite_setColor(s, lum);
}
