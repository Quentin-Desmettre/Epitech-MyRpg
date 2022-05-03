/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** cinematic
*/

#ifndef CINEMATIC_H_
    #define CINEMATIC_H_

    #include "rpg.h"

    #define SEC * 1000000

typedef struct cinematic {
    sfRenderTexture *rtex;
    sfRectangleShape *rect;
    sfSprite *floor;
    sfSprite *wall;
    level_t *level;
    npc_t *npc[2];
    int nb_flash;
    int player_state;
    p_clock_t *clock;
    p_clock_t *run_clock;
} cinematic_t;

void cinematic_ev(window_t *win, sfEvent ev);
void destroy_cinematic(cinematic_t *cin);

#endif
