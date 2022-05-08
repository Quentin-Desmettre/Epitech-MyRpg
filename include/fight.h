/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** fight.h
*/

#ifndef FIGHT_H
    #define FIGHT_H
    #include <unistd.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <math.h>
    #include <time.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>
    #include "rpg.h"

    #define DMG 10

typedef struct fight_t {
    sfRectangleShape *solid[20];
    sfRectangleShape *dmg[DMG];
    sfRectangleShape *player;
    sfRenderTexture *tex;
    sfVector2f dir[DMG];
    sfCircleShape *circle;
    float fall;
    int phase;
    int rand_time[DMG];
    p_clock_t *time[DMG];
    p_clock_t *speed;
    float nme;
    sfClock *player_clock;
} fight_t;

void pattern_zigzag(fight_t *fight, int start);
void pattern_square(fight_t *fight, int start);
int *create_zigzag_pattern(void);
int *create_square_pattern(void);
void inverse_pattern(int *pattern, int size);

int touch_solid(sfFloatRect rect, fight_t *fight);
void change_axe(fight_t *fight, int number);
void move_by(fight_t *fight);
void fill_ran_double(int size, sfVector2f *dir);
void set_dmg_pos(fight_t *fight);
fight_t *init_fight(void);
void destroy_fight(fight_t *fight);
float side_solid(sfFloatRect rect, fight_t *fight, int left);
float up_solid(sfFloatRect rect, fight_t *fight, int top);
void dis_circle(fight_t *fight, window_t *win);
int touch_dmg(sfFloatRect rect, fight_t *fight);
void place_circle(int x, fight_t *fight);

#endif
