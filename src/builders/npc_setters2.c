/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc_setters
*/

#include "rpg.h"

void set_npc_initframe(npc_t *npc, va_list va)
{
    npc->frame = va_arg(va, int);
}

void set_npc_health(npc_t *npc, va_list va)
{
    npc->thirst = va_arg(va, int);
}

void set_npc_atk(npc_t *npc, va_list va)
{
    npc->attack = va_arg(va, int);
}

void set_npc_def(npc_t *npc, va_list va)
{
    npc->defense = va_arg(va, int);
}

void set_npc_spd(npc_t *npc, va_list va)
{
    npc->speed = va_arg(va, int);
}
