/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** destroy.c
*/

#include "rpg.h"

void destroy_texts(int nb, ...)
{
    va_list va;
    sfText *tmp;

    va_start(va, nb);
    for (int i = 0; i < nb; i++) {
        tmp = va_arg(va, sfText *);
        sfText_destroy(tmp);
    }
    va_end(va);
}

void destroy_create_save(void **cr)
{
    create_save_t *c = *cr;
    button_t **buttons[3] = {c->actions, c->color_buttons, c->stats_buttons};
    int but_sizes[3] = {2, 6, 8};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < but_sizes[i]; j++)
            destroy_button(buttons[i][j]);
    sfSprite_destroy(c->background);
    destroy_texts(10, c->col_vals[0], c->col_vals[1], c->col_vals[2],
    c->prompt, c->pts_left, c->stats_prompt, c->stats_val[0],
    c->stats_val[1], c->stats_val[2], c->stats_val[3]);
    destroy_line_edit(c->name);
    destroy_clock(c->repeat);
    sfRenderTexture_destroy(c->rtex);
    sfSprite_destroy(c->skin);
    sfRectangleShape_destroy(c->skin_back);
    sfSprite_destroy(c->stats);
    free(c);
    *cr = NULL;
}
