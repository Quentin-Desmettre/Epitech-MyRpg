/*
** EPITECH PROJECT, 2021
** first_line_len
** File description:
** return the len of the first line of an array
*/

#include "../../include/my.h"

int first_line_len(int r, char *buffer)
{
    int count;
    int i = 0;
    char res[100];
    for (count = 0; buffer[count] != '\n'; count++) {
        if (buffer[count] >= 48 && buffer[count] <= 57) {
            res[i] = buffer[count];
            i++;
        } else {
            return (84);
        }
    }
    int size = my_strlen(res);
    return (size);
}