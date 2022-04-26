/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** change_xp
*/

#include "rpg.h"

float get_xp_percent(npc_t *player)
{
    return ((float)player->xp / (float)player->xp_limit) * 100;
}

void remove_xp(game_t *game, int xp)
{
    game->player->xp -= xp;
    if (game->player->xp < 0) {
        game->player->xp_limit -= 5;
        game->player->level--;
        game->player->xp += game->player->xp_limit;
    }
    if (game->player->level < 1) {
        game->player->level = 1;
        game->player->xp = 0;
        game->player->xp_limit = 5;
    }
}

void add_xp(game_t *game, int xp)
{
    game->player->xp += xp;
    if (game->player->xp >= game->player->xp_limit) {
        game->player->xp = 0;
        game->player->level++;
        game->player->xp_limit += 5;
    }
}
