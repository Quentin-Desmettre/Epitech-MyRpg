/*
** EPITECH PROJECT, 2021
** Day 11
** File description:
** linked list structure
*/

#ifndef MY_LIST_H
    #define MY_LIST_H
    #include <stdlib.h>

typedef struct linked_list {
    void *data;
    struct linked_list *next;
    struct linked_list *prev;
} list_t;

typedef struct list {
    void *data;
    struct list *next;
} s_list_t;

void append_node(list_t **begin, void *data);
void remove_node(list_t **begin, unsigned offset, void (*freer)(void *));

#endif
