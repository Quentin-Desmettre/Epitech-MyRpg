/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw_save.c
*/

#include "rpg.h"

static void check_button_repeat(create_save_t *c, window_t *win)
{
    int button;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    if (!sfMouse_isButtonPressed(sfMouseLeft))
        return;
    button = button_at(c->color_buttons, 6, mouse_pos.x, mouse_pos.y);
    if (button < 0 || !c->color_buttons[button]->is_press)
        return;
    if (get_elapsed_time(c->repeat) > REPEAT_DELAY)
        change_color(c, button);
}

static void draw_stats(create_save_t *c, sfVector2f size)
{
    sfVector2f tmp_pos;
    sfVector2f tmp_size;

    sfRenderTexture_drawText(c->rtex, c->stats_prompt, NULL);
    sfRenderTexture_drawText(c->rtex, c->pts_left, NULL);
    for (int i = 0; i < 8; i++) {
        if (!(i % 2)) {
            tmp_pos = c->stats_buttons[i]->pos;
            tmp_size = c->stats_buttons[i]->size;
            sfSprite_setTextureRect(c->stats, stats_rects[i / 2]);
            center_sprite(c->stats);
            set_sprite_size(c->stats, (sfVector2f){size.y * 0.1, size.y * 0.1});
            sfSprite_setPosition(c->stats,
            (sfVector2f){tmp_pos.x - tmp_size.y * 1.12, tmp_pos.y});
            sfRenderTexture_drawSprite(c->rtex, c->stats, NULL);
            sfRenderTexture_drawText(c->rtex, c->stats_val[i / 2], NULL);
        }
        draw_button_to_rtex(c->stats_buttons[i], c->rtex);
    }
}

static void draw_colors(create_save_t *c)
{
    for (int i = 0; i < 6; i++) {
        if (!(i % 2))
            sfRenderTexture_drawText(c->rtex, c->col_vals[i / 2], NULL);
        draw_button_to_rtex(c->color_buttons[i], c->rtex);
    }
}

const sfTexture *draw_create_save(window_t *win)
{
    create_save_t *c = win->menus[CREATE_SAVE];
    sfVector2f size = win_size(win);
    sfSprite *le = draw_line_edit(c->name,
    (sfVector2f){size.x * 0.3, size.x * 0.12});

    check_button_repeat(c, win);
    sfRenderTexture_clear(c->rtex, sfBlack);
    draw_button_to_rtex(c->actions[0], c->rtex);
    draw_button_to_rtex(c->actions[1], c->rtex);
    sfRenderTexture_drawSprite(c->rtex, le, NULL);
    sfRenderTexture_drawRectangleShape(c->rtex, c->skin_back, NULL);
    sfRenderTexture_drawText(c->rtex, c->prompt, NULL);
    sfRenderTexture_drawSprite(c->rtex, c->skin, NULL);
    draw_colors(c);
    draw_stats(c, size);
    sfRenderTexture_display(c->rtex);
    sfSprite_destroy(le);
    return sfRenderTexture_getTexture(c->rtex);
}
