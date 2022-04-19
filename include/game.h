/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "rpg.h"
    #include "npc.h"
    #include "lobby.h"
    #include "inventory.h"

typedef struct game {
    sfRenderTexture *rtex;
    inventory_t *inventory;
    level_t *level;
    npc_t *player;
    sfClock *clock;
} game_t;

#endif
