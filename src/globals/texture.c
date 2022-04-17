/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** textures.c
*/

#include "globals.h"

sfTexture *global_texture(void)
{
    static sfTexture *t = 0;

    if (!t)
        t = sfTexture_createFromFile(GLOBAL_TEXTURE, NULL);
    return t;
}

sfTexture *player_texture(void)
{
    static sfTexture *t = 0;

    if (!t)
        t = sfTexture_createFromFile("assets/player.png", NULL);
    return t;
}
