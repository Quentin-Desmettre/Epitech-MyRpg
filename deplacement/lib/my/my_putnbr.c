/*
** EPITECH PROJECT, 2019
** my_putnbr
** File description:
** my_putnbr
*/

#include "../../include/my.h"

int reverse(int nb)
{
    int i;
    if (nb != 0) {
        i = nb % 10;
        if (i < 0) {
            i = -i;
        }
        nb /= 10;
        reverse(nb);
        my_putchar(i + 48);
    }
}

int my_putnbr(int nb)
{
    if (nb == 0) {
        my_putchar('0');
    }
    if (nb < 0) {
        my_putchar('-');
    }
    reverse(nb);
}