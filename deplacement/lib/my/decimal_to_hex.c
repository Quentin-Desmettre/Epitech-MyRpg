/*
** EPITECH PROJECT, 2019
** decimal_to_hex
** File description:
** to convert decimal to hex
*/

#include "../../include/my.h"

char letter_in_hex(int number)
{
    if (number == 10)
        return ('a');
    if (number == 11)
        return ('b');
    if (number == 12)
        return ('c');
    if (number == 13)
        return ('d');
    if (number == 14)
        return ('e');
    if (number == 15)
        return ('f');
}

int convert_d_to_h(unsigned int number)
{
    int size[10000];
    int res;
    int count = 0;
    while (number != 0) {
        size[count] = (number % 16);
        number = number / 16;
        count++;
    }

    for (count = count - 1; count >= 0; count--) {
        if (size[count] > 9)
            my_putchar(letter_in_hex(size[count]));
        else
            my_putnbr(size[count]);
    }
}