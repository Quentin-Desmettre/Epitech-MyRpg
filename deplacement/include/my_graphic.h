/*
** EPITECH PROJECT, 2021
** my_h
** File description:
** my_h
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>

#ifndef GRAPHIC_H
    #define GRAPHIC_H

typedef struct game_object_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
    sfVector2f pos;
    sfVector2f size;
} game_object_t;

typedef struct button_s {
    sfSprite *sprite;
    sfIntRect r_rect;
    float thickness;
    sfRectangleShape *rect;
    sfTexture *texture;
    int click;
    void *callback;
    sfVector2f pos;
    sfVector2f size;
} button_t;

typedef struct text_s {
    char *string;
    sfText *text;
    sfVector2f pos;
    sfFont *font;
    int size;
} text_t;

typedef struct scene_s {
    game_object_t *obj;
    button_t *button1;
    button_t *button2;
    button_t *button3;
    int scene;
    text_t *text_quit;
    text_t *text_switch;
    int nb_text;
} scene_t;

/* PLAYER */
typedef struct player_s {
    int sprint;
    int normal_walk;
    int slow_walk;
    sfClock *clock_n_walk;
    sfTime time_n_walk;
    float seconds_n_walk;
    int speed;
    int moral;
    int in_game;
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfVector2f pos;
} player_t;

/* csfml button */
void center_button_x(button_t *button, sfRenderWindow *window);
void init_button(button_t *button, sfVector2f pos, sfVector2f size);
int button_is_clicked(button_t *button, sfVector2i p);
button_t *create_button(int p_x, int p_y, int s_x, int s_y);

/* move_player.c */
void check_move(player_t *player);
void move_right(player_t *p);
void move_left(player_t *p);
void move_up(player_t *p);
void move_down(player_t *p);

/* anime_move.c */
void what_move(player_t *player, int flag);
void anime_player(player_t *p, int move);
void anime_stand(player_t *p);

#endif /* GRAPHIC_H */