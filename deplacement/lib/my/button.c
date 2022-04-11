/*
** EPITECH PROJECT, 2019
** decimal_to_hex
** File description:
** to convert decimal to hex
*/
    
#include "../../include/my.h"

void center_button_x(button_t *button, sfRenderWindow *window)
{
    sfVector2u size_window = sfRenderWindow_getSize(window);
    sfVector2f new_pos;
    new_pos.x = (size_window.x / 2) - (button->size.x / 2);
    button->pos.x = new_pos.x;
    sfRectangleShape_setPosition(button->rect, button->pos);
}

void init_button(button_t *button, sfVector2f pos, sfVector2f size)
{
    button->rect = sfRectangleShape_create();
    button->pos = pos;
    button->size = size;
    sfRectangleShape_setSize(button->rect, size);
    sfRectangleShape_setPosition(button->rect, pos);
    sfRectangleShape_setFillColor(button->rect, sfBlue);
    sfRectangleShape_setOutlineColor(button->rect, sfBlue);
    sfRectangleShape_setOutlineThickness(button->rect, 0);
}

int button_is_clicked(button_t *button, sfVector2i p)
{
    sfVector2f pos = sfRectangleShape_getPosition(button->rect);
    sfVector2f size = sfRectangleShape_getSize(button->rect);
    sfVector2f sum;
    sum.x = size.x + pos.x;
    sum.y = pos.y + size.y;
    if ((p.x >= pos.x && p.x <= sum.x) && (p.y >= pos.y && p.y <= sum.y)) {
        sfRectangleShape_setFillColor(button->rect, sfBlack);
        return (1);
    }
    return (0);
}

button_t *create_button(int p_x, int p_y, int s_x, int s_y)
{
    button_t *button = malloc(sizeof(button_t));
    sfVector2f pos;
    pos.x = p_x;
    pos.y = p_y;
    sfVector2f size;
    size.x = s_x;
    size.y = s_y;
    init_button(button, pos, size);
    return (button);
}