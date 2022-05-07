/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"

void change_axe(fight_t *fight, int number)
{
    fight->dir[number].x = -fight->dir[number].x;
    fight->dir[number].y = -fight->dir[number].y;
}

void move_by(fight_t *fight)
{
    sfFloatRect tmp;
    float time;

    time = get_elapsed_time(fight->speed) / 10000.0;
    restart_clock(fight->speed);
    for (int i = 0; i < DMG; i++) {
        tmp = sfRectangleShape_getGlobalBounds(fight->dmg[i]);
        tmp.top += fight->dir[i].y * time * 0.7;
        tmp.left += fight->dir[i].x * time * 0.7;
        if (tmp.left <= 0 || tmp.left >= 1390 || tmp.top <= 0 || tmp.top >= 1030
        || touch_solid(tmp, fight)) {
            change_axe(fight, i);
        } else
            sfRectangleShape_setPosition(fight->dmg[i], (sfVector2f)
            {tmp.left, tmp.top});
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

void set_dmg_pos(fight_t *fight)
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

void move_blocs(fight_t *fight, window_t *win)
{
    if (fight->nme <= 0) {
        add_xp(win->menus[GAME], 2);
        add_quest_prog(win->menus[GAME], 1, 1);
        set_next_win_state(win, GAME);
        fight->nme = 100;
    }
    for (int i = 0; i < DMG; i++) {
        if (get_elapsed_time(fight->time[i]) / 1000000.0 >
        fight->rand_time[i]) {
            restart_clock(fight->time[i]);
            fill_ran_double(i, fight->dir);
            fight->rand_time[i] = (rand() % 3) + 1;
        }
    }
    move_pl_fight(fight, win);
    move_by(fight);
}
