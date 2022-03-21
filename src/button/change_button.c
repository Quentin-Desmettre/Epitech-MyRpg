/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** change_button.c
*/

#include "button.h"
#include "sprite.h"

void draw_button_to_rtex(button_t *b, sfRenderTexture *rtex)
{
    sfRenderTexture_drawSprite(rtex, b->sprite, NULL);
    center_text(b->text);
    sfText_setPosition(b->text, b->pos);
    sfRenderTexture_drawText(rtex, b->text, NULL);
}

void button_move(button_t *b, sfVector2f vector)
{
    sfSprite_move(b->sprite, vector);
    sfText_move(b->text, vector);
    b->pos.x += vector.x;
    b->pos.y += vector.y;
}

void button_set_pos(button_t *b, sfVector2f pos)
{
    sfSprite_setPosition(b->sprite, pos);
    sfText_setPosition(b->text, pos);
    b->pos = pos;
}

void button_set_size(button_t *b, sfVector2f size)
{
    set_sprite_size(b->sprite, size);
    sfText_setCharacterSize(b->text, size.x);
    b->size = size;
}
