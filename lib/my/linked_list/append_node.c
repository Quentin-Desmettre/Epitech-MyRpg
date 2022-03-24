/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** append_node.c
*/

#include "linked_list.h"
#include <stdlib.h>

void append_node(list_t **begin, void *data)
{
    list_t *new = malloc(sizeof(list_t));

    new->data = data;
    if (!(*begin)) {
        *begin = new;
        new->next = new;
        new->prev = new;
        return;
    }
    new->next = (*begin);
    new->prev = (*begin)->prev;
    (*begin)->prev->next = new;
    (*begin)->prev = new;
}

void remove_node(list_t **begin, unsigned offset, void (*freer)(void *))
{
    list_t *s = *begin;
    list_t *next;
    list_t *prev;

    if (!s)
        return;
    for (unsigned i = 0; i < offset; i++)
        s = s->next;
    if (freer)
        freer(s->data);
    if (s == s->next)
        *begin = NULL;
    else {
        prev = s->prev;
        next = s->next;
        prev->next = next;
        next->prev = prev;
        *begin = next;
    }
    free(s);
}
