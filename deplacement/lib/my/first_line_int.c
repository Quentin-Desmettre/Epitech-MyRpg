/*
** EPITECH PROJECT, 2021
** first_line_int
** File description:
** return the first line of an array only composed of int
*/

#include "../../include/my.h"

int first_line_int(int r, char *buffer)
{
    int count;
    int i = 0;
    char res[10000];
    for (count = 0; buffer[count] != '\n'; count++) {
        if (buffer[count] >= 48 && buffer[count] <= 57) {
            res[i] = buffer[count];
            i++;
        } else {
            return (84);
        }
    }
    int int_res = my_atoi(res);
    return (int_res);
}