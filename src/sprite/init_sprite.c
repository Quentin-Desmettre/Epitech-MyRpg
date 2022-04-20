/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** init_sprite.c
*/

#include <SFML/Graphics.h>
#include "sprite.h"
#include "globals.h"
#include "libmy.h"

sfRectangleShape *create_rectangle(sfVector2f size,
sfColor fcol, float thick, sfColor ocol)
{
    sfRectangleShape *r = sfRectangleShape_create();

    sfRectangleShape_setSize(r, size);
    sfRectangleShape_setFillColor(r, fcol);
    sfRectangleShape_setOutlineThickness(r, thick);
    sfRectangleShape_setOutlineColor(r, ocol);
    return r;
}

sfSprite *init_sprite(sfTexture *t, sfIntRect rect, sfVector2f size)
{
    sfSprite *s = sfSprite_create();

    sfSprite_setTexture(s, t, 0);
    sfSprite_setTextureRect(s, rect);
    set_sprite_size(s, size);
    return s;
}

sfSprite *init_sprite_from_texture(sfTexture const *t)
{
    sfSprite *s = sfSprite_create();

    sfSprite_setTexture(s, t, 0);
    return s;
}

sfText *init_text(char const *str, int char_size)
{
    sfText *t = sfText_create();

    sfText_setFont(t, global_font());
    sfText_setCharacterSize(t, char_size);
    sfText_setString(t, str);
    return t;
}

int getnbr_sftext(sfText *t)
{
    char const *str = sfText_getString(t);
    int error;

    return my_getnbr(str, &error);
}
