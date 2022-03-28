/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc_setters
*/

#include "rpg.h"

void set_npc_pos(npc_t *npc, va_list va)
{
    npc->pos = va_arg(va, sfVector2f);
    sfSprite_setPosition(npc->sprite, npc->pos);
}

void set_npc_scale(npc_t *npc, va_list va)
{
    npc->scale = va_arg(va, sfVector2f);
    sfSprite_setScale(npc->sprite, npc->pos);
}
