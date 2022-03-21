/*
** EPITECH PROJECT, 2021
** MY_MEMSET
** File description:
** Copies the char c to the first n characters of the string
*/

#include <stdlib.h>

int init_with(char *str, int c, int n)
{
    for (int i = 0; i < n; i++)
        str[i] = c;
    return 0;
}

void my_memset(void *what, int c, int n)
{
    char *cp = what;

    for (int i = 0; i < n; i++)
        cp[i] = c;
}

void free_str_array(char **array, int include_null)
{
    int i = 0;

    for (; array[i]; i++)
        free(array[i]);
    if (include_null)
        free(array[i]);
    free(array);
}
