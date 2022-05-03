/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc_setters
*/

#include "rpg.h"

void set_npc_txt(npc_t *npc, va_list va)
{
    npc->texture = get_texture_by_name(va_arg(va, char *));
    sfSprite_setTexture(npc->sprite, npc->texture, 0);
}

void set_npc_frames(npc_t *npc, va_list va)
{
    int size = 0;
    int *frames = va_arg(va, int *);

    for (; frames[size]; size++);
    npc->nb_frames = malloc(sizeof(int) * (size + 1));
    for (int i = 0; i < size; i++)
        npc->nb_frames[i] = frames[i];
    npc->nb_frames[size] = 0;
}

void set_npc_rects(npc_t *npc, va_list va)
{
    int size = 0;
    sfIntRect **rects = va_arg(va, sfIntRect **);

    for (; npc->nb_frames[size]; size++);
    npc->nb_rects = size;
    npc->rects = malloc(sizeof(sfIntRect *) * size);
    for (int i = 0; i < size; i++) {
        npc->rects[i] = malloc(sizeof(sfIntRect) * (npc->nb_frames[i] + 1));
        for (int j = 0; j < npc->nb_frames[i]; j++) {
            npc->rects[i][j].left = rects[i][j].left;
            npc->rects[i][j].top = rects[i][j].top;
            npc->rects[i][j].width = rects[i][j].width;
            npc->rects[i][j].height = rects[i][j].height;
        }
    }
}

void set_npc_dir(npc_t *npc, va_list va)
{
    npc->dir = va_arg(va, int);
}

void set_npc_grp(npc_t *npc, va_list va)
{
    npc->group = va_arg(va, int);
}
