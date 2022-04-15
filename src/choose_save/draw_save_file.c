/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw.c
*/

#include "rpg.h"

static void draw_pbar(sfRenderTexture *rtex, float percent, sfColor color,
sfVector2f sizes[2])
{
    sfVector2f size = sizes[0];
    sfVector2f pos = sizes[1];
    sfRectangleShape *filled = sfRectangleShape_create();
    sfRectangleShape *empty = sfRectangleShape_create();

    sfRectangleShape_setSize(filled, (sfVector2f){size.x * percent, size.y});
    sfRectangleShape_setSize(empty,
    (sfVector2f){size.x * (1 - percent), size.y});
    sfRectangleShape_setPosition(filled, pos);
    sfRectangleShape_setPosition(empty,
    (sfVector2f){pos.x + size.x * percent, pos.y});
    sfRectangleShape_setFillColor(filled, color);
    sfRectangleShape_setFillColor(empty, (sfColor){64, 64, 64, 255});
    sfRenderTexture_drawRectangleShape(rtex, filled, NULL);
    sfRenderTexture_drawRectangleShape(rtex, empty, NULL);
    sfRectangleShape_destroy(filled);
    sfRectangleShape_destroy(empty);
}

static void draw_stats_icons(sfRenderTexture *rtex, sfSprite *stats_img)
{
    sfVector2u size = sfRenderTexture_getSize(rtex);

    sfSprite_setPosition(stats_img,
    (sfVector2f){size.x * 0.1, size.y * 0.68});
    for (int i = 0; i < 4; i++) {
        sfSprite_setTextureRect(stats_img, stats_rects[i]);
        set_sprite_size(stats_img,
        (sfVector2f){size.y * 0.066, size.y * 0.066});
        sfRenderTexture_drawSprite(rtex, stats_img, NULL);
        sfSprite_move(stats_img, (sfVector2f){0, size.y * 0.077});
    }
}

static sfSprite *get_gui_sprite(gui_player_t *p)
{
    sfVector2u rtex_size = sfRenderTexture_getSize(p->rtex);

    sfRenderTexture_clear(p->rtex, sfBlack);
    sfRenderTexture_drawRectangleShape(p->rtex, p->border, NULL);
    if (my_strcmp(sfText_getString(p->stats), "Empty file")) {
        sfRenderTexture_drawSprite(p->rtex, p->skin, NULL);
        draw_pbar(p->rtex, p->infos.health_percent / 100.0,
        (sfColor){172, 4, 4, 255},
        (sfVector2f [2]){(sfVector2f){rtex_size.x * 0.8, rtex_size.y * 0.05},
        (sfVector2f){rtex_size.x * 0.1, rtex_size.y * 0.55}});
        draw_pbar(p->rtex, p->infos.m_health_percent / 100.0,
        (sfColor){30, 80, 175, 255},
        (sfVector2f [2]){(sfVector2f){rtex_size.x * 0.8, rtex_size.y * 0.05},
        (sfVector2f){rtex_size.x * 0.1, rtex_size.y * 0.62}});
        draw_stats_icons(p->rtex, p->stats_img);
    }
    sfRenderTexture_drawText(p->rtex, p->stats, NULL);
    sfRenderTexture_display(p->rtex);
    return init_sprite_from_texture(sfRenderTexture_getTexture(p->rtex));
}

void draw_gui_player(gui_player_t *p, sfRenderTexture *rtex, int index)
{
    sfSprite *s = get_gui_sprite(p);
    sfVector2u size = sfRenderTexture_getSize(rtex);
    sfVector2f pos = {SPACING * size.x +
    index * (size.x * ((1 - SPACING * 4) / 3 + SPACING)), size.y * 0.07};

    sfSprite_setPosition(s, pos);
    sfRenderTexture_drawSprite(rtex, s, NULL);
    sfSprite_destroy(s);
}
