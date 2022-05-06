/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw
*/

#include "rpg.h"
#include "inventory.h"

int get_stat(window_t *win, int i)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t infos = c->saves[c->primary]->infos;
    int nb_stats[4] = {infos.strength, infos.speed, infos.defense,
    infos.thirst_res};

    return nb_stats[i];
}

void draw_to_game(game_t *game, window_t *win)
{
    sfVector2u center;
    const sfTexture* tex;
    sfVector2f size = win_size(win);
    sfSprite *sprite = sfSprite_create();

    draw_level(game, size);
    sfRenderTexture_display(game->inventory->rtex);
    tex = sfRenderTexture_getTexture(game->inventory->rtex);
    center = sfTexture_getSize(tex);
    sfSprite_setTexture(sprite, tex, sfTrue);
    sfSprite_setOrigin(sprite, (sfVector2f){center.x / 2, center.y / 2});
    sfSprite_setScale(sprite, (sfVector2f){SCALE(size), SCALE(size)});
    sfSprite_setPosition(sprite, game->inventory->pos);
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    sfSprite_destroy(sprite);
}

void draw_buttons(game_t *game, window_t *win, sfVector2f size)
{
    sfText *text = init_text("Use", 1080 / 40);
    float indent = 114 * (SCALE(size)) * 2;

    for (int i = 0; i < 2; i++) {
        sfSprite_setScale(game->inventory->buttons[i],
        (sfVector2f){(SCALE(size)), (SCALE(size))});
        sfSprite_setPosition(game->inventory->buttons[i], (sfVector2f)
        {POS_X(size, i * indent, i), POS_Y(size, indent, 2)});
        sfRenderTexture_drawSprite(game->rtex, game->inventory->buttons[i],
        NULL);
    }
    center_text(text);
    sfText_setPosition(text, (sfVector2f){848 + 114 * 0, 313 + 114 * 4});
    sfRenderTexture_drawText(game->inventory->rtex, text, NULL);
    sfText_setString(text, "Drop");
    center_text(text);
    sfText_setPosition(text, (sfVector2f){848 + 114 * 2, 313 + 114 * 4});
    sfRenderTexture_drawText(game->inventory->rtex, text, NULL);
    sfText_destroy(text);
    draw_to_game(game, win);
}

void draw_stats(game_t *game, window_t *win)
{
    sfSprite *stats = init_sprite_from_texture(global_texture());
    sfVector2u size = sfRenderTexture_getSize(game->rtex);
    sfText *text = init_text("", size.y / 30);

    sfText_setPosition(text, (sfVector2f){size.x * 0.217, size.y * 0.635});
    sfSprite_setPosition(stats, (sfVector2f){size.x * 0.21, size.y * 0.59});
    for (int i = 0; i < 4; i++) {
        sftext_set_string_malloc(text, nbr_to_str(get_stat(win, i)));
        sfSprite_setTextureRect(stats, stats_rects[i]);
        sfSprite_setScale(stats, (sfVector2f){0.3, 0.3});
        sfRenderTexture_drawSprite(game->inventory->rtex, stats, NULL);
        sfRenderTexture_drawText(game->inventory->rtex, text, NULL);
        sfSprite_move(stats, (sfVector2f){size.x * 0.05, 0});
        sfText_move(text, (sfVector2f){size.x * 0.05, 0});
    }
    sfText_destroy(text);
    sfSprite_destroy(stats);
    if (game->inventory->item_selected != -1)
        draw_item_info(game, game->inventory->item_selected, size);
    draw_buttons(game, win, win_size(win));
}

void draw_inventory(game_t *game, window_t *win)
{
    sfSprite *sprite = game->inventory->draw ?
    sfSprite_copy(game->player->sprite) : NULL;

    if (!game->inventory->draw)
        return;
    center_inventory(game, win);
    sfRenderTexture_clear(game->inventory->rtex, sfTransparent);
    sfSprite_setTextureRect(sprite, game->player->rects[4][0]);
    sfSprite_setScale(sprite, (sfVector2f){5.5, 5.5});
    sfSprite_setPosition(sprite, (sfVector2f){570, 440});
    sfRenderTexture_drawSprite(game->rtex, game->inventory->sprite, NULL);
    sfRenderTexture_drawSprite(game->inventory->rtex, sprite, NULL);
    sfSprite_destroy(sprite);
    for (int i = 0; i < 12; i++)
        if (game->inventory->data->items[i] != -1)
            draw_item(game, game->inventory->data->items[i], i, win_size(win));
    for (int i = 0; i < 4; i++)
        draw_button_to_rtex(game->inventory->stat_btns[i], game->rtex);
    draw_stats(game, win);
    draw_stats_pts(game, win);
}
