/*
** EPITECH PROJECT, 2019
** project
** File description:
** project
*/

#include "include/my.h"

void anime_stand(player_t *p)
{
    p->rect.top = 640;
    p->rect.left = 0;
    p->rect.height = 64;
    p->rect.width = 64;
    sfSprite_setTextureRect(p->sprite, p->rect);
}

void anime_player(player_t *p, int move)
{
    p->time_n_walk = sfClock_getElapsedTime(p->clock_n_walk);
    p->seconds_n_walk = p->time_n_walk.microseconds / 1000000.0;
    if (move == 1)
        p->rect.top = 704;
    if (move == 2)
        p->rect.top = 576;
    if (move == 3)
        p->rect.top = 640;
    if (move == 4)
        p->rect.top = 512;
    if (p->seconds_n_walk > 0.05) {
        p->rect.left = p->rect.left + 64;
        if (p->rect.left == 576) {
            p->rect.left = 0;
        }
        sfSprite_setTextureRect(p->sprite, p->rect);
        sfClock_restart(p->clock_n_walk);
    }
}

void what_move(player_t *player, int flag)
{
    if ((flag & 1) > 0) {
        move_right(player);
        anime_player(player, 1);
    }
    if ((flag & 2) > 0) {
        move_left(player);
        anime_player(player, 2);
    }
    if ((flag & 4) > 0) {
        move_down(player);
        anime_player(player, 3);
    }
    if ((flag & 8) > 0) {
        move_up(player);
        anime_player(player, 4);
    }
}