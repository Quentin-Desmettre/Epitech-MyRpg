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

static const int p_frames[5] = {
    5, 5, 5, 5, 5
};

static const sfIntRect p_rect_left[5] = {
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100}
};

static const sfIntRect p_rect_top[5] = {
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100}
};

static const sfIntRect p_rect_right[5] = {
    {0, 0, 100, 100},
    {0, 0, 200, 100},
    {0, 0, 300, 100},
    {0, 0, 400, 100},
    {0, 0, 500, 100}
};

static const sfIntRect p_rect_down[5] = {
    {0, 0, 100, 100},
    {0, 0, 100, 200},
    {0, 0, 100, 300},
    {0, 0, 100, 400},
    {0, 0, 100, 500}
};

static const sfIntRect p_rect_idle[5] = {
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100},
    {0, 0, 100, 100}
};

static const sfIntRect *p_rects[5] = {
    p_rect_left,
    p_rect_top,
    p_rect_right,
    p_rect_down,
    p_rect_idle
};

#endif
