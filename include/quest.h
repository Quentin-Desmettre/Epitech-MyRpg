/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** inventory
*/

#ifndef QUEST_H
    #define QUEST_H

    #include "rpg.h"
    #include "game.h"

typedef struct quest_t {
    int check;
    int finish;
    char *name;
    char *desc;
} quest_t;

typedef struct quest_data_t {
    quest_t quests[6];
    int draw;
    sfText *name;
    sfText *desc;
    sfTexture *textr;
    sfRectangleShape *selec;
    sfSprite *back;
} quest_data_t;

#endif
