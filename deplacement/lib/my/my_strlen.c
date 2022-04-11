/*
** EPITECH PROJECT, 2021
** Task03
** File description:
** Count and return
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int i = 0;

    for (i; str[i] != '\0'; i++) {}
    return (i);
}
