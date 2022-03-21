/*
** EPITECH PROJECT, 42
** new_project
** File description:
** short file description
*/

#ifndef NEW_H
    #define NEW_H

void destroy_check_box(check_box *c);
void scale_check_box(check_box *c, sfVector2f factors);
void set_box_pos(check_box *c, sfVector2f pos);
void draw_check_box(sfRenderTexture *rtex, check_box *c);
check_box *init_check_box(int check, char const *text, float win_width);
void destroy_buttons(settings_t *se);
void destroy_settings(settings_t *se);
void load_mode(int fd, settings_t *se);
void load_framerate(int fd, settings_t *se);
void load_vsync(int fd, settings_t *se);
void load_musics(int fd, settings_t *se);
void load_settings(settings_t *se);
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
button_t *init_set_button(const sfIntRect rect);
void init_all_settings_button(settings_t *se);
settings_t *init_settings(window_t *win);
void update_vol(float m_vol, float s_vol, char const *format, ...);
void sfx_minus(settings_t *se);
void sfx_plus(settings_t *se);
void music_minus(settings_t *se);
void music_plus(settings_t *se);
void update_all_texts(settings_t *se);
void reset_set_buttons(settings_t *se);

#endif
