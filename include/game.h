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

typedef struct game {
    sfRenderTexture *rtex;
} game_t;

game_t *game_create(window_t *win);
void game_ev(window_t *win, sfEvent ev);
const sfTexture *draw_game(window_t *win);

#endif
