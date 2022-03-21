/*
** EPITECH PROJECT, 2021
** linked_list
** File description:
** delete a node at a given index
*/

#include "libmy.h"

void remove_node(linked_list_t **l, int index)
{
    linked_list_t *save = *l;
    linked_list_t *rm;

    if (index == 0) {
        rm = *l;
        *l = (*l)->next;
        free(rm);
        return;
    }
    for (int i = 0; i < index - 1; i++)
        (*l) = (*l)->next;
    rm = (*l)->next;
    (*l)->next = (*l)->next->next;
    free(rm);
    *l = save;
}
