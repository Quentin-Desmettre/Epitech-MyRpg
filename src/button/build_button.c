/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** build_button.c
*/

#include "button.h"

void init_default(button_t *b)
{
    b->size_fac = (sfVector2f){1, 1};
    b->pos_fac = (sfVector2f){1, 1};
    b->container_size = (sfVector2f){0, 0};
    b->action = NULL;
    b->text = init_text("", 0);
    b->sprite = init_sprite_from_texture(global_texture());
}

void button_set_container_size(button_t *b, sfVector2f new_size)
{
    b->container_size = new_size;
    update_button(b);
}

void update_button(button_t *b)
{
    sfVector2f sf = b->size_fac;
    sfVector2f pf = b->pos_fac;
    sfVector2f cs = b->container_size;
    b->size = (sfVector2f){sf.x * cs.x, sf.y * cs.y};
    b->pos = (sfVector2f){pf.x * cs.x, pf.y * cs.y};

    set_sprite_size(b->sprite, b->size);
    sfSprite_setPosition(b->sprite, b->pos);
    sfText_setCharacterSize(b->text, b->size.y);
    sfText_setPosition(b->text, b->pos);
}

button_t *build_button(char *format, ...)
{
    button_t *b = malloc(sizeof(button_t));
    char *params[] = {"sf", "pf", "base_size",
    "release", "text", "texture", "rect", NULL};
    void (*setters[])(button_t *, va_list) = {set_sf, set_pf,
    set_base_size, set_release, set_text, set_texture, set_rect};
    char **p = my_str_to_word_array(format, ",");
    va_list va;
    init_default(b);
    va_start(va, format);
    for (int i = 0, index = 0; p[i]; i++) {
        index = index_str_in_array(params, p[i]);
        if (index >= 0 && index < 7)
            setters[index](b, va);
    }
    va_end(va);
    free_str_array(p, 0);
    center_sprite(b->sprite);
    center_text(b->text);
    update_button(b);
    return b;
}
