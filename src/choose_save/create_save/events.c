/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** events.c
*/

#include "rpg.h"

static void check_press(create_save_t *c, float x, float y)
{
    check_button_press(c->color_buttons, 6, x, y);
    for (int i = 0; i < 6; i++)
        if (c->color_buttons[i]->is_press)
            restart_clock(c->repeat);
    check_button_press(c->stats_buttons, 8, x, y);
    check_button_press(c->actions, 2, x, y);
}

static void check_hover(create_save_t *c, float x, float y)
{
    check_button_move(c->color_buttons, 6, x, y);
    check_button_move(c->stats_buttons, 8, x, y);
    check_button_move(c->actions, 2, x, y);
    if (sfMouse_isButtonPressed(sfMouseLeft))
        check_press(c, x, y);
}

static void change_stats(create_save_t *c, int button)
{
    int type = button / 2;
    int offset = button % 2 ? 1 : -1;
    int error;
    int cur_val = my_getnbr(sfText_getString(c->stats_val[type]), &error);
    int new_val = cur_val + offset;
    int pts_left = my_getnbr(sfText_getString(c->pts_left) + 13,
    &error) - offset;
    char *tmp;
    char *tmp2;
    if (pts_left < 0 || new_val < 0)
        return;
    tmp = nbr_to_str(pts_left);
    tmp2 = str_concat(2, "Points left: ", tmp);
    sfText_setString(c->pts_left, tmp2);
    free(tmp);
    free(tmp2);
    tmp = nbr_to_str(new_val);
    sfText_setString(c->stats_val[type], tmp);
    center_text(c->stats_val[type]);
    free(tmp);
}

static void check_release(create_save_t *c, float x, float y, window_t *win)
{
    button_t **to_check[3] = {c->actions, c->color_buttons, c->stats_buttons};
    int sizes[3] = {2, 6, 8};
    int button = -1;
    int type;
    int is_pressed;
    for (type = 0; type < 3 && button < 0; type++)
        button = button_at(to_check[type], sizes[type], x, y);
    type--;
    is_pressed = button >= 0 ? to_check[type][button]->is_press : 0;
    restart_clock(c->repeat);
    for (int i = 0; i < 3; i++)
        check_button_press(to_check[i], sizes[i], -100, -100);
    if (!is_pressed || !to_check[type][button]->can_trigger)
        return;
    if (to_check[type][button]->release)
        sfSound_play(to_check[type][button]->release);
    if (type == 0)
        return button == 0 ?
        set_next_win_state(win, SELECT_SAVE) : create_file(c, win);
    return type == 1 ? change_color(c, button) : change_stats(c, button);
}

void create_save_events(window_t *win, sfEvent ev)
{
    create_save_t *c = win->menus[CREATE_SAVE];
    int error = 0;
    int pts_left;

    line_edit_event(c->name, ev);
    if (ev.type == sfEvtMouseMoved)
        check_hover(c, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_press(c, ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_release(c, ev.mouseButton.x, ev.mouseButton.y, win);
    pts_left = my_getnbr(sfText_getString(c->pts_left) + 13, &error);
    if (my_strlen(get_text(c->name)) && !error && !pts_left)
        set_button_enabled(c->actions[1], 1);
    else
        set_button_enabled(c->actions[1], 0);
}
