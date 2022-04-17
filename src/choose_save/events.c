/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** events.c
*/

#include "rpg.h"

void check_move(choose_save_t *c, sfEvent ev)
{
    float x = ev.mouseMove.x;
    float y = ev.mouseMove.y;
    sfFloatRect rect;
    sfSprite *tmp;

    check_button_move(c->buttons, 4, x, y);
    for (int i = 0; i < 3; i++) {
        tmp = get_gui_player(c->saves[i], c->rtex, i);
        rect = sfSprite_getGlobalBounds(tmp);
        sfSprite_destroy(tmp);
        if (sfFloatRect_contains(&rect, x, y)) {
            c->secondary = i;
            return;
        }
    }
    c->secondary = -1;
}

void update_buttons_colors(choose_save_t *c)
{
    gui_player_t *selected = c->primary >= 0 ? c->saves[c->primary] : NULL;
    int can_trigger[4] = {1, 1, 1, 1};

    if (!selected)
        memset(can_trigger + 1, 0, sizeof(int) * 3);
    else {
        if (!my_strcmp(sfText_getString(selected->stats), "Empty file")) {
            can_trigger[1] = 0;
            can_trigger[3] = 0;
        } else
            can_trigger[2] = 0;
    }
    for (int i = 0; i < 4; i++) {
        sfSprite_setColor(c->buttons[i]->sprite,
        can_trigger[i] ? sfWhite : grey);
        sfText_setColor(c->buttons[i]->text,
        can_trigger[i] ? sfWhite : grey);
        c->buttons[i]->can_trigger = can_trigger[i];
    }
}

void check_release(choose_save_t *c, sfEvent ev, window_t *win)
{
    sfVector2f pos = {ev.mouseButton.x, ev.mouseButton.y};
    sfFloatRect rect;
    sfSprite *tmp;

    if (check_button_release(c->buttons, 4, pos, win))
        return;
    for (int i = 0; i < 3; i++) {
        tmp = get_gui_player(c->saves[i], c->rtex, i);
        rect = sfSprite_getGlobalBounds(tmp);
        sfSprite_destroy(tmp);
        if (sfFloatRect_contains(&rect, pos.x, pos.y)) {
            c->primary = i;
            return update_buttons_colors(c);
        }
    }
    c->primary = -1;
    update_buttons_colors(c);
}

void file_select_events(window_t *win, sfEvent ev)
{
    choose_save_t *c = win->menus[SELECT_SAVE];

    if (ev.type == sfEvtMouseMoved)
        check_move(c, ev);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(c->buttons, 4, ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_release(c, ev, win);
}
