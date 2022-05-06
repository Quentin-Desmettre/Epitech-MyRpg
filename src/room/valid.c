/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** valid
*/

#include "rpg.h"

void set_door(ray_c *light, game_t *game)
{
    int door = rand() % (int)(game->level->size.y + 1);
    int door2 = (int)(rand() % 2 * (game->level->size.x + 1));

    light->map[door][door2] = '0';
    light->map[door][(int)(door2 == 0 ? 1 : game->level->size.x)] = '0';

    door = (rand() % 2 * (game->level->size.y + 1));
    door2 = rand() % (int)(game->level->size.x + 1);

    light->map[door][door2] = '0';
    light->map[(int)(door == 0 ? 1 : game->level->size.x)][door2] = '0';
}

unsigned char count(maze_t *maze, unsigned short col, unsigned short line)
{
    unsigned char count[2] = {0, 0};

    if (col + 1 < maze->nb_col &&
    maze->visited[line * maze->nb_col + col + 1] == 1)
        count[0]++;
    if (line + 1 < maze->nb_line &&
    maze->visited[(line + 1) * maze->nb_col + col] == 1)
        count[1]++;
    if (col > 0 && maze->visited[line * maze->nb_col + col - 1] == 1)
        count[0]++;
    if (line > 0 && maze->visited[(line - 1) * maze->nb_col + col] == 1)
        count[1]++;
    return count[0] + count[1];
}

unsigned char valid(maze_t *maze, unsigned short line,
unsigned short col, unsigned char dir)
{
    switch (dir) {
        case RIGHT_R :
            return (col + 1 < maze->nb_col && IS_VALID(maze, line * maze->
            nb_col + col + 1) && count(maze, col + 1, line) < 3);
        case DOWN_R :
            return (line + 1 < maze->nb_line && IS_VALID(maze, (line + 1) *
            maze->nb_col + col) && count(maze, col, line + 1) < 3);
        case LEFT_R :
            return (col > 0 && IS_VALID(maze, line * maze->nb_col + col - 1) &&
            count(maze, col - 1, line) < 3);
        case UP_R :
            return (line > 0 && IS_VALID(maze, (line - 1) * maze->nb_col + col)
            && count(maze, col, line - 1) < 3);
        default:
            return 0;
    }
}

void visit(maze_t *maze, unsigned short col,
unsigned short line, unsigned char dir)
{
    if ((dir == LEFT_R && col < 1) || (dir == RIGHT_R && col > maze->nb_col -
    2) || (dir == UP_R && line < 1) || (dir == DOWN_R && line > maze->nb_line -
    2))
        return;
    dir && dir != UP_R ? (col += MOVE_COL(dir)) : (line += MOVE_LINE(dir));
    if (!maze->visited[line * maze->nb_col + col])
        maze->visited[line * maze->nb_col + col] = 2;
}

unsigned char case_ok(maze_t *maze, unsigned short col, unsigned short line)
{
    for (unsigned char i = DOWN_R; i <= UP_R; i++) {
        if (valid(maze, line, col, i))
            return 1;
    }
    return 0;
}
