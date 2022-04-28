/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game_ev.c
*/

#include "rpg.h"

static void set_menus_to_false(game_t *g, int except)
{
    if (except != sfKeyI)
        g->inventory->draw = 0;
    if (except != sfKeyTab)
        g->quest->draw = 0;
    if (except != sfKeyJ)
        g->skills->draw = 0;
}

static void show_menus_ev(sfEvent ev, game_t *game)
{
    if (ev.key.code == sfKeyI ||
    ev.key.code == sfKeyTab || ev.key.code == sfKeyJ)
        set_menus_to_false(game, ev.key.code);
    if (ev.key.code == sfKeyI)
        game->inventory->draw = !game->inventory->draw;
    if (ev.key.code == sfKeyTab)
        game->quest->draw = !game->quest->draw;
    if (ev.key.code == sfKeyJ)
        game->skills->draw = !game->skills->draw;
}

static void debug_ev(sfEvent ev, window_t *win, game_t *game)
{
    if (ev.key.code == sfKeyR)
        new_room(win->menus[GAME], win->menus[LIGHT]);
    if (ev.key.code == sfKeyB)
        remove_xp(game, 1);
    if (ev.key.code == sfKeyN)
        add_xp(game, 1);
    if (ev.key.code == sfKeyAdd)
        next_level(win->menus[LIGHT]);
}

static void menus_ev(sfEvent ev, game_t *game, window_t *win)
{
    if (ev.type == sfEvtMouseButtonReleased &&
    ev.mouseButton.button == sfMouseLeft) {
        if (game->inventory->draw)
            inventory_events(game, ev, win);
        if (game->skills->draw)
            skills_events(game, ev, win_size(win));
        if (game->quest->draw)
            ev_quest(game, ev, win->win);
    }
}

void game_ev(window_t *win, sfEvent ev)
{
    game_t *game = win->menus[GAME];

    if (game->is_paused)
        pause_events(game, win, ev);
    else if (ev.type == sfEvtKeyReleased && !game->is_flashing) {
        if (check_pause(ev, game))
            return;
        if (ev.key.code == sfKeyE)
            take_item(win, win->menus[GAME], win->menus[LIGHT]);
        show_menus_ev(ev, game);
        debug_ev(ev, win, game);
    }
    menus_ev(ev, game, win);
}
