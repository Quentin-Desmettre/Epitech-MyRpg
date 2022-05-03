/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** level
*/

#include "rpg.h"

void destroy_level(level_t *l)
{
    sfSprite_destroy(l->sprite);
    for (int i = 0; i < l->size.x + 3; i++)
        free(l->room[i]);
    free(l->room);
    free(l);
}

static level_t *init_level(void)
{
    level_t *level = malloc(sizeof(level_t));

    memset(level, 0, sizeof(level_t));
    level->sprite = sfSprite_create();
    level->texture = global_texture();
    sfSprite_setTexture(level->sprite, level->texture, 0);
    level->size = BIG;
    return level;
}

level_t *level_create(char *params, ...)
{
    va_list va;
    level_t *level = init_level();
    static void (*level_setters[])(level_t *, va_list) = {
        set_level_depth, set_level_name, set_level_txt, set_level_size
    };

    va_start(va, params);
    for (int i = 0, index = 0; params[i]; i++) {
        index = index_of(params[i], LEVEL_PARAMS);
        if (index > -1)
            level_setters[index](level, va);
    }
    va_end(va);
    create_room(level);
    return level;
}
