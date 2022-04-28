/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pause
*/

#ifndef PAUSE_H_
    #define PAUSE_H_
    #include <SFML/Graphics.h>
    #include "button.h"
    #include "rpg.h"

typedef struct {
    sfRectangleShape *hider;
    sfSprite *background;
    button_t *buttons[3];
} pause_t;

typedef struct win window_t;

pause_t *create_pause(window_t *win);
void draw_pause(pause_t *p, sfRenderTexture *rtex);


#endif /* !PAUSE_H_ */
