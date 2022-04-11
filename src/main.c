/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"

static void win_destroy(window_t *win)
{
    sfRenderWindow_destroy(win->win);
    save_settings(win->menus[SETTINGS]);
    destroy_settings(win->menus[SETTINGS]);
    destroy_main_menu(win->menus[HOME]);
    dest_light(win->menus[LIGHT]);
    destroy_game(win->menus[GAME]);
    sfClock_destroy(win->lum_clock);
    free(win);
}

static void draw(window_t *win)
{
    const sfTexture* tex = win->draw[win->state] ?
    win->draw[win->state](win) : NULL;
    sfSprite *s = init_sprite_from_texture(tex);

    if (win->is_transition)
        update_transition(win, s);
    sfRenderWindow_clear(win->win, sfBlack);
    sfRenderWindow_drawSprite(win->win, s, NULL);
    draw_map(win->menus[LIGHT], win->menus[GAME], win->win);
    sfRenderWindow_display(win->win);
    // sfTexture_destroy((sfTexture *)(((all_t *)(win->menus[LIGHT]))->state.texture));
    sfSprite_destroy(s);
}

void set_next_win_state(window_t *win, int next)
{
    win->next_state = next;
    win->is_transition = 1;
}

static void poll_events(window_t *win)
{
    sfEvent ev;

    while (sfRenderWindow_pollEvent(win->win, &ev)) {
        if (ev.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
            set_next_win_state(win, EXIT);
        if (win->event[win->state])
            win->event[win->state](win, ev);
    }
    if (win->state == SETTINGS)
        check_sound_repeat(win, &ev);
}

int main(void)
{
    window_t *win;

    if (!global_texture() || !global_font())
        return 84;
    win = window_create();
    while (sfRenderWindow_isOpen(win->win)) {
        poll_events(win);
        draw(win);
    }
    win_destroy(win);
    sfFont_destroy(global_font());
    sfTexture_destroy(global_texture());
    return 0;
}
