/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rpg.h
*/

#ifndef RPG_H
    #define RPG_H
    #include <string.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include "settings.h"
    #include "sprite.h"
    #include "level.h"
    #include "room.h"
    #include "game.h"
    #include "npc.h"

    #define REPEAT_DELAY 500000
    #define WIN_SIZE(win) ((sfVector2f){(win)->mode.width, (win)->mode.height})

typedef struct {
    button_t *buttons[5];
    sfSprite *background;
    sfRenderTexture *rtex;
} main_menu_t;

typedef struct win {
    sfVideoMode mode;
    sfRenderWindow *win;
    int state;
    void *menus[7];
    sfClock *lum_clock;

    int is_transition;
    int next_state;
    int framerate;

    const sfTexture* (*draw[6])(struct win *);
    void (*event[6])(struct win *, sfEvent ev);
    void (*update[6])(void *);

} window_t;

typedef enum {
    SETTINGS, HOME, EXIT, GAME
} state_t;

static const sfIntRect back_rect = {
    0, 0, 1, 1
};

// settings
void rescale_all(window_t *win);
void move_settings(settings_t *se, window_t *win);
void go_back(settings_t *se, window_t *win);
void update_full_screen(settings_t *se, window_t *win);
void update_vsync(settings_t *se, window_t *win);
void update_res(settings_t *se, window_t *win);
void update_framerate(settings_t *se, window_t *win);
void save_settings(settings_t *se);
void rescale_settings(settings_t *se, window_t *win);
void settings_ev(window_t *win, sfEvent ev);
void draw_set_button(sfRenderTexture *r, button_t *b);
const sfTexture *draw_settings(window_t *win);
void check_sound_repeat(window_t *win, sfEvent *ev);
int get_set_button_at(settings_t *se, sfEvent *ev);
void manage_settings_hover(sfEvent *ev, window_t *win);
void manage_settings_press(sfEvent *ev, window_t *win);
void manage_settings_release(sfEvent *ev, window_t *win);
sfVector2f conv(sfVector2f c, window_t *win);
settings_t *init_settings(window_t *win);
void apply_settings(settings_t *se, window_t *win);

// window
window_t *window_create(void);
void rescale_all(window_t *win);
void update_transition(window_t *win, sfSprite *s);
void set_next_win_state(window_t *win, int state);

// main menu
const sfTexture *draw_main_menu(window_t *m);
main_menu_t *create_main_menu(sfVector2f win_size);
void rescale_main_menu(main_menu_t *m, sfVector2f win_size);
void destroy_main_menu(main_menu_t *m);
void main_menu_ev(window_t *win, sfEvent ev);

// mainmenu events
void quit_main_menu(void *win);
void go_to_settings(void *win);
void go_to_local_save(void *win);
void go_to_map_editor(void *win);
void go_to_online_level(void *win);

// game
game_t *game_create(window_t *win);
void game_ev(window_t *win, sfEvent ev);
const sfTexture *draw_game(window_t *win);
void destroy_game(game_t *game);

#endif
