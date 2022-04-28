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

    #define DMG 12

typedef struct fight_t
{
    sfRectangleShape *solid[20];
    sfRectangleShape *dmg[DMG];
    sfRectangleShape *player;
    sfRenderTexture *tex;
    sfSprite *sprt;
    float fall;

    int test;
    sfVector2f *dir;
    int phase;
    int rand_time[DMG];

    p_clock_t *time[DMG];
    p_clock_t *clock_zigzag;
    p_clock_t *clock_square;
    int *zz;
    int *square;
} fight_t;

void pattern_zigzag(fight_t *fight, int start);
void pattern_square(fight_t *fight, int start);
int *create_zigzag_pattern(void);
int *create_square_pattern(void);
void inverse_pattern(int *pattern, int size);

int touch_solid(sfFloatRect rect, fight_t *fight);
void change_axe(fight_t *fight, int number);
void move_by(fight_t *fight, sfRenderWindow *win);
void fill_ran_double(int size, sfVector2f *dir);
void set_dmg_pos(fight_t *fight, sfRenderWindow *win);
void move_blocs(fight_t *fight, p_clock_t *clock_dmg, sfRenderWindow *win);
void fall(sfFloatRect *rect, fight_t *fight);
void side_move(sfFloatRect *rect, fight_t *fight, int left);
void jump(sfFloatRect *rect, fight_t *fight);
void move_pl_fight(fight_t *fight);
fight_t *init_fight(void);
void destroy_fight(fight_t *fight);

#endif
