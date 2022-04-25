/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pathfinding.c
*/

#include "rpg.h"

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

static sfVector2u lower_around(int **map,
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
            is_valid[i] = map[positions[i].x][positions[i].y] < 0 ? 0 : 1;
    }
    for (int i = 0; i < 4; i++)
        if (is_valid[i] && map[positions[i].x][positions[i].y] < min) {
            min = map[positions[i].x][positions[i].y];
            min_index = i;
        }
    return min_index >= 0 ? positions[min_index] : (sfVector2u){-1, -1};
}

static void extract_path(int **map,
sfVector2u start, sfVector2u goal, sfVector2u max)
{
    sfVector2u pos = goal;

    map[pos.x][pos.y] = -2;
    while (pos.x != start.x || pos.y != start.y) {
        pos = lower_around(map, pos, max);
        if (pos.x >= max.y || pos.y >= max.x)
            break;
        map[pos.x][pos.y] = -2;
    }
    for (unsigned line = 0; line < max.y; line++)
        for (unsigned column = 0; column < max.x; column++)
            map[line][column] = (map[line][column] > 0) ? 0 : map[line][column];
}

static void update_path_pos(int **map,
sfVector2u pos, sfVector2u max, sfVector2u goal)
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
            update_path_pos(map, positions[i], max, goal);
}

void update_path(enemy_t *e, level_t *l, ray_c *data)
{
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u logic_pos = get_logic_pos(e, graph_max, data->cell);
    sfVector2u goal = graphic_pos_to_map(e->goal,
    graph_max, e->size, data->cell);

    for (unsigned line = 0; line < e->size.y; line++)
        for (unsigned column = 0; column < e->size.x; column++)
            e->map[line][column] = (e->map[line][column] == -1) ? -1 : 0;
    e->map[logic_pos.x][logic_pos.y] = 1;
    update_path_pos(e->map, logic_pos, e->size, goal);
    extract_path(e->map, logic_pos, goal, e->size);
}
