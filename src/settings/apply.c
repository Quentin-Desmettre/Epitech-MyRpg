/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** apply.c
*/

#include <SFML/Graphics.h>
#include "rpg.h"

static void recreate_render_texture(window_t *win)
{
    sfRenderTexture_destroy(((settings_t *)win->menus[SETTINGS])->rtex);
    ((settings_t *)win->menus[SETTINGS])->rtex =
    sfRenderTexture_create(win->mode.width, win->mode.height, 0);
}

static void apply_mode(settings_t *se, window_t *win)
{
    bool is_fullscreen = se->full_screen->is_checked;

    if (is_fullscreen) {
        sfSprite_setColor(se->res_button->sprite,
        (sfColor){127, 127, 127, 255});
        win->mode = sfVideoMode_getDesktopMode();
    } else
        win->mode = available_modes[se->resolution];
    recreate_render_texture(win);
    win->win = sfRenderWindow_create(win->mode, "Backrooms",
    is_fullscreen ? sfFullscreen : sfClose, NULL);
    rescale_all(win);
}

void apply_settings(settings_t *se, window_t *win)
{
    apply_mode(se, win);
    sfRenderWindow_setFramerateLimit(win->win,
    available_framerates[se->framerate]);
    sfRenderWindow_setVerticalSyncEnabled(win->win, se->vsync->is_checked);
    update_all_texts(se);
    set_music_vol(se->music_vol);
    set_sound_vol(se->sfx_vol);
    set_musics_volume(get_music_vol());
    set_sounds_volume(get_sound_vol());
}
