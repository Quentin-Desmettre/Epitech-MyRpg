/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** object_use
*/

#include "rpg.h"

void use_object(game_t *game, choose_save_t *c)
{
    player_info_t *infos = &c->saves[c->primary]->infos;

    if (game->inventory->item_selected == WATER) {
        add_quest_prog(game, 2, 1);
        infos->thirst_percent += 40;
        if (infos->thirst_percent > 100)
            infos->thirst_percent = 100;
        remove_item(game->inventory, game->inventory->item_selected, 1);
    }
    if (game->inventory->item_selected == PILLS) {
        add_quest_prog(game, 3, 1);
        infos->health_percent += 40;
        if (infos->health_percent > 100)
            infos->health_percent = 100;
        remove_item(game->inventory, game->inventory->item_selected, 1);
    }
}
