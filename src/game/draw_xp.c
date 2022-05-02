/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw_xp
*/

#include "rpg.h"

void draw_game_bar(sfRenderTexture *rtex, sfVector2f pos,
sfVector2f size, sfVector2f types)
{
    int type = types.y;
    float percent = types.x / 100.0;
    sfIntRect const f_rect = bars_frames[1 + type];
    sfIntRect filled_rect = {f_rect.left, f_rect.top,
    f_rect.width * percent, f_rect.height};
    sfSprite *frame = init_sprite(bars_texture(), bars_frames[7], size);
    sfSprite *filled = init_sprite(bars_texture(), filled_rect,
    (sfVector2f){size.x * percent, size.y});
    sfSprite *logo = init_sprite(bars_texture(), bars_frames[4 + type],
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

void draw_xp(game_t *game, window_t *win)
{
    sfVector2f w_size = win_size(win);
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t infos = c->saves[c->primary]->infos;
    sfVector2f pos = {w_size.x / 50, w_size.y - w_size.y / 16};
    sfVector2f size = {w_size.x / 8, w_size.y / 25};
    float percent = get_xp_percent(game->player);

    draw_game_bar(game->rtex, pos, size, (sfVector2f){percent, 2});
    pos.y -= size.y + w_size.y / 60;
    draw_game_bar(game->rtex, pos, size,
    (sfVector2f){infos.m_health_percent, 1});
    pos.y -= size.y + w_size.y / 60;
    draw_game_bar(game->rtex, pos, size, (sfVector2f){infos.health_percent, 0});
    game->skills->data->tab[SPRINT] > 0 ? draw_sprint(game, w_size) : 0;
    game->skills->data->tab[CRY] > 0 ? draw_cry(game, w_size) : 0;
    game->skills->data->tab[FIND_EXIT] > 0 ? draw_find_exit(game, w_size) : 0;
}
