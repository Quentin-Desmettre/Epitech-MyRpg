/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** setters_next.c
*/

#include "button.h"

void set_texture(button_t *b, va_list va)
{
    sfSprite_setTexture(b->sprite, va_arg(va, sfTexture *), 0);
}

void set_rect(button_t *b, va_list va)
{
    sfSprite_setTextureRect(b->sprite, va_arg(va, sfIntRect));
}
