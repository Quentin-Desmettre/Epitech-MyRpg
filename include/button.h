/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** button.h
*/

#ifndef BUTTON_H
    #define BUTTON_H
    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "sprite.h"
    #include "globals.h"
    #include "libmy.h"

typedef struct {
    sfText *text;
    sfSprite *sprite;
    int is_press;
    int is_hover;
    sfVector2f pos;
    sfVector2f size;
    void (*action)(void *);
    sfVector2f size_fac;
    sfVector2f pos_fac;
    sfVector2f container_size;
} button_t;

void destroy_button(button_t *b);
void hover_button(button_t *b, int is_on);
void press_button(button_t *b, int is_press);

// additional params: size, string, action
button_t *init_button(sfTexture *t, sfIntRect rect,
sfVector2f pos, ...);

/// \brief Build a button according to parameters
/// \param format The format string.
/// The available parameters are:
///  sf (sfVector2f, size factors), pf (same),
///  base_size (sfVector2f, container size),
///  release (void (*)(void *), action on release),
///  text (char *), texture (sfTexture *), rect (sfIntRect)
button_t *build_button(char *format, ...);
void update_button(button_t *b);
void draw_button_to_rtex(button_t *b, sfRenderTexture *rtex);
void button_move(button_t *b, sfVector2f vector);
void button_set_pos(button_t *b, sfVector2f pos);
void button_set_size(button_t *b, sfVector2f size);
bool is_on_button(sfVector2f pos, button_t *b);
void check_button_move(button_t **buttons, int nb_button, float x, float y);
void check_button_press(button_t **buttons, int nb_button, float x, float y);
int button_at(button_t **buttons, int nb_button, float x, float y);

void set_pf(button_t *b, va_list va);
void set_sf(button_t *b, va_list va);
void set_base_size(button_t *b, va_list va);
void set_release(button_t *b, va_list va);
void set_text(button_t *b, va_list va);
void set_texture(button_t *b, va_list va);
void set_rect(button_t *b, va_list va);

#endif
