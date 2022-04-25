/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "player.h"

int **wa_to_ia(game_t *game, sfVector2u rs)
{
    int **ia = malloc(sizeof(int *) * rs.y);

    for (unsigned line = 0; line < rs.y; line++) {
        ia[line] = malloc(sizeof(int) * rs.x);
        for (unsigned col = 0; col < rs.x; col++) {
            ia[line][col] = ((game->level->room[line / 2][col / 2] == 'X') ||
            (game->level->room[(line - 1) / 2][col / 2] == 'X')) ? -1 : 0;
        }
    }
    return ia;
}

int is_pos_valid(int **map, sfVector2u pos, sfVector2u max, sfVector2u cur)
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

void update_path_pos(int **map, sfVector2u pos, sfVector2u max, sfVector2u goal)
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

sfVector2u lower_around(int **map, sfVector2u pos, sfVector2u max)
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

void extract_path(int **map, sfVector2u start, sfVector2u goal, sfVector2u max)
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

void clean_maze(int **map, sfVector2u size)
{
    for (unsigned line = 0; line < size.y; line++)
        for (unsigned column = 0; column < size.x; column++)
            map[line][column] = (map[line][column] == -1) ? -1 : 0;
}

void update_path(enemy_t *e, level_t *l, ray_c *data)
{
    sfVector2u graph_max = get_graphic_size(l, data);
    sfVector2u logic_pos = get_logic_pos(e, graph_max, data->cell);
    sfVector2u goal = graphic_pos_to_map(e->goal,
    graph_max, e->size, data->cell);

    clean_maze(e->map, e->size);
    e->map[logic_pos.x][logic_pos.y] = 1;
    update_path_pos(e->map, logic_pos, e->size, goal);
    extract_path(e->map, logic_pos, goal, e->size);
}

sfVector2f obj_to_v2f(int dir)
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
    sfVector2u positions[4] = {
        {pos.x - 1, pos.y}, {pos.x + 1, pos.y},
        {pos.x, pos.y - 1}, {pos.x, pos.y + 1}
    };
    int dir = -1;
    sfVector2f tmp;

    for (int i = 0; i < 4; i++) {
        if (positions[i].x < graph_max.y && positions[i].y < graph_max.x &&
        e->map[positions[i].x][positions[i].y] == -2) {
            dir = i;
        }
    }
    tmp = obj_to_v2f(dir);
    update_vector(&tmp, e->enemy, win_s);
    return tmp;
}

sfVector2f rnd_point(game_t *g, ray_c *data, npc_t *npc)
{
    sfVector2f size = g->level->size;
    sfVector2u max = {(size.y + 1) * data->cell,
    (size.x + 1) * data->cell + data->cell / 2};
    sfVector2f map_pos;
    sfVector2f base_pos = sfSprite_getPosition(npc->sprite);

    do {
        map_pos.x = my_rand(data->cell, max.x);
        map_pos.y = my_rand(data->cell, max.y);
        sfSprite_setPosition(npc->sprite, map_pos);
    } while (is_pnj_colliding(data, npc, g->level));
    sfSprite_setPosition(npc->sprite, base_pos);
    return map_pos;
}

void create_enemy(game_t *game, ray_c *data)
{
    enemy_t *en = malloc(sizeof(enemy_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    static const sfIntRect *pl_rects[5] = {
        pl_rect_top, pl_rect_down, pl_rect_left, pl_rect_right, pl_rect_idle
    };

    en->enemy = npc_create("tnicgv", "./assets/party.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, ENEMY_GRP, 2);
    sfSprite_setOrigin(en->enemy->sprite, (sfVector2f){32, 32});
    sfSprite_setPosition(en->enemy->sprite, rnd_point(game, data, en->enemy));
    en->enemy->dir = IDLE;
    en->decide_clock = sfClock_create();
    en->mov_vector = rand_dir();
    en->rnd_mve = my_rand(3000000, 5000000);
    en->rnd_wait = my_rand(1000000, 3000000);
    en->is_in_rush = 0;
    en->size = (sfVector2u){(game->level->size.y + 2) * 2,
    (game->level->size.x + 2) * 2};
    en->map = wa_to_ia(game, en->size);
    append_node(&game->enemies, en);
}
