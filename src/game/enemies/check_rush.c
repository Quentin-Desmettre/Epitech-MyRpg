/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** check_rush.c
*/

#include "rpg.h"

int other_are_rushing(list_t *enemies, enemy_t *exclude)
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

void recreate_enemy(game_t *game, ray_c *light)
{
    while (game->enemies)
        remove_node(&game->enemies, 0, destroy_enemy);
    for (int i = 0; i < 10; i++)
        create_enemy(game, light);
}

void launch_combat(window_t *win)
{
    fight_t *fight = win->menus[FIGHT];
    game_t *g = GET_GAME(win);
    sfFloatRect hit = get_npc_hitbox(g->player);

    if (win->is_transition)
        return;
    change_pos(fight);
    g->splash = create_circular_splash(sfSprite_getPosition(g->player->sprite),
    (sfVector2f){hit.width * 0.3, hit.width * 0.3});
    fight->nme = 100;
}

int check_rush(enemy_t *en, ray_c *data, game_t *g, window_t *win)
{
    if (!en->is_in_rush) {
        en->is_in_rush = can_rush(en, data, g->player, win);
        en->enemy->speed += en->is_in_rush ? SPEED_ACC : 0;
        if (en->is_in_rush && !other_are_rushing(g->enemies, en)) {
            g->rush_music ? sfMusic_play(g->rush_music) : 0;
            g->is_flashing = 1;
            restart_clock(g->flash_clock);
            g->inventory->draw = 0;
            g->nb_flash = 3;
        }
    }
    if (en->is_in_rush) {
        rush_to_player(en, g->level, win, g->player->sprite);
        return 1;
    }
    return 0;
}
