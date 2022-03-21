/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rpg.h
*/

#pragma once
#include <SFML/Window.h>
#include <SFML/Graphics.h>

#define REPEAT_DELAY 500000

typedef struct {
    sfVideoMode mode;
    sfRenderWindow *win;
    int state;
    void *menus[5];
    sfClock *lum_clock;

    int is_transition;
    int next_state;
    int framerate;
} window_t;

typedef enum {
    SETTINGS, HOME
} state_t;

void rescale_all(window_t *win);
