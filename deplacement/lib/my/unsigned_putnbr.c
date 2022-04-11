/*
** EPITECH PROJECT, 2019
** my_putnbr
** File description:
** unsigned my_putnbr
*/

#include "../../include/my.h"

int reverse_u(unsigned int nb)
{
    int i;
    if (nb != 0) {
        i = nb % 10;
        if (i < 0) {
            i = -i;
        }
        nb /= 10;
        reverse_u(nb);
        my_putchar(i + 48);
    }
}

int unsigned_nbr(unsigned int nb)
{
    if (nb == 0) {
        my_putchar('0');
    }
    if (nb < 0) {
        return (84);
    }
    reverse_u(nb);
}