/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw_select.c
*/

#include "rpg.h"

static void draw_hider(sfRenderTexture *rtex, sfSprite *hider)
{
    sfVector2u size = sfRenderTexture_getSize(rtex);

    sfSprite_setPosition(hider, (sfVector2f){0, size.y * 0.8});
    sfSprite_setTextureRect(hider, (sfIntRect){0, 0, size.x, size.y * 0.2});
    sfRenderTexture_drawSprite(rtex, hider, NULL);
}

static void rescale_gui_player(gui_player_t *g, sfVector2f win_size)
{
    sfVector2f size = {win_size.x * ((1 - SPACING * 4) / 3), win_size.y * 0.7};
    sfVector2f sk_size = {size.x * 0.9, size.y * 0.5};

    sfRenderTexture_destroy(g->rtex);
    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    sfRectangleShape_setSize(g->border, size);
    set_sprite_size(g->skin, sk_size);
    sfSprite_setPosition(g->skin, (sfVector2f){(size.x - sk_size.x) * 0.5,
    (size.x - sk_size.x) * 0.5});
    set_sprite_size(g->stats_img, (sfVector2f){size.y * 0.066, size.y * 0.066});
    if (!my_strcmp(sfText_getString(g->stats), "Empty file")) {
        sfText_setCharacterSize(g->stats, size.x * 0.13);
        center_text(g->stats);
        sfText_setPosition(g->stats, (sfVector2f){size.x * 0.5, size.y * 0.5});
    } else {
        sfText_setPosition(g->stats,
        (sfVector2f){size.x * 0.1 + size.y * 0.1, size.y * 0.68});
        sfText_setCharacterSize(g->stats, (size.y * ((0.9 - 0.7)) / 3));
    }
}

void rescale_choose_save(choose_save_t *c, sfVector2f size)
{
    sfRenderTexture_destroy(c->rtex);
    c->rtex = sfRenderTexture_create(size.x, size.y, 0);
    for (int i = 0; i < 4; i++) {
        c->buttons[i]->container_size = size;
        update_button(c->buttons[i]);
        if (i < 3)
            rescale_gui_player(c->saves[i], size);
    }
}

const sfTexture *draw_choose_save(window_t *win)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    sfRenderTexture_clear(c->rtex, sfBlack);
    for (int i = 0; i < 3; i++)
        draw_gui_player(c->saves[i], c->rtex, i);
    draw_hider(c->rtex, c->hider);
    for (int i = 0; i < 4; i++)
        draw_button_to_rtex(c->buttons[i], c->rtex);
    sfRenderTexture_display(c->rtex);
    return sfRenderTexture_getTexture(c->rtex);
}
