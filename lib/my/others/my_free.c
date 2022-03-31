/*
** EPITECH PROJECT, 2021
** my_free.c
** File description:
** my_free
*/

#include <stdlib.h>
#include <stdarg.h>
#include "libmy.h"

void free_dbtable(void **table)
{
    for (int i = 0; table[i] != 0; i++)
        free(table[i]);
    free(table);
}

void my_free(char *to_free, ...)
{
    va_list list_arg;

    va_start(list_arg, to_free);
    for (int i = 0; to_free[i]; i++) {
        if (to_free[i] == 'p')
            free(va_arg(list_arg, void *));
        if (to_free[i] == 'P')
            free_dbtable(va_arg(list_arg, void **));
    }
    va_end(list_arg);
}
