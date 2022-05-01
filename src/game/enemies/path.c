/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** path.c
*/

#include "rpg.h"

static int **wa_to_ia(char **map, sfVector2u rs)
{
    int **ia = malloc(sizeof(int *) * rs.y);

    for (unsigned line = 0; line < rs.y; line++) {
        ia[line] = malloc(sizeof(int) * rs.x);
        for (unsigned col = 0; col < rs.x; col++) {
            ia[line][col] = ((map[line / 2][col / 2] == 'X') ||
            (map[(line - 1) / 2][col / 2] == 'X')) ? -1 : 0;
        }
    }
    return ia;
}

void destroy_path(path_t *p)
{
    if (!p)
        return;
    for (unsigned i = 0; i < p->size.y; i++)
        free(p->map[i]);
    free(p->map);
    free(p);
}

path_t *create_path(char **map, sfVector2u map_size)
{
    path_t *p = malloc(sizeof(path_t));

    p->size = map_size;
    p->map = wa_to_ia(map, map_size);
    return p;
}
