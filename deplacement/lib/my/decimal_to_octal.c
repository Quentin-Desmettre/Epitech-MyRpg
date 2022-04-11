/*
** EPITECH PROJECT, 2019
** decimal_to_octal
** File description:
** to convert decimal to octal
*/

#include "../../include/my.h"

int convert_d_to_o(unsigned int number)
{
    int res = 0;
    int pos = 1;

    if (number < 0) {
        return (84);
    } else {
        while (number != 0) {
            res = res + (number % 8) * pos;
            number = number / 8;
            pos = pos * 10;
        }
        unsigned_nbr(res);
    }
}