/*
** EPITECH PROJECT, 2021
** my_list_size
** File description:
** compute length of linked list
*/

#include "libmy.h"

int list_size(linked_list_t const *begin)
{
    int len = 0;

    while (begin) {
        len++;
        begin = begin->next;
    }
    return len;
}
