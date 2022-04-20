/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** room
*/

#include "rpg.h"

maze_t *create_maze(level_t *level)
{
    maze_t *maze = malloc(sizeof(maze_t));

    memset(maze, 0, sizeof(maze_t));
    maze->perfect = 1;
    maze->nb_line = level->size.x;
    maze->nb_col = level->size.y;
    maze->index_end = maze->nb_line * maze->nb_col - 1;
    maze->grid = malloc(sizeof(char) * (maze->index_end + 1));
    maze->visited = malloc(sizeof(unsigned char) * (maze->index_end + 1));
    memset(maze->grid, 'X', sizeof(char) * (maze->index_end + 1));
    memset(maze->visited, 0, sizeof(unsigned char) * (maze->index_end + 1));
    maze->grid[0] = '*';
    maze->visited[0] = 1;
    return maze;
}

pile_t *create_pile(maze_t *maze)
{
    pile_t *pile = malloc(sizeof(pile_t));

    pile->count = 0;
    pile->path = malloc(sizeof(unsigned int) * (maze->index_end));
    push(maze, pile, 0);
    return pile;
}

void init_room(level_t *level, maze_t *maze)
{
    level->room = malloc(sizeof(char *) * (maze->nb_line + 3));
    level->room[0] = malloc(sizeof(char) * (maze->nb_col + 3));
    level->room[maze->nb_line + 1] = malloc(sizeof(char) *
    (maze->nb_col + 3));
    for (int i = 0; i < maze->nb_col + 2; i++) {
        level->room[0][i] = 'X';
        level->room[maze->nb_line + 1][i] = 'X';
    }
    level->room[0][maze->nb_col + 2] = 0;
    level->room[maze->nb_line + 1][maze->nb_col + 2] = 0;
    level->room[maze->nb_line + 2] = 0;
    for (unsigned int i = 0; i < maze->index_end; i++) {
        if (maze->grid[i] == 'X' && !(rand() % COMPLEXITY))
            maze->grid[i] = '*';
    }
}

void create_room(level_t *level)
{
    maze_t *maze = create_maze(level);
    pile_t *pile = create_pile(maze);

    while (pile->count) {
        if (!for_content(maze, pile, pile->path[pile->count - 1]))
            pop(pile);
    }
    init_room(level, maze);
    for (int i = 0; i < maze->nb_line; i++) {
        level->room[i + 1] = malloc(sizeof(char) * (maze->nb_col + 3));
        level->room[i + 1][0] = 'X';
        my_strncpy(level->room[i + 1] + 1, maze->grid +
        (i * maze->nb_col), maze->nb_col);
        level->room[i + 1][maze->nb_col + 1] = 'X';
        level->room[i + 1][maze->nb_col + 2] = 0;
    }
    my_free("ppppp", pile->path, maze->grid, maze->visited, pile, maze);
}

void new_room(level_t *level, ray_c *light)
{
    my_free("P", level->room);
    create_room(level);
    for (int i = 0; i < level->size.y + 2; i++) {
        for (int j = 0; j < level->size.x + 2; j++)
            light->map[i][j] = (level->room[j][i] == 'X') ? '1' : '0';
    }
}
