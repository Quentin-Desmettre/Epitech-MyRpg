/*
** EPITECH PROJECT, 2019
** my_putstr
** File description:
** my_putstr
*/

#include "../../include/my.h"

int my_strcmp(char *first,  char *second)
{
    int size_f = my_strlen(first);
    int size_s = my_strlen(second);
    int verify = 0;
    if (size_f != size_s)
        return (84);
    for (int count = 0; count < size_f; count++) {
        if (first[count] == second[count]) {
            verify++;
        }
    }
    if (verify == size_f) {
        return (0);
    } else {
        return (84);
    }
}