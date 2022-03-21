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
typedef struct {
    sfText *text;
    sfSprite *sprite;
    int is_press;
    int is_hover;
    sfVector2f pos;
    sfVector2f size;
    void (*action)(void *);
} button_t;

void destroy_button(button_t *b);
void hover_button(button_t *b, int is_on);
void press_button(button_t *b, int is_press);

// additional params: size, string, action
button_t *init_button(sfTexture *t, sfIntRect rect,
sfVector2f pos, ...);
void draw_button_to_rtex(button_t *b, sfRenderTexture *rtex);
void button_move(button_t *b, sfVector2f vector);
void button_set_pos(button_t *b, sfVector2f pos);
void button_set_size(button_t *b, sfVector2f size);
bool is_on_button(sfVector2f pos, button_t *b);
void check_button_move(button_t **buttons, int nb_button, float x, float y);
void check_button_press(button_t **buttons, int nb_button, float x, float y);
int button_at(button_t **buttons, int nb_button, float x, float y);

#endif
