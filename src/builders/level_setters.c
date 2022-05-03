/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** level_setter
*/

#include "rpg.h"

void set_level_depth(level_t *level, va_list va)
{
    level->depth = va_arg(va, int);
}

void set_level_name(level_t *level, va_list va)
{
    level->name = va_arg(va, char *);
}

void set_level_txt(level_t *level, va_list va)
{
    level->texture = get_texture_by_name(va_arg(va, char *));
    sfSprite_setTexture(level->sprite, level->texture, 0);
}

void set_level_size(level_t *level, va_list va)
{
    level->size = va_arg(va, sfVector2f);
}
