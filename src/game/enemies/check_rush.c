/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** check_rush.c
*/

#include "rpg.h"

static sfVector2f obj_to_v2f(int dir)
{
    sfVector2f dirs[4] = {
        {0, -1}, {0, 1},
        {-1, 0}, {1, 0}
    };

    if (dir < 0 || dir > 3)
        return (sfVector2f){0, 0};
    return dirs[dir];
}

sfVector2f vector_to_objective(enemy_t *e, level_t *l,
ray_c *data, sfVector2f win_s)
{
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u pos = get_logic_pos(e, graph_max, data->cell);
    sfVector2u g_pos = graphic_pos_to_map(e->goal,
    graph_max, e->size, data->cell);
    sfVector2u positions[4] = {{pos.x - 1, pos.y},
    {pos.x + 1, pos.y}, {pos.x, pos.y - 1}, {pos.x, pos.y + 1}};
    sfVector2f gr_pos = sfSprite_getPosition(e->enemy->sprite);
    int dir = -1;
    sfVector2f tmp;

    for (int i = 0; i < 4; i++) {
        if (positions[i].x < graph_max.y && positions[i].y < graph_max.x &&
        e->map[positions[i].x][positions[i].y] == -2) {
            dir = i;
        }
    }
    tmp = !(g_pos.x == pos.x && g_pos.y == pos.y) ? obj_to_v2f(dir) :
    (sfVector2f){e->goal.x - gr_pos.x ? 1 : 0, e->goal.y - gr_pos.y ? 1 : 0};
    update_vector(&tmp, e->enemy, win_s);
    return tmp;
}

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
    write(1, "HEHEHEHA\n", 9);
    sfSleep((sfTime){500000});
    exit(0);
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
