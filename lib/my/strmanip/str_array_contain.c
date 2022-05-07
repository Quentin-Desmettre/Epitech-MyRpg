/*
** EPITECH PROJECT, 2021
** B-PSU-101-LIL-1-1-minishell1-quentin.desmettre
** File description:
** str_array_contain.c
*/

#include "libmy.h"

int str_array_contain(char **array, char *str)
{
    for (int i = 0; array[i]; i++)
        if (my_strcmp(array[i], str) == 0)
            return 1;
    return 0;
}

int index_str_in_array(char const **array, char const *str)
{
    for (int i = 0; array[i]; i++)
        if (my_strcmp(array[i], str) == 0)
            return i;
    return -1;
}

int my_str_array_len(char **array)
{
    int len = 0;

    for (len = 0; array[len]; len++);
    return len;
}

void append_str_array(char ***array, char *val)
{
    int i;
    char **new = malloc(sizeof(char *) * (my_str_array_len(*array) + 2));

    for (i = 0; (*array)[i]; i++)
        new[i] = (*array)[i];
    new[i] = val;
    new[i + 1] = NULL;
    free(*array);
    *array = new;
}
