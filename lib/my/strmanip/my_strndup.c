/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** my_strndup
*/

#include "libmy.h"

char *my_strndup(char const *src, int nb)
{
    int i = 0;
    char *dest = malloc(sizeof(char) * (nb + 1));

    while (i < nb) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return dest;
}
