/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** setters.c
*/

#include "button.h"

void set_pf(button_t *b, va_list va)
{
    b->pos_fac = va_arg(va, sfVector2f);
}

void set_sf(button_t *b, va_list va)
{
    b->size_fac = va_arg(va, sfVector2f);
}

void set_base_size(button_t *b, va_list va)
{
    b->container_size = va_arg(va, sfVector2f);
}

void set_release(button_t *b, va_list va)
{
    b->action = va_arg(va, void (*)(void *));
}

void set_text(button_t *b, va_list va)
{
    sfText_setString(b->text, va_arg(va, char *));
}
