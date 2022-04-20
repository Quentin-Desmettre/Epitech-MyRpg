/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** safe.c
*/

#include "rpg.h"

sfSound *sound_func(void)
{
    char *a = NULL;
    write(2, "Gros connard!\nUtilise create_sound(char *) à la place de "
    "sfSound_create!\n", 68);
    *a = 3;
    return NULL;
}

sfMusic *music_func(char *s)
{
    s = NULL;
    write(2, "Gros connard!\nUtilise create_music(char *) à la place "
    "de sfMusic_createFromFile!\n", 82);
    *s = 3;
    return NULL;
}
