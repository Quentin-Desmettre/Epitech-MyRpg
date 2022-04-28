/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/fight.h"

void change_axe(fight_t *fight, int number)
{
    fight->dir[number].x = -fight->dir[number].x;
    fight->dir[number].y = -fight->dir[number].y;
}

void move_by(fight_t *fight, sfRenderWindow *win)
{
    sfVector2u size_win = sfRenderWindow_getSize(win);
    for (int i = 0; i < DMG; i++) {
        sfVector2f pos_dmg = sfRectangleShape_getPosition(fight->dmg[i]);
        sfVector2f size_dmg = sfRectangleShape_getSize(fight->dmg[i]);
        sfFloatRect tmp = sfRectangleShape_getGlobalBounds(fight->dmg[i]);
        tmp.top += fight->dir[i].y;
        tmp.left += fight->dir[i].x;

        if (tmp.left <= 0 || tmp.left >= (size_win.x - size_dmg.x)
            || tmp.top <= 0 || tmp.top >= (size_win.y - size_dmg.y) ||
            touch_solid(tmp, fight)) {
            change_axe(fight, i);
        } else
            sfRectangleShape_setPosition(fight->dmg[i],
            (sfVector2f){pos_dmg.x + fight->dir[i].x, pos_dmg.y + fight->dir[i]
            .y});
    }
}

void fill_ran_double(int size, sfVector2f *dir)
{
    int r = 0;
    int which = 0;

    r = 5;
    which = (rand() % 2);
    if (rand() % 2)
        r = -r;
    if (which == 1) {
        dir[size].x = r;
        dir[size].y = 0;
    } else {
        dir[size].y = r;
        dir[size].x = 0;
    }
}

void set_dmg_pos(fight_t *fight, sfRenderWindow *win)
{
    for (int i = 0; i < DMG; i++) {
        do {
            sfRectangleShape_setPosition(fight->dmg[i]
            , (sfVector2f){50 * (2 + rand()
            % 36), 50 * (12 + rand() % 8)});
        } while (touch_solid(sfRectangleShape_getGlobalBounds(fight->dmg[i])
        , fight));
    }
}

void move_blocs(fight_t *fight, sfClock *clock_dmg, sfRenderWindow *win)
{
    sfTime time_dmg = sfClock_getElapsedTime(clock_dmg);
    float seconds = time_dmg.microseconds;

    for (int i = 0; i < DMG; i++) {
        if (sfClock_getElapsedTime(fight->time[i]).microseconds / 1000000.0 >
        fight->rand_time[i]) {
            sfClock_restart(fight->time[i]);
            fill_ran_double(i, fight->dir);
            fight->rand_time[i] = (rand() % 3) + 1;
        }
    }
    if (seconds > 5000) {
        move_by(fight, win);
        sfClock_restart(clock_dmg);
    }
}