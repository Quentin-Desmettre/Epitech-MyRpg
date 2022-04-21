/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"
#include "player.h"

void move_pl(window_t *win);

static void win_destroy(window_t *win)
{
    sfRenderWindow_destroy(win->win);
    save_settings(win->menus[SETTINGS]);
    destroy_settings(win->menus[SETTINGS]);
    destroy_main_menu(win->menus[HOME]);
    dest_light(win->menus[LIGHT]);
    destroy_game(win->menus[GAME]);
    sfClock_destroy(win->lum_clock);
    free_choose_save(win->menus[SELECT_SAVE]);
    if (win->music)
        destroy_music(win->music);
    if (win->close_sfx)
        destroy_sound(win->close_sfx);
    free(win);
}

static void draw(window_t *win)
{
    const sfTexture* tex = win->draw[win->state] ?
    win->draw[win->state](win) : NULL;
    sfTexture *cpy = tex ? sfTexture_copy(tex) : NULL;
    sfSprite *s = init_sprite_from_texture(cpy);

    if (win->is_transition)
        update_transition(win, s);
    sfRenderWindow_drawSprite(win->win, s, NULL);
    if (win->state == GAME) {
        draw_room(win->menus[LIGHT], win->menus[GAME], win->win);
        draw_map(win->menus[LIGHT], win->menus[GAME], win->win);
        draw_inventory(win->menus[GAME], win);
        move_pl(win);
    }
    sfRenderWindow_display(win->win);
    sfTexture_destroy(cpy);
    sfSprite_destroy(s);
    sfRenderWindow_clear(win->win, sfBlack);
}

void set_next_win_state(window_t *win, int next)
{
    win->next_state = next;
    win->is_transition = 1;
    if (next == EXIT && win->close_sfx)
        sfSound_play(win->close_sfx);
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

    my_srand();
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
    sfTexture_destroy(player_texture());
    sfTexture_destroy(bars_texture());
    return 0;
}
