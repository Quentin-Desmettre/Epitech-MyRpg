/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"

void change_to_prop(sfRenderTexture *tex , sfRectangleShape *rec, window_t *win)
{
    coo_t tmp = sfRectangleShape_getPosition(rec);
    coo_t tmp2 = sfRectangleShape_getPosition(rec);
    coo_t size = win_size(win);
    float offset = (size.x - ((800 / 600.0) * size.y)) / 2;

    tmp.x = tmp.x / 1080 * size.y + offset;
    tmp.y = tmp.y / 1080 * size.y;
    sfRectangleShape_setScale(rec, (coo_t){size.y / 1080, size.y / 1080});
    sfRectangleShape_setPosition(rec, tmp);
    sfRenderTexture_drawRectangleShape(tex, rec, NULL);
    sfRectangleShape_setScale(rec, (coo_t){1, 1});
    sfRectangleShape_setPosition(rec, tmp2);
}

void change_to_prop_c(sfRenderTexture *tex , sfCircleShape *crl, window_t *win)
{
    coo_t tmp = sfCircleShape_getPosition(crl);
    coo_t tmp2 = sfCircleShape_getPosition(crl);
    coo_t size = win_size(win);
    float offset = (size.x - ((800 / 600.0) * size.y)) / 2;

    tmp.x = tmp.x / 1080 * size.y + offset;
    tmp.y = tmp.y / 1080 * size.y;
    sfCircleShape_setScale(crl, (coo_t){size.y / 1080, size.y / 1080});
    sfCircleShape_setPosition(crl, tmp);
    sfRenderTexture_drawCircleShape(tex, crl, NULL);
    sfCircleShape_setScale(crl, (coo_t){1, 1});
    sfCircleShape_setPosition(crl, tmp2);
}

void change_to_prop_s(sfRenderTexture *tex , sfSprite *ply, window_t *win)
{
    coo_t tmp = sfSprite_getPosition(ply);
    coo_t tmp2 = sfSprite_getPosition(ply);
    coo_t size = win_size(win);
    float offset = (size.x - ((800 / 600.0) * size.y)) / 2;

    tmp.x = tmp.x / 1080 * size.y + offset;
    tmp.y = tmp.y / 1080 * size.y;
    sfSprite_setScale(ply, (coo_t){size.y / 1080, size.y / 1080});
    sfSprite_setPosition(ply, tmp);
    sfRenderTexture_drawSprite(tex, ply, NULL);
    sfSprite_setScale(ply, (coo_t){1, 1});
    sfSprite_setPosition(ply, tmp2);
}

void dmg_to_nme(fight_t *fight, window_t *win)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t info = c->saves[c->primary]->infos;
    int x = 120;

    if (sfCircleShape_getPosition(fight->circle).x == 120)
        x = 1320;
    place_circle(x, fight);
    fight->nme -= 15 + 15 * ((2.0 - ((ray_c *)win->menus[LIGHT])->lvl) / 2.0) +
    15 * (info.strength / 30.0);
}

void dis_circle(fight_t *fight, window_t *win)
{
    coo_t tmp = sfRectangleShape_getPosition(fight->player);
    coo_t tmp2 = sfCircleShape_getPosition(fight->circle);
    coo_t w_size = win_size(win);

    draw_game_bar(fight->tex, (coo_t){w_size.x / 50 * 49 - w_size.x / 6,
    w_size.y / 20}, (coo_t){w_size.x / 6, w_size.y / 25}, (coo_t)
    {fight->nme, 0});
    if (sqrt(pow(tmp.x + 50 - tmp2.x, 2) + pow(tmp.y + 50 - tmp2.y, 2)) > 115)
        return;
    dmg_to_nme(fight, win);
}
