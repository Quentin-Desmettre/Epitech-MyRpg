/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc
*/

#include "rpg.h"

static npc_t *init_npc(void)
{
    npc_t *npc = malloc(sizeof(npc_t));

    memset(npc, 0, sizeof(npc_t));
    npc->sprite = sfSprite_create();
    sfSprite_setPosition(npc->sprite, (sfVector2f){0, 0});
    npc->frame = 0;
    npc->dir = RIGHT;
    npc->health = 100;
    npc->attack = 10;
    npc->defense = 10;
    npc->speed = 10;
    npc->pos = (sfVector2f){0, 0};
    return npc;
}

npc_t *npc_create(char *params, ...)
{
    va_list va;
    npc_t *npc = init_npc();

    va_start(va, params);
    for (int i = 0, index = 0; params[i]; i++) {
        index = index_of(params[i], NPC_PARAMS);
        if (index > -1)
            npc_setters[index](npc, va);
    }
    sfSprite_setTextureRect(npc->sprite, npc->rects[npc->dir][npc->frame]);
    va_end(va);
    return npc;
}
