/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** sprite.h
*/

#ifndef SPRITE_H
    #define SPRITE_H
    #include <SFML/Graphics.h>

sfSprite *init_sprite(sfTexture *t, sfIntRect rect, sfVector2f size);
sfSprite *init_sprite_from_texture(sfTexture const *t);
sfText *init_text(char const *str, int charSize);
void set_sprite_size(sfSprite *s, sfVector2f size);
void center_text(sfText *t);
sfVector2f get_sprite_size(sfSprite *s);
void center_sprite(sfSprite *s);

#endif
