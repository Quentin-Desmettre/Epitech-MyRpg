/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** build_button.c
*/

#include "button.h"

void set_button_enabled(button_t *b, int enabled)
{
    sfColor new_col = enabled ? sfSprite_getColor(b->sprite) :
    (sfColor){127, 127, 127, 255};

    if (!b->can_trigger && enabled)
        new_col = sfWhite;
    sfSprite_setColor(b->sprite, new_col);
    sfText_setColor(b->text, new_col);
    b->can_trigger = enabled;
}

void init_default(button_t *b)
{
    b->size_fac = (sfVector2f){1, 1};
    b->pos_fac = (sfVector2f){1, 1};
    b->container_size = (sfVector2f){0, 0};
    b->action = NULL;
    b->text = init_text("", 0);
    b->base_char_size = 0;
    b->sprite = init_sprite_from_texture(global_texture());
    b->font_factor = 0;
    b->is_hover = 0;
    b->is_press = 0;
    b->can_trigger = 1;
    b->press = NULL;
    b->release = NULL;
}

void update_button(button_t *b)
{
    sfVector2f sf = b->size_fac;
    sfVector2f pf = b->pos_fac;
    sfVector2f cs = b->container_size;
    b->size = (sfVector2f){sf.x * cs.x, sf.y * cs.y};
    b->pos = (sfVector2f){pf.x * cs.x, pf.y * cs.y};

    if (sf.x == 0.0)
        b->size.x = b->size.y;
    if (sf.y == 0.0)
        b->size.y = b->size.x;

    set_sprite_size(b->sprite, b->size);
    sfSprite_setPosition(b->sprite, b->pos);
    sfText_setCharacterSize(b->text, b->size.y * b->font_factor);
    sfText_setPosition(b->text, b->pos);
    b->base_char_size = b->size.y * b->font_factor;
}

button_t *build_button(char *format, ...)
{
    button_t *b = malloc(sizeof(button_t));
    char *params[] = {"sf", "pf", "base_size",
    "release", "text", "texture", "rect", "ff", "p_sf", "r_sf", NULL};
    void (*setters[])(button_t *, va_list) = {set_sf, set_pf, set_base_size,
    set_release, set_text, set_texture, set_rect, set_f_size, set_pfx, set_rfx};
    char **p = my_str_to_word_array(format, ",");
    va_list va;
    init_default(b);
    va_start(va, format);
    for (int i = 0, index = 0; p[i]; i++) {
        index = index_str_in_array((const char **)params, p[i]);
        if (index >= 0 && index < 11)
            setters[index](b, va);
    }
    va_end(va);
    free_str_array(p, 0);
    center_sprite(b->sprite);
    center_text(b->text);
    update_button(b);
    return b;
}
