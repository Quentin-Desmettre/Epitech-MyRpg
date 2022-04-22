/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"

int scale_inventory(game_t *game, ray_c *data, window_t *win)
{
    sfVector2u size_win = sfRenderWindow_getSize(win->win);

    data->cell = size_win.y / (15.0);
    sfSprite_setScale(game->inventory->items_sprite[0]
    , (sfVector2f){0.5 / 1080 * size_win.y,  0.5 / 1080 * size_win.y});
    sfSprite_setScale(game->inventory->items_sprite[1]
    , (sfVector2f){0.5 / 1080 * size_win.y,  0.5 / 1080 * size_win.y});
    return 0;
}

void take_item(window_t *win, game_t *game, ray_c *data)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(game->player->sprite);
    sfFloatRect rect2 = {0, 0, 0, 0};
    list_t *tmp = game->items;
    int i = scale_inventory(game, data, win);

    if (tmp == NULL)
        return;
    do {
        sfSprite_setPosition(game->inventory->items_sprite[ITM_TYPE(tmp)],
        (coo_t){((item_t *)(tmp->data))->pos.x * data->cell + data->cell / 7.0,
        ((item_t *)(tmp->data))->pos.y * data->cell});
        rect2 = sfSprite_getGlobalBounds(game->inventory->items_sprite
        [ITM_TYPE(tmp)]);
        if (sfFloatRect_intersects(&rect, &rect2, 0)) {
            add_item(game->inventory, ITM_TYPE(tmp), 1);
            remove_node(&(game->items), i, free);
        } else
            i++;
        tmp = tmp->next;
    } while (tmp != game->items && tmp != 0);
}