/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"

void unblock_pl(ray_c *data, npc_t *player, level_t *level)
{
    coo_t size = level->size;

    for (int i = 0; i < size.y + 2; i++) {
        for (int j = 0; j < size.x + 2; j++)
            data->map[i][j] = pnj_colliding2(player, i, j, data) == 1 ? '0' :
            data->map[i][j];
    }
}

int scale_inventory(game_t *game, ray_c *data, window_t *win)
{
    sfVector2u size_win = sfRenderWindow_getSize(win->win);

    data->cell = size_win.y / (15.0);
    sfSprite_setScale(game->inventory->items_sprite[0]
    , (sfVector2f){0.5 / 1080 * size_win.y, 0.5 / 1080 * size_win.y});
    sfSprite_setScale(game->inventory->items_sprite[1]
    , (sfVector2f){0.5 / 1080 * size_win.y, 0.5 / 1080 * size_win.y});
    return 0;
}

void set_sprite_pos(game_t *game, item_t *it, ray_c *data)
{
    sfSprite_setPosition(game->inventory->items_sprite[it->type],
    (coo_t){it->pos.x * data->cell + data->cell / 7.0, it->pos.y * data->cell});
}

void update_inventory(void)
{
    window_t *win = window(NULL);
    game_t *g = win->menus[GAME];
    choose_save_t *c = win->menus[SELECT_SAVE];
    int prim = c->primary;

    if (prim < 0)
        return;
    c->saves[prim]->infos.inventory = *g->inventory->data;
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
        set_sprite_pos(game, tmp->data, data);
        rect2 = BOUNDS(game->inventory->items_sprite[ITM_TYPE(tmp)]);
        if (sfFloatRect_intersects(&rect, &rect2, 0) && ITM_TYPE(tmp) != 2) {
            add_item(game->inventory, ITM_TYPE(tmp), 1);
            update_inventory();
            tmp = tmp->next;
            remove_node(&(game->items), i, free);
            continue;
        }
        i++;
        tmp = tmp->next;
    } while (tmp != game->items && tmp != 0 && game->items != 0);
}
