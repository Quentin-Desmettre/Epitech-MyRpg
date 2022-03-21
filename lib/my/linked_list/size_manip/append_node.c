/*
** EPITECH PROJECT, 2021
** linked_list
** File description:
** append a node
*/

#include "libmy.h"

void append_node(linked_list_t **begin, void *data)
{
    linked_list_t *save = *begin;

    if (!(*begin)) {
        *begin = my_malloc(sizeof(linked_list_t));
        (*begin)->data = data;
        (*begin)->next = NULL;
        return;
    }
    while ((*begin)->next)
        (*begin) = (*begin)->next;
    (*begin)->next = my_malloc(sizeof(linked_list_t));
    *begin = (*begin)->next;
    (*begin)->data = data;
    (*begin)->next = NULL;
    *begin = save;
}
