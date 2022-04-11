/*
** EPITECH PROJECT, 2021
** display_arg
** File description:
** display_arg
*/

#include "../../include/my.h"

void display_array(int *array, int size)
{
    my_printf("\n");
    for (int i = 0; i < size; i++) {
        my_printf("%d ", array[i]);
    }
}