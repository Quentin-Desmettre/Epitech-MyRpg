/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** room
*/

#include "rpg.h"

maze_t *create_maze(level_t *level)
{
    maze_t *maze = my_malloc(sizeof(maze_t));

    memset(maze, 0, sizeof(maze_t));
    maze->perfect = 1;
    maze->nb_line = level->size.x;
    maze->nb_col = level->size.y;
    maze->index_end = maze->nb_line * maze->nb_col - 1;
    maze->grid = my_malloc(sizeof(char) * (maze->index_end + 1));
    maze->visited = my_malloc(sizeof(unsigned char) * (maze->index_end + 1));
    memset(maze->grid, 'X', sizeof(char) * (maze->index_end + 1));
    memset(maze->visited, 0, sizeof(unsigned char) * (maze->index_end + 1));
    maze->grid[0] = '*';
    maze->visited[0] = 1;
    return maze;
}

pile_t *create_pile(maze_t *maze)
{
    pile_t *pile = my_malloc(sizeof(pile_t));

    pile->count = 0;
    pile->path = my_malloc(sizeof(unsigned int) * (maze->index_end));
    push(maze, pile, 0);
    return pile;
}

void create_room(level_t *level)
{
    maze_t *maze = create_maze(level);
    pile_t *pile = create_pile(maze);

    while (pile->count) {
        if (!for_content(maze, pile, pile->path[pile->count - 1]))
            pop(pile);
    }
    level->room = my_malloc(sizeof(char *) * (maze->nb_line + 1));
    for (int i = 0; i < maze->nb_line; i++) {
        level->room[i] =
        my_strndup(maze->grid + (i * maze->nb_col), maze->nb_col);
    }
    level->room[maze->nb_line] = NULL;
    free(pile->path);
    free(maze->grid);
    free(maze->visited);
    free(pile);
    free(maze);
}
