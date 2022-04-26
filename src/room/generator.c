/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** generator
*/

#include "rpg.h"

void lazy_room(window_t *win)
{
    draw_map(win->menus[LIGHT], win->menus[GAME], win);
    new_room(win->menus[GAME], win->menus[LIGHT]);
}

void pop(pile_t *pile)
{
    if (pile->count == 0)
        return;
    pile->count--;
    pile->path[pile->count] = 0;
}

void push(maze_t *maze, pile_t *pile, unsigned int index)
{
    maze->visited[index] = 1;
    maze->grid[index] = '*';
    pile->path[pile->count] = index;
    pile->count++;
}

unsigned char get_dir(maze_t *maze, unsigned short col, unsigned short line)
{
    if (maze->grid[maze->index_end] != '*' &&
    col > maze->nb_col - 3 && line > maze->nb_line - 3) {
        if (col == maze->nb_col - 2 && line == maze->nb_line - 2)
            return rand() % 2 ? DOWN_R : RIGHT_R;
        return col == maze->nb_col - 1 ? DOWN_R : RIGHT_R;
    }
    return rand() % 4;
}

unsigned char for_content(maze_t *maze, pile_t *pile, unsigned int index)
{
    unsigned char dir = 0;
    unsigned char path_found = 0;
    unsigned short col = index % maze->nb_col;
    unsigned short line = (index - col) / maze->nb_col;

    for (; case_ok(maze, col, line); dir = get_dir(maze, col, line)) {
        if (valid(maze, line, col, dir)) {
            dir && dir != UP_R ?
            (col += MOVE_COL(dir)) : (line += MOVE_LINE(dir));
            index = line * maze->nb_col + col;
            push(maze, pile, index);
            path_found = 1;
        } else
            visit(maze, col, line, dir);
    }
    return path_found;
}
