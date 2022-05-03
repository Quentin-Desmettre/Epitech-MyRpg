/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** room.h
*/

#ifndef __ROOM__
    #define __ROOM__

    #include <sys/stat.h>
    #include <sys/stat.h>
    #include <threads.h>
    #include <unistd.h>
    #include <string.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <stdio.h>
    #include <time.h>

    #define PATH 'o'
    #define WALL 'X'
    #define TRAIL '*'

    #define DOWN_R 0
    #define RIGHT_R 1
    #define LEFT_R 2
    #define UP_R 3

    #define MOVE_COL(dir) (dir == RIGHT_R) ? 1 : -1
    #define MOVE_LINE(dir) (dir == DOWN_R) ? 1 : -1
    #define IS_VALID(maze, index) (!maze->visited[(index)])

typedef struct maze {
    char *grid;
    unsigned char *visited;
    unsigned int index_end;
    unsigned int perfect;
    unsigned short nb_line;
    unsigned short nb_col;
} maze_t;

typedef struct pile {
    unsigned int *path;
    unsigned int count;
} pile_t;

maze_t *get_args(int ac, char **av);
void find_path(maze_t *maze, pile_t *pile);
void push(maze_t *maze, pile_t *pile, unsigned int index);
unsigned char case_ok(maze_t *maze, unsigned short col, unsigned short line);
void visit(maze_t *maze, unsigned short col,
unsigned short line, unsigned char dir);
unsigned char valid(maze_t *maze, unsigned short line,
unsigned short col, unsigned char dir);
void pop(pile_t *pile);
unsigned char for_content(maze_t *maze, pile_t *pile, unsigned int index);

#endif
