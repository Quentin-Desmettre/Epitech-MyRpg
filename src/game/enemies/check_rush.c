/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** check_rush.c
*/

#include "rpg.h"

static int other_are_rushing(list_t *enemies, enemy_t *exclude)
{
    list_t *begin = enemies;
    enemy_t *tmp;

    if (!begin)
        return 0;
    do {
        tmp = enemies->data;
        if (tmp->is_in_rush && tmp != exclude)
            return 1;
        enemies = enemies->next;
    } while (enemies != begin);
    return 0;
}

void launch_combat(void)
{
    print("HEHEHEHA\n");
    sfSleep((sfTime){500000});
    exit(0);
}

int check_rush(enemy_t *en, ray_c *data, game_t *g, window_t *win)
{
    if (!en->is_in_rush) {
        en->is_in_rush = can_rush(en, data, g->player);
        en->enemy->speed *= en->is_in_rush ? SPEED_ACC : 1;
        if (en->is_in_rush && !other_are_rushing(g->enemies, en)) {
            g->is_flashing = 1;
            sfClock_restart(g->flash_clock);
            g->inventory->draw = 0;
            g->nb_flash = 5;
        }
    }
    if (en->is_in_rush) {
        rush_to_player(en, g->level, win, g->player->sprite);
        return 1;
    }
    return 0;
}