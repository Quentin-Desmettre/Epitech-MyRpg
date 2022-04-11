/*
** EPITECH PROJECT, 2019
** decimal_to_hex
** File description:
** to convert decimal to hex
*/

#include "../../include/my.h"

int convert_d_to_b(unsigned int number)
{
    int size[500];
    int count = 0;

    while (number > 0) {
        size[count] = number % 2;
        number = number / 2;
        count++;
    }

    for (count = count - 1; count >= 0; count--)
        unsigned_nbr(size[count]);
}