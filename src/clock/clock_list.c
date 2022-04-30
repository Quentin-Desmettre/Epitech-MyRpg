/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** clock_list.c
*/

#include "rpg.h"

list_t **clocks(void)
{
    static list_t *list = NULL;

    return &list;
}

void destroy_clock(p_clock_t *p)
{
    list_t *list = *clocks();
    list_t *begin = list;
    int index = 0;

    clock_destroy(p);
    if (!begin)
        return;
    do {
        if (list->data == p) {
            remove_node(clocks(), index, 0);
            return;
        }
        list = list->next;
        index++;
    } while (list != begin);
}

p_clock_t *create_clock(void)
{
    p_clock_t *c = p_clock_create();

    append_node(clocks(), c);
    return c;
}

void pause_clocks(void)
{
    list_t *list = *clocks();
    list_t *begin = list;

    if (!begin)
        return;
    do {
        pause_clock(list->data);
        list = list->next;
    } while (list != begin);
}

void resume_clocks(void)
{
    list_t *list = *clocks();
    list_t *begin = list;

    if (!begin)
        return;
    do {
        resume_clock(list->data);
        list = list->next;
    } while (list != begin);
}
