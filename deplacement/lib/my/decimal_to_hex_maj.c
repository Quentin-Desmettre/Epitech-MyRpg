/*
** EPITECH PROJECT, 2019
** decimal_to_hex
** File description:
** to convert decimal to hex in maj
*/

#include "../../include/my.h"

char letter_in_hex_maj(int number)
{
    if (number == 10)
        return ('A');
    if (number == 11)
        return ('B');
    if (number == 12)
        return ('C');
    if (number == 13)
        return ('D');
    if (number == 14)
        return ('E');
    if (number == 15)
        return ('F');
}

int convert_d_to_h_maj(unsigned int number)
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
            my_putchar(letter_in_hex_maj(size[count]));
        else
            my_putnbr(size[count]);
    }
}