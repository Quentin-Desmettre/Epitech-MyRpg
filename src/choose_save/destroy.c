/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** destroy.c
*/

#include "rpg.h"

void free_save(gui_player_t *g)
{
    sfSprite_destroy(g->border);
    sfText_destroy(g->name);
    sfRenderTexture_destroy(g->rtex);
    sfSprite_destroy(g->skin);
    sfSprite_destroy(g->stats_img);
    sfText_destroy(g->stats);
    free(g);
}

void free_choose_save(choose_save_t *c)
{
    for (int i = 0; i < 4; i++)
        destroy_button(c->buttons[i]);
    if (c->create_save)
        destroy_create_save((void **)(&c->create_save));
    sfTexture_destroy((sfTexture *)sfSprite_getTexture(c->hider));
    sfSprite_destroy(c->hider);
    sfRenderTexture_destroy(c->rtex);
    for (int i = 0; i < 3; i++)
        free_save(c->saves[i]);
    free(c);
}
