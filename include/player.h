/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "rpg.h"
    #include "npc.h"

    #define P_TEXT "assets/texture.png"
    #define P_HEALTH 200
    #define P_ATK 15
    #define P_DEF 15
    #define P_SPD 15
    #define THIRST 1

    #define PLAYER_GRP 0
    #define ENEMY_GRP 1
    #define ENEMY_LOADING_GRP 2
    #define V2F_EQ(a, b) ((a).x == (b).x && (a).y == (b).y)

static const int p_frames[5] = {
    5, 5, 5, 5, 5
};

static const sfIntRect pl_rect_left[9] = {
    {0, 704, 64, 64},
    {64, 704, 64, 64},
    {128, 704, 64, 64},
    {192, 704, 64, 64},
    {256, 704, 64, 64},
    {320, 704, 64, 64},
    {384, 704, 64, 64},
    {448, 704, 64, 64},
    {512, 704, 64, 64}
};

static const sfIntRect pl_rect_top[9] = {
    {0, 576, 64, 64},
    {64, 576, 64, 64},
    {128, 576, 64, 64},
    {192, 576, 64, 64},
    {256, 576, 64, 64},
    {320, 576, 64, 64},
    {384, 576, 64, 64},
    {448, 576, 64, 64},
    {512, 576, 64, 64}
};

static const sfIntRect pl_rect_right[9] = {
    {0, 640, 64, 64},
    {64, 640, 64, 64},
    {128, 640, 64, 64},
    {192, 640, 64, 64},
    {256, 640, 64, 64},
    {320, 640, 64, 64},
    {384, 640, 64, 64},
    {448, 640, 64, 64},
    {512, 640, 64, 64}
};

static const sfIntRect pl_rect_down[9] = {
    {0, 512, 64, 64},
    {64, 512, 64, 64},
    {128, 512, 64, 64},
    {192, 512, 64, 64},
    {256, 512, 64, 64},
    {320, 512, 64, 64},
    {384, 512, 64, 64},
    {448, 512, 64, 64},
    {512, 512, 64, 64}
};

static const sfIntRect pl_rect_idle[2] = {
    {0, 640, 64, 64},
    {64, 640, 64, 64}
};

static const sfIntRect pl_rect_dance[7] = {
    {64, 896, 64, 64},
    {128, 896, 64, 64},
    {192, 896, 64, 64},
    {256, 896, 64, 64},
    {320, 896, 64, 64},
    {256, 896, 64, 64},
    {192, 896, 64, 64}
};

static const sfIntRect died_rect[] = {
    {0, 1280, 64, 64},
    {64, 1280, 64, 64},
    {128, 1280, 64, 64},
    {192, 1280, 64, 64},
    {256, 1280, 64, 64},
    {320, 1280, 64, 64}
};

#endif
