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

static const sfIntRect pl_rect_idle[5] = {
    {0, 640, 64, 64},
    {64, 640, 64, 64}
};

static const sfIntRect *pl_rects[5] = {
    pl_rect_top,
    pl_rect_down,
    pl_rect_left,
    pl_rect_right,
    pl_rect_idle
};
#endif
