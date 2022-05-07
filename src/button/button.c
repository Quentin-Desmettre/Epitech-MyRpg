/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** init_button.c
*/

#include "button.h"
#include <stdarg.h>
#include <stdlib.h>
#include "sprite.h"
#include "audio_builder.h"

void destroy_button(button_t *b)
{
    sfSprite_destroy(b->sprite);
    sfText_destroy(b->text);
    if (b->press)
        destroy_sound(b->press);
    if (b->release)
        destroy_sound(b->release);
    free(b);
}

static void factor_color(sfSprite *s, float factor, sfText *text)
{
    sfColor c = sfSprite_getColor(s);

    c.r *= factor;
    c.g *= factor;
    c.b *= factor;
    sfSprite_setColor(s, c);
    sfText_setFillColor(text, c);
}

void hover_button(button_t *b, int is_on)
{
    if (is_on == b->is_hover)
        return;
    if (is_on) {
        sfSprite_scale(b->sprite, (sfVector2f){1.05, 1.05});
        sfText_setCharacterSize(b->text,
        sfText_getCharacterSize(b->text) * 1.05);
    } else {
        sfSprite_scale(b->sprite,
        (sfVector2f){1.0 / 1.05 , 1.0 / 1.05});
        sfText_setCharacterSize(b->text, b->base_char_size);
    }
    b->is_hover = is_on;
}

void press_button(button_t *b, int is_press)
{
    if (is_press == b->is_press)
        return;
    if (is_press) {
        if (b->press)
            sfSound_play(b->press);
        hover_button(b, 0);
        factor_color(b->sprite, 0.5, b->text);
    } else {
        hover_button(b, 1);
        factor_color(b->sprite, 2.0, b->text);
    }
    b->is_press = is_press;
}

button_t *init_button(sfTexture *t, sfIntRect rect,
sfVector2f pos, ...)
{
    button_t *n = malloc(sizeof(button_t));
    va_list va;
    sfVector2f size;
    char *str;

    init_default(n);
    va_start(va, pos);
    size = va_arg(va, sfVector2f);
    str = va_arg(va, char *);
    n->is_hover = 0;
    n->is_press = 0;
    n->pos = pos;
    n->size = size;
    n->text = init_text(str, size.y * 0.7);
    n->sprite = init_sprite(t, rect, size);
    sfSprite_setPosition(n->sprite, pos);
    center_text(n->text);
    n->action = va_arg(va, void (*)(void *));;
    va_end(va);
    return n;
}
