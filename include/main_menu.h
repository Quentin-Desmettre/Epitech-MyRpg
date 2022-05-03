/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main_menu.h
*/

#ifndef MAIN_MENU_H
    #define MAIN_MENU_H
    #include <SFML/Graphics.h>

static const char *mm_texts[] = {
    "Load save", "Create map", "Play online", "", ""
};
static const sfVector2f mm_pf[5] = {
    {0.75, 0.25}, {0.75, 0.5}, {0.75, 0.75}, {0.05, 0.9}, {0.05, 0.1}
};
static const sfVector2f mm_sf[5] = {
    {0.4, 0.17}, {0.4, 0.17}, {0.4, 0.17}, {0.08, 0}, {0.08, 0}
};
static const double mm_ff_factors[5] = {
    0.55, 0.5, 0.55, 0.2, 0.2
};
static const sfIntRect mm_rects[] = {
    {0, 1, 630, 80},
    {0, 1, 630, 80},
    {0, 1, 630, 80},
    {211, 242, 80, 80},
    {80, 161, 80, 80}
};

#endif
