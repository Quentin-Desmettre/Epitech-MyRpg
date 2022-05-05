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
        infos->m_health_percent += 40;
        if (infos->m_health_percent > 100)
            infos->m_health_percent = 100;
    }
    if (game->inventory->item_selected == PILLS) {
        infos->health_percent += 40;
        if (infos->health_percent > 100)
            infos->health_percent = 100;
    }
    remove_item(game->inventory, game->inventory->item_selected, 1);
}
