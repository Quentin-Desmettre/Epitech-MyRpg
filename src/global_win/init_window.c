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
    const sfTexture* (*dr[])(window_t *) = {
        draw_settings, draw_main_menu, NULL, draw_game, NULL, draw_choose_save,
        draw_create_save
    };
    void (*ev[])(window_t *, sfEvent) = {
        settings_ev, main_menu_ev, NULL, game_ev, NULL, file_select_events,
        create_save_events
    };
    for (int i = 0; i < 7; i++) {
        win->draw[i] = dr[i];
        win->event[i] = ev[i];
    }
}

void center_inventory(game_t *game, window_t *win)
{
    sfVector2f size = WIN_SIZE(win);
    sfVector2u center = sfTexture_getSize(game->inventory->texture);

    sfSprite_setScale(game->inventory->sprite,
    (sfVector2f){size.y / 1080, size.y / 1080});
    game->inventory->pos.x = size.x / 2;
    game->inventory->pos.y = size.y / 2;
    sfSprite_setOrigin(game->inventory->sprite,
    (sfVector2f){center.x / 2, center.y / 2});
    sfSprite_setPosition(game->inventory->sprite, game->inventory->pos);
}

window_t *window_create(void)
{
    window_t *win = malloc(sizeof(window_t));

    memset(win->menus, 0, sizeof(void *) * 12);
    create_pointers(win);
    create_basics(win);
    create_settings(win);
    win->menus[HOME] = create_main_menu(WIN_SIZE(win));
    win->menus[GAME] = game_create(win);
    win->menus[LIGHT] = malloc(sizeof(all_t));
    win->menus[SELECT_SAVE] = create_choose_save(WIN_SIZE(win));
    set_game_light(win->menus[LIGHT], win->menus[GAME]);
    apply_settings(win->menus[SETTINGS], win);
    center_inventory(win->menus[GAME], win);
    return win;
}
