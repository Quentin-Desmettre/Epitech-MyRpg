/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** button.h
*/

#ifndef BUTTON_H
    #define BUTTON_H
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
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
    float font_factor;
    int can_trigger;
    int base_char_size;
    sfSound *press;
    sfSound *release;
} button_t;

void destroy_button(button_t *b);
void hover_button(button_t *b, int is_on);
void press_button(button_t *b, int is_press);
void button_set_pos(button_t *b, sfVector2f pos);
void init_default(button_t *b);

// additional params: size, string, action
button_t *init_button(sfTexture *t, sfIntRect rect,
sfVector2f pos, ...) __attribute__((deprecated("Use build_button instead")));

///////////////////////////////////////////////////////////////////////////////
/// \brief Build a button according to parameters
/// \param format The format string. each parameter must be separated by 1 ,
/// \param sf sfVector2f, size factors (relative to container_size)
/// \param pf sfVector2f, pos factors (relative to container_size)
/// \param ff float, font size (text height = container_size.y * font_factor)
/// \param base_size sfVector2f, container size
/// \param release void (*)(void *), action to be executed on release
/// \param text char *, text to be display
/// \param texture sfTexture *, the texture to be used
/// \param rect sfIntRect, the texture rect
/// \param p_sf char *, Name of the audio file you want to be played on press
/// \param r_sf char *, Name of the audio file you want to be played on release
/// \return The built button
///////////////////////////////////////////////////////////////////////////////
button_t *build_button(char *format, ...);

///////////////////////////////////////////////////////////////////////////////
/// \brief Update the button position, according to it's given parameters and
/// the container size
/// \param b The button to update
///////////////////////////////////////////////////////////////////////////////
void update_button(button_t *b);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw the given button to the given RenderTexture
/// \param b The button to draw
/// \param rtex The renderTexture to draw to
///////////////////////////////////////////////////////////////////////////////
void draw_button_to_rtex(button_t *b, sfRenderTexture *rtex);

void button_move(button_t *b, sfVector2f vector);
void button_set_pos(button_t *b, sfVector2f pos);
void button_set_size(button_t *b, sfVector2f size);

bool is_on_button(sfVector2f pos, button_t *b);

///////////////////////////////////////////////////////////////////////////////
/// \brief For each given button, this function sets its hover mode to true
/// if the given coordinates are on the button; Else, it sets
/// the hover mode to false.
/// \param buttons The array of button to check
/// \param nb_button The size of the array
/// \param x The x coordinate to check
/// \param y The y coordinate to check
///////////////////////////////////////////////////////////////////////////////
void check_button_move(button_t **buttons, int nb_button, float x, float y);

///////////////////////////////////////////////////////////////////////////////
/// \brief For each given button, this function sets its press mode to true
/// if the given coordinates are on the button; Else, it sets the
/// press mode to false.
/// \param buttons The array of button to check
/// \param nb_button The size of the array
/// \param x The x coordinate to check
/// \param y The y coordinate to check
///////////////////////////////////////////////////////////////////////////////
void check_button_press(button_t **buttons, int nb_button, float x, float y);

///////////////////////////////////////////////////////////////////////////////
/// \brief For each given button, this function sets its press & hover mode to
/// false, and call the function pointer of the released button,
/// if it is not NULL.
/// \param buttons The array of button to check
/// \param nb_button The size of the array
/// \param pos The x & y coordinates to check
/// \param win The main window, to call the function pointer
/// \return 0 if no functions were called, else 1
///////////////////////////////////////////////////////////////////////////////
int check_button_release(button_t **buttons, int nb_button,
sfVector2f pos, void *win);

///////////////////////////////////////////////////////////////////////////////
/// \brief Get the button at given coordinates
/// \param buttons The array of button to check
/// \param nb_button The size of the array
/// \param x The x coordinate to check
/// \param y The y coordinate to check
/// \return -1 if there is no button at (x ; y), else the index of
/// the button in the array
///////////////////////////////////////////////////////////////////////////////
int button_at(button_t **buttons, int nb_button, float x, float y);

void set_pf(button_t *b, va_list va);
void set_sf(button_t *b, va_list va);
void set_base_size(button_t *b, va_list va);
void set_release(button_t *b, va_list va);
void set_text(button_t *b, va_list va);
void set_texture(button_t *b, va_list va);
void set_rect(button_t *b, va_list va);
void set_f_size(button_t *b, va_list va);
void set_button_enabled(button_t *b, int enabled);
void set_pfx(button_t *b, va_list va);
void set_rfx(button_t *b, va_list va);
void center_rectangle(sfRectangleShape *rect);

#endif
