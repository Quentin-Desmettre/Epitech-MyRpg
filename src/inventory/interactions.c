/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** interactions
*/

#include "rpg.h"
#include "inventory.h"

void inventory_buttons(game_t *game, sfEvent ev, sfVector2f size)
{
    item_t *item;
    float indent = 114 * (SCALE(size)) * 2;
    sfFloatRect mouse = {ev.mouseButton.x, ev.mouseButton.y, 1, 1};
    sfFloatRect buttons[2] = {{POS_X(size, 0, 0), POS_Y(size, indent, 2),
    103 * (SCALE(size)), 40 * (SCALE(size))}, {POS_X(size, indent, 1),
    POS_Y(size, indent, 2), 103 * (SCALE(size)), 40 * (SCALE(size))}};
    sfVector2f pos = sfSprite_getPosition(game->player->sprite);

    if (sfFloatRect_intersects(&mouse, &buttons[0], 0) &&
    game->inventory->item_selected != -1)
        remove_item(game->inventory, game->inventory->item_selected, 1);
    if (sfFloatRect_intersects(&mouse, &buttons[1], 0) &&
    game->inventory->item_selected != -1) {
        item = malloc(sizeof(item_t));
        item->type = game->inventory->item_selected;
        item->pos = (coo_t){pos.x / (size.y / 15), pos.y / (size.y / 15)};
        append_node(&game->items, item);
        remove_item(game->inventory, game->inventory->item_selected, 1);
    }
}

void inventory_events(game_t *game, sfEvent ev, window_t *win)
{
    sfFloatRect mouse = {ev.mouseButton.x, ev.mouseButton.y, 1, 1};

    for (int i = 0; game->inventory->data->items[i] != -1 && i < 12; i++) {
        if (sfFloatRect_intersects(&mouse, &game->inventory->items_pos[i], 0)) {
            game->inventory->item_selected = game->inventory->data->items[i];
            return;
        }
    }
    inventory_buttons(game, ev, win_size(win));
}
