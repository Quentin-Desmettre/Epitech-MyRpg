/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** fonts.c
*/

#include "globals.h"

sfFont *global_font(void)
{
    static sfFont *f = NULL;

    if (!f)
        f = sfFont_createFromFile(GLOBAL_FONT);
    return f;
}
