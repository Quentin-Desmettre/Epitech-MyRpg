/*
** EPITECH PROJECT, 2021
** my_atoi
** File description:
** personal atoi
*/

#include "../../include/my.h"

int my_atoi(char *str)
{
    int a = 0;
    int count = 0;
    int neg = 1;
    if (str[0] == '-') {
        neg = -1;
        count = count + 1;
        while (str[count] != '\0') {
            a = a * 10 + (str[count] - '0');
            count++;
        }
        return (-a);
    } else {
        while (str[count] != '\0') {
            a = a * 10 + (str[count] - '0');
            count++;
        }
        return (a);
    }
}