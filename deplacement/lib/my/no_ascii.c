/*
** EPITECH PROJECT, 2021
** no_ascii
** File description:
** pour passer le ascii en non ascii : argv[i] - '0'
*/
#include "../../include/my.h"

int no_ascii(char number)
{
    int convert = number - '0';
    return (convert);
}