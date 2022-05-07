/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** interactions
*/

#include "rpg.h"
#include "inventory.h"

void destroy_inventory(inventory_t *inventory)
{
    sfSprite_destroy(inventory->sprite);
    free(inventory->data);
    for (int i = 0; i < NB_ITEMS + 1; i++)
        sfSprite_destroy(inventory->items_sprite[i]);
    sfRenderTexture_destroy(inventory->rtex);
    for (int i = 0; i < 4; i++)
        destroy_button(inventory->stat_btns[i]);
    for (int j = 0; j < 2; j++)
        sfSprite_destroy(inventory->buttons[j]);
    free(inventory);
}

void add_stat(window_t *win, int type)
{
    game_t *game = win->menus[GAME];
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t *infos = &c->saves[c->primary]->infos;

    if (type == 0) {
        infos->strength += 1;
        game->player->attack += 1;
    } else if (type == 1) {
        infos->speed += 1;
        game->player->speed += 1;
    }
    if (type == 2) {
        infos->defense += 1;
        game->player->defense += 1;
    } else if (type == 3) {
        infos->thirst_res += 1;
        game->player->thirst += 1;
    }
    if (game->sounds[2])
        sfSound_play(game->sounds[2]);
}

void inventory_stats(game_t *game, sfEvent ev, window_t *win)
{
    sfFloatRect button;
    sfFloatRect mouse = {ev.mouseButton.x, ev.mouseButton.y, 1, 1};

    for (int i = 0; i < 4; i++) {
        button = sfSprite_getGlobalBounds
        (game->inventory->stat_btns[i]->sprite);
        if (sfFloatRect_intersects(&mouse, &button, NULL)
        && game->skills->data->xp > 0) {
            add_stat(win, i);
            game->skills->data->xp--;
            return;
        }
    }
}

void inventory_buttons(game_t *game, sfEvent ev, sfVector2f size, window_t *win)
{
    item_t *item;
    float indent = 114 * (SCALE(size)) * 2;
    sfFloatRect mouse = {ev.mouseButton.x, ev.mouseButton.y, 1, 1};
    sfFloatRect buttons[2] = {{POS_X(size, 0, 0), POS_Y(size, indent, 2),
    103 * (SCALE(size)), 40 * (SCALE(size))}, {POS_X(size, indent, 1),
    POS_Y(size, indent, 2), 103 * (SCALE(size)), 40 * (SCALE(size))}};
    sfVector2f pos = sfSprite_getPosition(game->player->sprite);
    int selected = game->inventory->item_selected;

    if (sfFloatRect_intersects(&mouse, &buttons[0], 0) && selected != -1)
        use_object(game, win->menus[SELECT_SAVE]);
    if (sfFloatRect_intersects(&mouse, &buttons[1], 0) && selected != -1) {
        item = malloc(sizeof(item_t));
        item->type = selected;
        item->pos = (coo_t){pos.x / (size.y / 15), pos.y / (size.y / 15)};
        append_node(&game->items, item);
        update_inventory();
        remove_item(game->inventory, selected, 1);
    }
    inventory_stats(game, ev, win);
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
    inventory_buttons(game, ev, win_size(win), win);
}
