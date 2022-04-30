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
    #include "game.h"

typedef struct {
    sfRectangleShape *hider;
    button_t *buttons[3];
} pause_t;

typedef struct win window_t;
typedef struct game game_t;

pause_t *create_pause(window_t *win);
void draw_pause(pause_t *p, sfRenderTexture *rtex);
void pause_events(game_t *g, window_t *win, sfEvent ev);

#endif /* !PAUSE_H_ */
