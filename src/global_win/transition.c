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
        while (win->close_sfx &&
        sfSound_getStatus(win->close_sfx) != sfStopped);
        sfRenderWindow_close(win->win);
    }
}

static void reset_lum(window_t *win, int *dir, sfColor *lum)
{
    *dir = 1;
    win->is_transition = false;
    *lum = (sfColor){255, 255, 255, 255};
    if (win->state == GAME)
        for (int i = 0; i < 10; i++)
            create_enemy(win->menus[GAME], win->menus[LIGHT]);
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

    if (win->is_transition &&
    sfClock_getElapsedTime(win->lum_clock).microseconds > 33333) {
        if (lum.a == 39)
            switch_color_dir(win, &dir);
        update_lum(&lum, &fac);
        sfSprite_setColor(s, lum);
        if (dir == -1 && lum.a == 255)
            reset_lum(win, &dir, &lum);
        sfClock_restart(win->lum_clock);
    }
    sfSprite_setColor(s, lum);
}
