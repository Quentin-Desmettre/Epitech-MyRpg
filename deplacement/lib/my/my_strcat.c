/*
** EPITECH PROJECT, 2019
** my_putstr
** File description:
** my_putstr
*/

#include "../../include/my.h"

char *my_strcat(char *first, char *last)
{
    int len_f = my_strlen(first);
    int len_l = my_strlen(last);
    int global_len = len_f + len_l;
    char *res = (char *)malloc(global_len + 1);
    for (int i = 0; i < len_f; i++) {
        res[i] = first[i];
    }
    for (int j = 0; j < len_l; j++) {
        res[j + len_f] = last[j];
    }
    res[global_len] = '\0';
    return (res);
}