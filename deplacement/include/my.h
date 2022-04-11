/*
** EPITECH PROJECT, 2021
** my_h
** File description:
** my_h
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "my_graphic.h"
#include <time.h>

#ifndef MY_H
    #define MY_H

    #define ALPHA(c) ((c) >= 97 && (c) <= 122)
    #define ALPHA_MAJ(c) ((c) >= 65 && (c) <= 90)
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define MAX(a, b) ((a) > (b) ? (a) : (b))

void my_putchar(char c);
int my_putnbr(int nb);
int my_putstr(char *str);
int my_strlen(char const *str);
int no_ascii(char number);
int my_atoi(char *str);
int first_line_int(int r, char *buffer);
int first_line_len(int r, char *buffer);
int my_printf(char *option, ...);
int my_strlen(char const *str);
int unsigned_nbr(unsigned int nb);
int convert_d_to_o(unsigned int number);
int convert_d_to_h(unsigned int number);
int convert_d_to_b(unsigned int number);
int convert_d_to_h_maj(unsigned int number);
void display_sign(int number);
int analyse_percent(char c, ...);
void display_array(int *array, int size);
int my_strcmp(char *first,  char *second);
char *my_strcat(char *first, char *last);

#endif /* MY_H */