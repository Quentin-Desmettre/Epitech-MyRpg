/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** create.c
*/

#include "rpg.h"
#include "line_edit.h"

void destroy_line_edit(line_edit_t *le)
{
    sfRectangleShape_destroy(le->background);
    sfText_destroy(le->text);
    sfRenderTexture_destroy(le->rtex);
    destroy_clock(le->underscore);
    free(le);
}

void update_underscore(line_edit_t *le)
{
    if (get_elapsed_time(le->underscore) <
    LINEEDIT_TIME * (le->has_underscore ? 1.2 : 1))
        return;
    restart_clock(le->underscore);
    if (le->has_underscore)
        remove_last_text(le->text);
    else
        append_to_text(le->text, '_');
    le->has_underscore = !le->has_underscore;
}

sfSprite *draw_line_edit(line_edit_t *le, sfVector2f pos)
{
    sfSprite *s;

    sfRenderTexture_clear(le->rtex, sfWhite);
    update_underscore(le);
    sfRenderTexture_drawRectangleShape(le->rtex, le->background, NULL);
    sfRenderTexture_drawText(le->rtex, le->text, NULL);
    sfRenderTexture_display(le->rtex);
    s = init_sprite_from_texture(sfRenderTexture_getTexture(le->rtex));
    sfSprite_setPosition(s, pos);
    return s;
}

void scale_line_edit(line_edit_t *le, sfVector2f size)
{
    float char_size = size.y / le->max_char * 5;

    sfRenderTexture_destroy(le->rtex);
    le->rtex = sfRenderTexture_create(size.x, size.y, 0);
    sfRectangleShape_setSize(le->background, size);
    sfText_setCharacterSize(le->text, char_size);
    sfText_setOrigin(le->text,
    (sfVector2f){0, char_size * 0.65});
    sfText_setPosition(le->text, (sfVector2f){size.x * 0.02, size.y * 0.5});
}

line_edit_t *create_line_edit(sfVector2f size, char const *def, int max_char)
{
    line_edit_t *le = malloc(sizeof(line_edit_t));
    int maxi = max_char >= 0 ? max_char : 12;

    le->background = sfRectangleShape_create();
    sfRectangleShape_setTexture(le->background, global_texture(), 0);
    sfRectangleShape_setTextureRect(le->background, line_edit_rect);
    le->rtex = sfRenderTexture_create(size.x, size.y, 0);
    le->text = init_text(def, size.y / (float)maxi * 5);
    sfText_setLetterSpacing(le->text, 1.1);
    le->underscore = create_clock();
    le->has_underscore = 0;
    le->max_char = maxi;
    return le;
}
