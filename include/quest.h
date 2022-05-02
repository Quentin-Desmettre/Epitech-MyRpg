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
    quest_t quests[4];
    sfText *name;
    sfText *desc;
    sfTexture *textr;
    sfRectangleShape *selec;
    sfSprite *back;
    char const *name_qst[4];
    char const *desc_qst[4];
    int is_quest_used[4];
    int draw;
} quest_data_t;

#endif
