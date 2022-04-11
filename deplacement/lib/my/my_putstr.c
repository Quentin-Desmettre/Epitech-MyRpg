/*
** EPITECH PROJECT, 2019
** my_putstr
** File description:
** my_putstr
*/

#include "../../include/my.h"

int my_putstr(char *str)
{
    for (char i = 0; str[i] != '\0'; i++){
        my_putchar(str[i]);
    }
}
