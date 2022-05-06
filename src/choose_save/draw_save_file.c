/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw.c
*/

#include "rpg.h"

static void draw_stats_icons(sfRenderTexture *rtex, sfSprite *stats_img)
{
    sfVector2u size = sfRenderTexture_getSize(rtex);

    sfSprite_setPosition(stats_img,
    (sfVector2f){size.x * 0.1, size.y * 0.67});
    for (int i = 0; i < 4; i++) {
        sfSprite_setTextureRect(stats_img, stats_rects[i]);
        set_sprite_size(stats_img,
        (sfVector2f){size.y * 0.066, size.y * 0.066});
        sfRenderTexture_drawSprite(rtex, stats_img, NULL);
        sfSprite_move(stats_img, (sfVector2f){0, size.y * 0.077});
    }
}

void draw_bar(sfRenderTexture *rtex, sfVector2f pos,
sfVector2f size, sfVector2f types)
{
    sfIntRect const f_rect = bars_frames[1 + (int)types.y];
    sfIntRect filled_rect = {f_rect.left, f_rect.top,
    f_rect.width * (types.x / 100.0), f_rect.height};
    sfSprite *frame = init_sprite(get_texture_by_name("assets/bars.png"),
    bars_frames[0], size);
    sfSprite *filled = init_sprite(get_texture_by_name("assets/bars.png"),
    filled_rect, (sfVector2f){size.x * (types.x / 100.0), size.y});
    sfSprite *logo = init_sprite(get_texture_by_name("assets/bars.png"),
    bars_frames[4 + (int)types.y],
    (sfVector2f){size.y, size.y});

    sfSprite_setPosition(frame, pos);
    sfSprite_setPosition(filled, pos);
    sfSprite_setPosition(logo, (sfVector2f){pos.x - size.y * 0.5, pos.y});
    sfRenderTexture_drawSprite(rtex, filled, NULL);
    sfRenderTexture_drawSprite(rtex, frame, NULL);
    sfRenderTexture_drawSprite(rtex, logo, NULL);
    sfSprite_destroy(filled);
    sfSprite_destroy(frame);
    sfSprite_destroy(logo);
}

static sfSprite *get_gui_sprite(gui_player_t *p)
{
    sfVector2u rtex_size = sfRenderTexture_getSize(p->rtex);

    sfRenderTexture_clear(p->rtex, sfBlack);
    sfRenderTexture_drawSprite(p->rtex, p->border, NULL);
    if (my_strcmp(sfText_getString(p->stats), "Empty file")) {
        sfRenderTexture_drawSprite(p->rtex, p->skin, NULL);
        sfRenderTexture_drawText(p->rtex, p->name, NULL);
        draw_bar(p->rtex, (sfVector2f){rtex_size.x * 0.2, rtex_size.y * 0.48},
        (sfVector2f){rtex_size.x * 0.7, rtex_size.y * 0.08},
        (sfVector2f){p->infos.health_percent, 0});
        draw_bar(p->rtex, (sfVector2f){rtex_size.x * 0.2, rtex_size.y * 0.57},
        (sfVector2f){rtex_size.x * 0.7, rtex_size.y * 0.08},
        (sfVector2f){p->infos.thirst_percent, 1});
        draw_stats_icons(p->rtex, p->stats_img);
    }
    sfRenderTexture_drawText(p->rtex, p->stats, NULL);
    sfRenderTexture_display(p->rtex);
    return init_sprite_from_texture(sfRenderTexture_getTexture(p->rtex));
}

sfSprite *get_gui_player(gui_player_t *p, sfRenderTexture *rtex, int index)
{
    sfSprite *s = get_gui_sprite(p);
    sfVector2u size = sfRenderTexture_getSize(rtex);
    sfVector2f pos = {SPACING * size.x +
    index * (size.x * ((1 - SPACING * 4) / 3 + SPACING)), size.y * 0.07};

    sfSprite_setPosition(s, pos);
    return s;
}
