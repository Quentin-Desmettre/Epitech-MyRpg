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
    sfText *text = init_text(nbr_to_str(game->inventory->data->nb_items[box]), size.y / 40);
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

void draw_inventory(game_t *game, window_t *win)
{
    if (!game->inventory->draw)
        return;
    center_inventory(game, win);
    sfRenderTexture_drawSprite(game->rtex, game->inventory->sprite, NULL);
    for (int i = 0; i < 12; i++) {
        if (game->inventory->data->nb_items[i] > 0 &&
        game->inventory->data->items[i] != -1)
            draw_item(game, game->inventory->data->items[i], i);
    }
}
