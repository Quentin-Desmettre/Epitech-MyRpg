/*
** EPITECH PROJECT, 2019
** project
** File description:
** project
*/

#include "include/my.h"

void move_down(player_t *p)
{
    sfVector2f pos = sfSprite_getPosition(p->sprite);
    sfVector2f new_pos;
    if (sfKeyboard_isKeyPressed(sfKeyLShift) == sfTrue) {
        p->sprint = 1;
        new_pos.x = pos.x + 0;
        new_pos.y = pos.y + (p->speed / 20) * 1.5;
    } else if (sfKeyboard_isKeyPressed(sfKeyLControl) == sfTrue) {
        p->slow_walk = 1;
        new_pos.x = pos.x + 0;
        new_pos.y = pos.y + (p->speed / 20) * 0.5;
    } else {
        p->normal_walk = 1;
        new_pos.x = pos.x + 0;
        new_pos.y = pos.y + (p->speed / 20);
    }
    sfSprite_setPosition(p->sprite, new_pos);
}

void move_up(player_t *p)
{
    sfVector2f pos = sfSprite_getPosition(p->sprite);
    sfVector2f new_pos;
    if (sfKeyboard_isKeyPressed(sfKeyLShift) == sfTrue) {
        p->sprint = 1;
        new_pos.x = pos.x + 0;
        new_pos.y = pos.y - (p->speed / 20) * 1.5;
    } else if (sfKeyboard_isKeyPressed(sfKeyLControl) == sfTrue) {
        p->slow_walk = 1;
        new_pos.x = pos.x + 0;
        new_pos.y = pos.y - (p->speed / 20) * 0.5;
    } else {
        p->normal_walk = 1;
        new_pos.x = pos.x + 0;
        new_pos.y = pos.y - (p->speed / 20);
    }
    sfSprite_setPosition(p->sprite, new_pos);
}

void move_left(player_t *p)
{
    sfVector2f pos = sfSprite_getPosition(p->sprite);
    sfVector2f new_pos;
    if (sfKeyboard_isKeyPressed(sfKeyLShift) == sfTrue) {
        p->sprint = 1;
        new_pos.x = pos.x - (p->speed / 20) * 1.5;
        new_pos.y = pos.y + 0;
    } else if (sfKeyboard_isKeyPressed(sfKeyLControl) == sfTrue) {
        p->slow_walk = 1;
        new_pos.x = pos.x - (p->speed / 20) * 0.5;
        new_pos.y = pos.y + 0;
    } else {
        p->normal_walk = 1;
        new_pos.x = pos.x - (p->speed / 20);
        new_pos.y = pos.y + 0;
    }
    sfSprite_setPosition(p->sprite, new_pos);
}

void move_right(player_t *p)
{
    sfVector2f pos = sfSprite_getPosition(p->sprite);
    sfVector2f new_pos;
    if (sfKeyboard_isKeyPressed(sfKeyLShift) == sfTrue) {
        p->sprint = 1;
        new_pos.x = pos.x + (p->speed / 20) * 1.5;
        new_pos.y = pos.y + 0;
    } else if (sfKeyboard_isKeyPressed(sfKeyLControl) == sfTrue) {
        p->slow_walk = 1;
        new_pos.x = pos.x + (p->speed / 20) * 0.5;
        new_pos.y = pos.y + 0;
    } else {
        p->normal_walk = 1;
        new_pos.x = pos.x + (p->speed / 20);
        new_pos.y = pos.y + 0;
    }
    sfSprite_setPosition(p->sprite, new_pos);
}

void check_move(player_t *player)
{
    int flag = 0;
    flag += (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue ? 1 : 0);
    flag += (sfKeyboard_isKeyPressed(sfKeyQ) == sfTrue ? 2 : 0);
    flag += (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue ? 4 : 0);
    flag += (sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue ? 8 : 0);
    if (flag == 0) {
        anime_stand(player);
        return;
    }
    what_move(player, flag);
}