/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "player.h"

void center_rectangle(sfRectangleShape *rect)
{
    sfVector2f size = sfRectangleShape_getSize(rect);

    sfRectangleShape_setOrigin(rect,
    (sfVector2f){size.x * 0.5, size.y * 0.5});
}

void create_colors_buttons(create_save_t *c, sfVector2f size,
sfVector2f p_pos, sfVector2f p_size)
{
    sfVector2f but_size = (sfVector2f){size.y * 0.1, size.y * 0.1};
    sfColor colors[3] = {sfRed, sfGreen, sfBlue};

    for (int i = 0; i < 6; i++) {
        if (!(i % 2)) {
            c->col_vals[i / 2] = init_text("255", size.x * (0.16 / 4));
            center_text(c->col_vals[i / 2]);
            sfText_setPosition(c->col_vals[i / 2], (sfVector2f){p_pos.x,
            p_pos.y + p_size.y * 0.8 + (i / 2) * but_size.y * 1.5});
            sfText_setColor(c->col_vals[i / 2], colors[i / 2]);
        }
        c->color_buttons[i] = build_button("base_size,release,texture,rect",
        size, NULL, global_texture(), settings_rects[i % 2]);
        button_set_size(c->color_buttons[i], but_size);
        button_set_pos(c->color_buttons[i], (sfVector2f){i % 2 ?
        p_pos.x + size.x * 0.08 : p_pos.x - size.x * 0.08,
        p_pos.y + p_size.y * 0.8 + (i / 2) * but_size.y * 1.5});
    }
}

void create_stats_buttons(create_save_t *c, sfVector2f size)
{
    sfVector2f but_size = (sfVector2f){size.y * 0.1, size.y * 0.1};
    sfVector2f but_pos;
    float x_factors[4] = {0.43, 0.57, 0.78, 0.92};

    for (int i = 0; i < 8; i++) {
        c->stats_buttons[i] = build_button("base_size,release,texture,rect",
        size, NULL, global_texture(), settings_rects[i % 2]);
        button_set_size(c->stats_buttons[i], but_size);
        but_pos.x = size.x * x_factors[i % 4];
        but_pos.y = size.y * (i > 3 ? 0.75 : 0.6);
        button_set_pos(c->stats_buttons[i], but_pos);
        if (!(i % 2)) {
            c->stats_val[i / 2] = init_text("0", size.x * 0.04);
            center_text(c->stats_val[i / 2]);
            sfText_setPosition(c->stats_val[i / 2],
            (sfVector2f){but_pos.x + size.x * (x_factors[1] - x_factors[0]) / 2,
            but_pos.y});
        }
    }
    c->pts_left = init_text("Points left: 4", size.x * 0.03);
    center_text(c->pts_left);
    sfText_setPosition(c->pts_left, (sfVector2f){size.x * 0.42, size.y * 0.9});
    c->stats_prompt =
    init_text("Choose your base stats wisely.", size.x * 0.04);
    sfText_setPosition(c->stats_prompt,
    (sfVector2f){size.x * 0.35, size.y * 0.43});
}

create_save_t *create_create_save(sfVector2f size, int f_no)
{
    create_save_t *c = malloc(sizeof(create_save_t));
    sfVector2f le_size = {size.x * 0.6, size.y * 0.2};
    sfVector2f le_pos = {size.x * 0.3, size.x * 0.12};
    sfVector2f p_pos = {size.x * 0.15, le_pos.y + le_size.y * 0.5};
    sfVector2f p_size = {size.x * 0.2, size.x * 0.2};

    c->rtex = sfRenderTexture_create(size.x, size.y, 0);
    c->stats = init_sprite_from_texture(global_texture());
    c->background = init_sprite_from_texture(global_texture());
    c->skin = init_sprite(player_texture(), pl_rect_idle[0], p_size);
    center_sprite(c->skin);
    sfSprite_setPosition(c->skin, p_pos);
    c->skin_back = create_rectangle(p_size, sfBlack,
    size.x * 0.2 * 0.02, sfWhite);
    center_rectangle(c->skin_back);
    sfRectangleShape_setPosition(c->skin_back, p_pos);
    c->name = create_line_edit(le_size, "", 12);
    for (int i = 0; i < 2; i++)
        c->actions[i] = build_button("sf,pf,ff,base_size,release,text,texture,"
        "rect,p_sf,r_sf", (sfVector2f){0.2, 0.1}, (sfVector2f){0.65 + 0.22 * i, 0.9},
        0.65, size, NULL, i ? "Create" : "Cancel", global_texture(),
        button_rect, BUTTON_PRESS, BUTTON_RELEASE);
    scale_line_edit(c->name, le_size);
    c->prompt = init_text("Name your character.", size.y * 0.07);
    sfText_setPosition(c->prompt, (sfVector2f){le_pos.x, size.y * 0.06});
    create_colors_buttons(c, size, p_pos, p_size);
    create_stats_buttons(c, size);
    c->repeat = sfClock_create();
    set_button_enabled(c->actions[1], 0);
    c->f_no = f_no;
    return c;
}

void check_button_repeat(create_save_t *c, window_t *win)
{
    int button;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(win->win);

    if (!sfMouse_isButtonPressed(sfMouseLeft))
        return;
    button = button_at(c->color_buttons, 6, mouse_pos.x, mouse_pos.y);
    if (button < 0 || !c->color_buttons[button]->is_press)
        return;
    if (sfClock_getElapsedTime(c->repeat).microseconds > REPEAT_DELAY)
        change_color(c, button);
}

const sfTexture *draw_create_save(window_t *win)
{
    create_save_t *c = win->menus[CREATE_SAVE];
    sfVector2f size = WIN_SIZE(win);
    sfSprite *le = draw_line_edit(c->name,
    (sfVector2f){size.x * 0.3, size.x * 0.12});
    sfVector2f tmp_pos;
    sfVector2f tmp_size;

    check_button_repeat(c, win);
    sfRenderTexture_clear(c->rtex, sfBlack);
    //sfRenderTexture_drawSprite(c->rtex, c->background, NULL);
    draw_button_to_rtex(c->actions[0], c->rtex);
    draw_button_to_rtex(c->actions[1], c->rtex);
    sfRenderTexture_drawSprite(c->rtex, le, NULL);
    sfRenderTexture_drawRectangleShape(c->rtex, c->skin_back, NULL);
    sfRenderTexture_drawText(c->rtex, c->prompt, NULL);
    sfRenderTexture_drawSprite(c->rtex, c->skin, NULL);
    for (int i = 0; i < 6; i++) {
        if (!(i % 2))
            sfRenderTexture_drawText(c->rtex, c->col_vals[i / 2], NULL);
        draw_button_to_rtex(c->color_buttons[i], c->rtex);
    }
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
    sfRenderTexture_display(c->rtex);
    sfSprite_destroy(le);
    return sfRenderTexture_getTexture(c->rtex);
}
