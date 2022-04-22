/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw
*/

#include "rpg.h"
#include "inventory.h"

void draw_item(game_t *game, int item, int box)
{
    sfVector2u size = sfRenderTexture_getSize(game->rtex);
    sfText *text = init_text(nbr_to_str(game->inventory->data->nb_items[box])
    , size.y / 40);
    sfSprite *sprite = game->inventory->items_sprite[item];
    int line = box / 3;
    int col = box % 3;

    sfText_setPosition(text, (sfVector2f){877 + 114 * col, 363 + 114 * line});
    sfSprite_setScale(sprite, (sfVector2f){1, 1});
    sfSprite_setPosition(sprite, (sfVector2f)
    {797 + 114 * col, 293 + 114 * line});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfText_destroy(text);
}

void create_desc(sfText *text, int item)
{
    char **words = my_str_to_word_array(ITEM_TXT(item), " ");
    sfFloatRect pos = sfText_getGlobalBounds(text);
    char *str;
    const char *tmp;

    sfText_setString(text, "");
    for (int i = 0; words[i]; i++) {
        tmp = sfText_getString(text);
        str = str_concat(3, tmp, words[i], " ");
        sfText_setString(text, str);
        free(str);
        pos = sfText_getGlobalBounds(text);
        if (pos.left + pos.width > 1715) {
            str = str_concat(2, tmp, "\n");
            sfText_setString(text, str);
            free(str);
            i--;
        }
    }
    my_free("P", words);
}

void draw_item_info(game_t *game, int item, sfVector2u size)
{
    sfText *text = init_text(ITEM_TITLE(item), size.y / 40);
    sfSprite *sprite = game->inventory->items_sprite[item];

    sfSprite_setScale(sprite, (sfVector2f){2.5, 2.5});
    sfSprite_setPosition(sprite, (sfVector2f){1242, 233});
    sfText_setPosition(text, (sfVector2f){1330, 450});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    create_desc(text, item);
    sfText_setCharacterSize(text, size.y / 45);
    sfText_setPosition(text, (sfVector2f){1200, 500});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    sfText_destroy(text);
}

int get_stat(window_t *win, int i)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t infos = c->saves[c->primary]->infos;
    int nb_stats[4] = {infos.strength, infos.stamina, infos.speed,
    infos.mental_stability};

    return nb_stats[i];
}

void draw_stats(game_t *game, window_t *win)
{
    sfSprite *stats = sfSprite_create();
    sfVector2u size = sfRenderTexture_getSize(game->rtex);
    sfText *text = init_text("", size.y / 30);

    sfSprite_setTexture(stats, global_texture(), 0);
    set_sprite_size(stats, (sfVector2f){size.y * 0.066, size.y * 0.066});
    sfText_setPosition(text, (sfVector2f){size.x * 0.217, size.y * 0.74});
    sfSprite_setPosition(stats, (sfVector2f){size.x * 0.21, size.y * 0.69});
    for (int i = 0; i < 4; i++) {
        sfText_setString(text, nbr_to_str(get_stat(win, i)));
        sfSprite_setTextureRect(stats, stats_rects[i]);
        sfSprite_setScale(stats, (sfVector2f){0.3, 0.3});
        sfRenderTexture_drawSprite(game->rtex, stats, NULL);
        sfRenderTexture_drawText(game->rtex, text, NULL);
        sfSprite_move(stats, (sfVector2f){size.x * 0.05, 0});
        sfText_move(text, (sfVector2f){size.x * 0.05, 0});
    }
    if (game->inventory->item_selected != -1)
        draw_item_info(game, game->inventory->item_selected, size);
}

void draw_inventory(game_t *game, window_t *win)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfSprite *sprite = sfSprite_copy(game->player->sprite);

    sfSprite_setTextureRect(sprite, game->player->rects[4][0]);
    sfSprite_setScale(sprite, (sfVector2f){6, 6});
    sfSprite_setPosition(sprite, (sfVector2f){565, 535});
    sfRectangleShape_setFillColor(rect, (sfColor){50, 50, 50, 128});
    sfRectangleShape_setSize(rect, (sfVector2f){1920, 1080});
    if (!game->inventory->draw)
        return sfRectangleShape_destroy(rect);
    center_inventory(game, win);
    sfRenderTexture_drawRectangleShape(game->rtex, rect, NULL);
    sfRenderTexture_drawSprite(game->rtex, game->inventory->sprite, NULL);
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    for (int i = 0; i < 12; i++) {
        if (game->inventory->data->items[i] != -1)
            draw_item(game, game->inventory->data->items[i], i);
    }
    draw_stats(game, win);
    sfRectangleShape_destroy(rect);
}
