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

void update_xp(void)
{
    window_t *win = window(NULL);
    game_t *g = win->menus[GAME];
    choose_save_t *c = win->menus[SELECT_SAVE];
    int prim = c->primary;

    if (prim < 0)
        return;
    c->saves[prim]->infos.xp = g->player->xp;
    c->saves[prim]->infos.xp_limit = g->player->xp_limit;
    c->saves[prim]->infos.level = g->player->level;
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
    update_xp();
}

void add_xp(game_t *game, int xp)
{
    game->player->xp += xp;
    if (game->player->xp >= game->player->xp_limit) {
        if (game->sounds[1])
            sfSound_play(game->sounds[1]);
        game->player->xp = 0;
        game->player->level++;
        game->player->xp_limit += 5;
        game->skills->data->pc += 2;
        game->skills->data->xp += 2;
    }
    update_xp();
}
