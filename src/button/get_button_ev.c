/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** get_button_ev.c
*/

#include "button.h"
#include <stdbool.h>

bool is_on_button(sfVector2f pos, button_t *b)
{
    sfFloatRect bounds = {
        b->pos.x - b->size.x / 2.0, b->pos.y - b->size.y / 2.0,
        b->size.x, b->size.y
    };

    if (sfFloatRect_contains(&bounds, pos.x, pos.y))
        return true;
    return false;
}

void check_button_move(button_t **buttons, int nb_button, float x, float y)
{
    sfVector2f pos = {x, y};

    for (int i = 0; i < nb_button; i++)
        hover_button(buttons[i],
        buttons[i]->can_trigger ? is_on_button(pos, buttons[i]) : 0);
}

void check_button_press(button_t **buttons, int nb_button, float x, float y)
{
    sfVector2f pos = {x, y};

    for (int i = 0; i < nb_button; i++)
        press_button(buttons[i],
        buttons[i]->can_trigger ? is_on_button(pos, buttons[i]) : 0);
}

int check_button_release(button_t **buttons, int nb_button,
sfVector2f pos, void *win)
{
    int button = button_at(buttons, nb_button, pos.x, pos.y);
    int is_pressed = button >= 0 ? buttons[button]->is_press : 0;

    for (int i = 0; i < nb_button; i++)
        press_button(buttons[i], 0);
    if (button < 0)
        return 0;
    if (!is_pressed || !buttons[button]->can_trigger)
        return 0;
    if (buttons[button]->release)
        sfSound_play(buttons[button]->release);
    if (buttons[button]->action)
        buttons[button]->action(win);
    return 1;
}

int button_at(button_t **buttons, int nb_button, float x, float y)
{
    sfVector2f pos = {x, y};

    for (int i = 0; i < nb_button; i++)
        if (is_on_button(pos, buttons[i]))
            return i;
    return -1;
}
