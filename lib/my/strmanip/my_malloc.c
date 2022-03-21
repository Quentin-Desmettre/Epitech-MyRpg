/*
** EPITECH PROJECT, 2021
** B-PSU-101-LIL-1-1-minishell1-quentin.desmettre
** File description:
** my_malloc.c
*/

#include <stdlib.h>
#include <unistd.h>

void *my_malloc(unsigned long long size)
{
    void *r = malloc(size);

    if (!r) {
        write(2, "Invalid malloc. Abort.\n", 23);
        exit(84);
    }
    return r;
}
