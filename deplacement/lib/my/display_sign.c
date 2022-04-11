/*
** EPITECH PROJECT, 2019
** display sign
** File description:
** display sign
*/

#include "../../include/my.h"

void display_sign(int number)
{
    if (number < 0) {
        my_putnbr(number);
    } else {
        my_putchar('+');
        my_putnbr(number);
    }
}