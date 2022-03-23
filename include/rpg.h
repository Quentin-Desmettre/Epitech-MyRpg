/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rpg.h
*/

#ifndef RPG_H
    #define RPG_H
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include "settings.h"
    #include "sprite.h"

    #define REPEAT_DELAY 500000

typedef struct {
    button_t *buttons[5];
    sfSprite *background;
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
    SETTINGS, HOME, EXIT
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

window_t *window_create(int ac, char **av);
void rescale_all(window_t *win);
void update_transition(window_t *win, sfSprite *s);

#endif
