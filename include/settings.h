/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** check_box.h
*/

#ifndef SETTINGS_H
    #define SETTINGS_H
    #include "my_clock.h"
    #include "button.h"
    #define SETTINGS_FILE ".conf"
    #include "sprite.h"
    #include <stdlib.h>
    #include "globals.h"
    #include <SFML/Audio.h>
    #define ALL_FLAGS S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH
    #define BOUNDS(s) (sfSprite_getGlobalBounds(s))
    #define set_music_vol(x) music_vol(1, x)
    #define set_sound_vol(x) sound_vol(1, x)

typedef struct {
    sfSprite *box;
    sfSprite *check;
    sfText *text;
    int is_checked;
} check_box;

typedef struct {
    check_box *vsync;
    check_box *full_screen;

    button_t *framerate_button;
    button_t *res_button;

    sfText *sfx_vol_text;
    sfText *sfx_text;
    button_t *sfx_plus;
    button_t *sfx_minus;

    sfText *music_vol_text;
    sfText *music_text;
    button_t *music_plus;
    button_t *music_minus;

    button_t *back;
    sfSprite *background;

    sfRenderTexture *rtex;

    p_clock_t *repeat_clock;

    int sfx_vol;
    int music_vol;
    int framerate;
    int resolution;
} settings_t;

static const sfIntRect check_rect[2] = {
    {0, 241, 82, 80},
    {0, 161, 80, 80}
};
static const sfIntRect settings_rects[11] = {
    {160, 161, 80, 80},
    {240, 161, 80, 80},
    {320, 81, 709, 118},
    {320, 199, 709, 118},
    {320, 317, 709, 118},
    {320, 435, 709, 118},
    {320, 553, 709, 118},
    {1028, 81, 709, 118},
    {1028, 199, 709, 118},
    {1028, 317, 709, 118},
    {80, 161, 80, 80}
};

static const sfVideoMode available_modes[] = {
    {800, 600, 32},
    {1024, 800, 32},
    {1920, 1080, 32}
};
static const int available_framerates[] = {
    30, 60, 90, 120, 144
};

void destroy_check_box(check_box *c);
void scale_check_box(check_box *c, sfVector2f factors);
void set_box_pos(check_box *c, sfVector2f pos);
void draw_check_box(sfRenderTexture *rtex, check_box *c);
check_box *init_check_box(int check, char const *text, float win_width);
void destroy_settings(settings_t *se);
void load_settings(settings_t *se);
void update_vol(float m_vol, float s_vol, char const *format, ...);
void sfx_minus(settings_t *se);
void sfx_plus(settings_t *se);
void music_minus(settings_t *se);
void music_plus(settings_t *se);
void update_all_texts(settings_t *se);
void reset_set_buttons(settings_t *se);
list_t **sound_list(void);
list_t **music_list(void);
float music_vol(int change, float new);
float sound_vol(int change, float new);

static inline void sftext_set_string_malloc(sfText *t, char *str)
{
    sfText_setString(t, str);
    free(str);
}

static inline float get_music_vol(void)
{
    return music_vol(0, 0);
}

static inline float get_sound_vol(void)
{
    return sound_vol(0, 0);
}

#endif
