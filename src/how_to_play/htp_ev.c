/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** htp_ev.c
*/

#include "rpg.h"

void set_htp(window_t *win, int scene_from)
{
    sfVector2f win_s = win_size(win);
    how_to_play_t *h = win->menus[HTP];
    sfVector2f quit_pos = {win_s.x * 0.05, win_s.x * 0.05};
    sfVector2f prev_pos = {win_s.x * 0.11, win_s.y - win_s.x * 0.04};
    sfVector2f next_pos = {win_s.x * (1 - 0.11), win_s.y - win_s.x * 0.04};

    h->from = scene_from;
    h->quit->container_size = win_s;
    update_button(h->quit);
    button_set_pos(h->quit, quit_pos);
    h->next->container_size = win_s;
    update_button(h->next);
    button_set_pos(h->next, next_pos);
    h->prev->container_size = win_s;
    update_button(h->prev);
    button_set_pos(h->prev, prev_pos);
    sfRenderTexture_destroy(h->rtex);
    h->rtex = sfRenderTexture_create(win_s.x, win_s.y, 0);
    set_next_win_state(win, HTP);
}

const sfTexture *draw_htp(window_t *win)
{
    how_to_play_t *h = win->menus[HTP];
    sfVector2f s = win_size(win);

    sfRenderTexture_clear(h->rtex, sfBlack);
    set_sprite_size(h->pages->data, (sfVector2f){s.x * 0.8, s.y * 0.8});
    center_sprite(h->pages->data);
    sfSprite_setPosition(h->pages->data, (sfVector2f){s.x * 0.5, s.y * 0.45});
    sfRenderTexture_drawSprite(h->rtex, h->pages->data, NULL);
    draw_button_to_rtex(h->quit, h->rtex);
    draw_button_to_rtex(h->next, h->rtex);
    draw_button_to_rtex(h->prev, h->rtex);
    sfRenderTexture_display(h->rtex);
    return sfRenderTexture_getTexture(h->rtex);
}

void htp_event(window_t *win, sfEvent ev)
{
    how_to_play_t *h = win->menus[HTP];
    button_t *buttons[3] = {h->quit, h->next, h->prev};

    if (ev.type == sfEvtMouseMoved)
        check_button_move(buttons, 3, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(buttons, 3, ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_button_release(buttons, 3,
        (sfVector2f){ev.mouseButton.x, ev.mouseButton.y}, win);
}
