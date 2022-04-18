/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** globals.h
*/

#ifndef GLOBALS_H
    #define GLOBALS_H
    #include <SFML/Graphics.h>
    #define GLOBAL_FONT "assets/font.ttf"
    #define GLOBAL_TEXTURE "assets/texture.png"

sfTexture *global_texture(void);
sfFont *global_font(void);
sfTexture *bars_texture(void);

#endif
