/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "rpg.h"
    #include "quest.h"
    #include "npc.h"
    #include "lobby.h"
    #include "skills.h"
    #include "inventory.h"
    #include "pause.h"

typedef struct item {
    int type;
    sfVector2f pos;
} item_t;

typedef struct game {
    list_t *items;
    sfRenderTexture *rtex;
    inventory_t *inventory;
    level_t *level;
    npc_t *player;
    p_clock_t *clock;
    skills_t *skills;
    list_t *enemies;
    int is_flashing;
    int nb_flash;
    quest_data_t *quest;
    p_clock_t *flash_clock;
    int is_paused;
    pause_t *pause;
} game_t;

// item room
char choose_item(int i, int j, char c, game_t *game);

#endif
