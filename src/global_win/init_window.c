/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** init_window.c
*/

#include "rpg.h"
#include "game.h"
#include "light.h"

static void create_basics(window_t *win)
{
    win->state = HOME;
    win->next_state = HOME;
    win->is_transition = 0;
    win->mode = (sfVideoMode){800, 600, 32};
    win->lum_clock = sfClock_create();
}

static void create_settings(window_t *win)
{
    win->menus[SETTINGS] = init_settings(win);
    load_settings(win->menus[SETTINGS]);
}

static void create_pointers(window_t *win)
{
    const sfTexture* (*dr[6])(window_t *) = {
        draw_settings, draw_main_menu, NULL, draw_game, NULL, draw_choose_save
    };
    void (*ev[6])(window_t *, sfEvent) = {
        settings_ev, main_menu_ev, NULL, game_ev, NULL, NULL
    };
    for (int i = 0; i < 6; i++) {
        win->draw[i] = dr[i];
        win->event[i] = ev[i];
    }
}

window_t *window_create(void)
{
    window_t *win = malloc(sizeof(window_t));

    create_pointers(win);
    create_basics(win);
    create_settings(win);
    win->menus[HOME] = create_main_menu(WIN_SIZE(win));
    win->menus[GAME] = game_create(win);
    win->menus[LIGHT] = malloc(sizeof(all_t));
    win->menus[SELECT_SAVE] = create_choose_save(WIN_SIZE(win));
    set_game_light(win->menus[LIGHT], win->menus[GAME]);
    apply_settings(win->menus[SETTINGS], win);
    return win;
}
