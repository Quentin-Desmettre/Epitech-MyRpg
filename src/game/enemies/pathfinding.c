/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pathfinding.c
*/

#include "rpg.h"

static int lower_around(int **map,
sfVector2u pos, sfVector2u max)
{
    sfVector2u positions[4] = {
        {pos.x - 1, pos.y}, {pos.x + 1, pos.y},
        {pos.x, pos.y - 1}, {pos.x, pos.y + 1}
    };
    char is_valid[4];
    int min = INT32_MAX;
    int min_index = -1;

    for (int i = 0; i < 4; i++) {
        if (positions[i].x >= max.y || positions[i].y >= max.x)
            is_valid[i] = 0;
        else
            is_valid[i] = map[positions[i].x][positions[i].y] <= 0 ? 0 : 1;
    }
    for (int i = 0; i < 4; i++)
        if (is_valid[i] && map[positions[i].x][positions[i].y] < min) {
            min = map[positions[i].x][positions[i].y];
            min_index = i;
        }
    return min_index;
}

sfVector2f vector_to_objective(enemy_t *e,
game_t *g, ray_c *data, sfVector2f win_s)
{
    sfVector2u graph_max = get_graphic_size(g->level, data);
    sfVector2u logic_pos = graphic_pos_to_map(
    sfSprite_getPosition(e->enemy->sprite),
    graph_max, g->path->size, data->cell);
    int min = lower_around(g->path->map, logic_pos, g->path->size);
    sfVector2f dir;
    sfVector2f dirs[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    if (min < 0 || min > 3)
        return (sfVector2f){0, 0};
    dir = dirs[min];
    update_vector(&dir, e->enemy, win_s);
    return dir;
}

static int is_pos_valid(int **map,
sfVector2u pos, sfVector2u max, sfVector2u cur)
{
    unsigned px = pos.x;
    unsigned py = pos.y;
    unsigned cx = cur.x;
    unsigned cy = cur.y;

    if (px >= max.y || py >= max.x)
        return 0;
    if (map[px][py] == -1)
        return 0;
    if (map[px][py] == 0 || map[px][py] > map[cx][cy] + 2)
        return 1;
    return 0;
}

static void update_path_pos(int **map,
sfVector2u pos, sfVector2u max)
{
    sfVector2u positions[4] = {
        {pos.x - 1, pos.y}, {pos.x + 1, pos.y},
        {pos.x, pos.y - 1}, {pos.x, pos.y + 1}
    };
    char is_valid[4];

    if (map[pos.x][pos.y] >= MAX_DISTANCE)
        return;
    for (int i = 0; i < 4; i++) {
        is_valid[i] = is_pos_valid(map, positions[i], max, pos);
        if (is_valid[i])
            map[positions[i].x][positions[i].y] = map[pos.x][pos.y] + 1;
    }
    for (int i = 0; i < 4; i++)
        if (is_valid[i])
            update_path_pos(map, positions[i], max);
}

void update_path(path_t *p, level_t *l, ray_c *data, sfVector2f graphic_goal)
{
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u logic_pos = graphic_pos_to_map(graphic_goal,
    graph_max, p->size, data->cell);

    for (unsigned line = 0; line < p->size.y; line++)
        for (unsigned column = 0; column < p->size.x; column++)
            p->map[line][column] = (p->map[line][column] == -1) ? -1 : 0;
    if (logic_pos.x >= p->size.y || logic_pos.y >= p->size.x)
        return;
    p->map[logic_pos.x][logic_pos.y] = 1;
    update_path_pos(p->map, logic_pos, p->size);
}
