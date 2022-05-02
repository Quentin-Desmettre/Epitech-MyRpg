/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/rpg.h"

void change_to_prop(sfRenderTexture *tex , sfRectangleShape *rec, window_t *win)
{
    sfVector2f tmp = sfRectangleShape_getPosition(rec);
    sfVector2f tmp2 = sfRectangleShape_getPosition(rec);
    sfVector2f size = win_size(win);
    float offset = (size.x - ((800 / 600.0) * size.y)) / 2;

    tmp.x = tmp.x / 1080 * size.y + offset;
    tmp.y = tmp.y / 1080 * size.y;
    sfRectangleShape_setScale(rec, (sfVector2f){size.y / 1080, size.y / 1080});
    sfRectangleShape_setPosition(rec, tmp);
    sfRenderTexture_drawRectangleShape(tex, rec, NULL);
    sfRectangleShape_setScale(rec, (sfVector2f){1, 1});
    sfRectangleShape_setPosition(rec, tmp2);
}

void change_to_prop_c(sfRenderTexture *tex , sfCircleShape *crl, window_t *win)
{
    sfVector2f tmp = sfCircleShape_getPosition(crl);
    sfVector2f tmp2 = sfCircleShape_getPosition(crl);
    sfVector2f size = win_size(win);
    float offset = (size.x - ((800 / 600.0) * size.y)) / 2;

    tmp.x = tmp.x / 1080 * size.y + offset;
    tmp.y = tmp.y / 1080 * size.y;
    sfCircleShape_setScale(crl, (sfVector2f){size.y / 1080, size.y / 1080});
    sfCircleShape_setPosition(crl, tmp);
    sfRenderTexture_drawCircleShape(tex, crl, NULL);
    sfCircleShape_setScale(crl, (sfVector2f){1, 1});
    sfCircleShape_setPosition(crl, tmp2);
}

void change_to_prop_s(sfRenderTexture *tex , sfSprite *ply, window_t *win)
{
    sfVector2f tmp = sfSprite_getPosition(ply);
    sfVector2f tmp2 = sfSprite_getPosition(ply);
    sfVector2f size = win_size(win);
    float offset = (size.x - ((800 / 600.0) * size.y)) / 2;

    tmp.x = tmp.x / 1080 * size.y + offset;
    tmp.y = tmp.y / 1080 * size.y;
    sfSprite_setScale(ply, (sfVector2f){size.y / 1080, size.y / 1080});
    sfSprite_setPosition(ply, tmp);
    sfRenderTexture_drawSprite(tex, ply, NULL);
    sfSprite_setScale(ply, (sfVector2f){1, 1});
    sfSprite_setPosition(ply, tmp2);
}

void dis_circle(fight_t *fight, window_t *win)
{
    sfVector2f tmp = sfRectangleShape_getPosition(fight->player);
    sfVector2f tmp2 = sfCircleShape_getPosition(fight->circle);
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t info = c->saves[c->primary]->infos;
    sfVector2f w_size = win_size(win);
    int pos = 0;
    int x = 120;

    draw_game_bar(fight->tex, (sfVector2f){w_size.x / 50 * 49 - w_size.x / 6,
    w_size.y / 20}, (sfVector2f){w_size.x / 6, w_size.y / 25}, (sfVector2f){fight->nme, 0});
    if (sqrt(pow(tmp.x + 50 - tmp2.x, 2) + pow(tmp.y + 50 - tmp2.y, 2)) > 125)
        return;
    if (sfCircleShape_getPosition(fight->circle).x == 120)
        x = 1320;
    do {
        sfCircleShape_setPosition(fight->circle, (sfVector2f){x, 100 * (9 - pos)});
        pos++;
    } while (touch_solid(sfCircleShape_getGlobalBounds(fight->circle), fight));
    fight->nme -= 15 + 15 * (((2.0 - ((ray_c *)win->menus[LIGHT])->lvl) / 2.0) +
    15 * (info.strength / 30.0));
}