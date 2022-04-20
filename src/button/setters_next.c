/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** setters_next.c
*/

#include "button.h"
#include "audio_builder.h"

void set_texture(button_t *b, va_list va)
{
    sfSprite_setTexture(b->sprite, va_arg(va, sfTexture *), 0);
}

void set_rect(button_t *b, va_list va)
{
    sfSprite_setTextureRect(b->sprite, va_arg(va, sfIntRect));
}

void set_f_size(button_t *b, va_list va)
{
    float size = va_arg(va, double);

    b->font_factor = size;
}

void set_pfx(button_t *b, va_list va)
{
    char *file = va_arg(va, char *);

    b->press = create_sound(file);
}

void set_rfx(button_t *b, va_list va)
{
    char *file = va_arg(va, char *);

    b->release = create_sound(file);
}
