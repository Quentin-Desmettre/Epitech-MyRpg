/*
** EPITECH PROJECT, 2021
** Bootstrap my_printf
** File description:
** disp_stdarg
*/

#include "../../include/my.h"

int analyse_percent(char c, ...)
{
    va_list print;
    va_start(print, c);
    if (c == 's')
        my_putstr(va_arg(print, char *));
    if (c == 'c')
        my_putchar(va_arg(print, int));
    if (c == 'd' || c == 'i')
        my_putnbr(va_arg(print, int));
    if (c == 'u')
        unsigned_nbr(va_arg(print, int));
    if (c == 'o')
        convert_d_to_o(va_arg(print, int));
    if (c == 'x')
        convert_d_to_h(va_arg(print, int));
    if (c == 'X')
        convert_d_to_h_maj(va_arg(print, int));
    if (c == 'b')
        convert_d_to_b(va_arg(print, int));
    va_end(print);
}

int my_printf(char *str, ...)
{
    va_list arg;
    va_start(arg, str);

    int count;
    int count_p = 0;
    for (count = 0; str[count] != '\0'; count++) {
        if (str[count] == '%' && str[count + 1] == '%') {
            my_putchar('%');
            count++;
        } else if (str[count] == '%' && str[count + 1] == '+') {
            display_sign(va_arg(arg, int));
            count = count + 2;
        } else if (str[count] == '%') {
            analyse_percent(str[count + 1], va_arg(arg, int));
            count++;
        } else {
            my_putchar(str[count]);
        }
    }
    va_end(arg);
}