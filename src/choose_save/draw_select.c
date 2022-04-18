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

void draw_rect_around(sfSprite *around, sfColor c,
sfRenderTexture *rtex)
{
    sfVector2f rect_size = get_sprite_size(around);
    sfRectangleShape *s = create_rectangle(rect_size,
    sfTransparent, rect_size.x * 0.02, c);

    sfRectangleShape_setPosition(s, sfSprite_getPosition(around));
    sfRenderTexture_drawRectangleShape(rtex, s, NULL);
    sfRectangleShape_destroy(s);
}

const sfTexture *draw_choose_save(window_t *win)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    sfSprite *tmp;

    sfRenderTexture_clear(c->rtex, sfBlack);
    for (int i = 0; i < 3; i++) {
        tmp = get_gui_player(c->saves[i], c->rtex, i);
        sfRenderTexture_drawSprite(c->rtex, tmp, NULL);
        if (c->secondary == i)
            draw_rect_around(tmp, (sfColor){64, 64, 64, 255}, c->rtex);
        if (c->primary == i)
            draw_rect_around(tmp, sfWhite, c->rtex);
        sfSprite_destroy(tmp);
    }
    draw_hider(c->rtex, c->hider);
    for (int i = 0; i < 4; i++)
        draw_button_to_rtex(c->buttons[i], c->rtex);
    sfRenderTexture_display(c->rtex);
    return sfRenderTexture_getTexture(c->rtex);
}
