/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw
*/

#include "rpg.h"
#include "inventory.h"

void draw_item(game_t *game, int item, int box, sfRenderWindow *win)
{
    sfSprite *sprite = game->inventory->items_sprite[item];
    int line = box / 3;
    int col = box % 3;

    sfSprite_setPosition(sprite, (sfVector2f)
    {797 + 114 * col, 293 + 114 * line});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
}

void draw_inventory(game_t *game, sfRenderWindow *win)
{
    if (!game->inventory->draw)
        return;
    sfRenderTexture_drawSprite(game->rtex, game->inventory->sprite, NULL);
    for (int i = 0; i < game->inventory->data->size; i++) {
        if (game->inventory->data->nb_items[i] > 0 &&
        game->inventory->data->items[i] != -1)
            draw_item(game, game->inventory->data->items[i], i, win);
    }
}
