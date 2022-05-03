/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** player
*/

#ifndef PLAYER_CINE_H_
    #define PLAYER_CINE_H_

    #include "rpg.h"

static const int cine_frames[3] = {
    1, 9, 6
};

static const sfIntRect cine_rect_left[1] = {
    {0, 576, 64, 64}
};

static const sfIntRect cine_rect_right[9] = {
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

static const sfIntRect cine_rect_down[6] = {
    {0, 1280, 64, 64},
    {64, 1280, 64, 64},
    {128, 1280, 64, 64},
    {192, 1280, 64, 64},
    {256, 1280, 64, 64},
    {320, 1280, 64, 64}
};

static const sfIntRect *cine_rects[3] = {
    cine_rect_left, cine_rect_right, cine_rect_down
};

#endif
