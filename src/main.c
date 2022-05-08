/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"
#include "player.h"

static void win_destroy(window_t *win)
{
    sfRenderWindow_destroy(win->win);
    save_settings(win->menus[SETTINGS]);
    destroy_settings(win->menus[SETTINGS]);
    destroy_main_menu(win->menus[HOME]);
    dest_light(win->menus[LIGHT]);
    destroy_fight(win->menus[FIGHT]);
    destroy_game(win->menus[GAME]);
    destroy_clock(win->lum_clock);
    free_choose_save(win->menus[SELECT_SAVE]);
    if (win->music)
        destroy_music(win->music);
    if (win->close_sfx)
        destroy_sound(win->close_sfx);
    destroy_musics();
    destroy_sounds();
    destroy_cinematic(win->menus[CINE]);
    destroy_end(win->menus[END]);
    destroy_htp(win->menus[HTP]);
    free(win);
}

static void draw(window_t *win)
{
    const sfTexture* tex = win->draw[win->state] ?
    win->draw[win->state](win) : NULL;
    sfTexture *cpy = tex ? sfTexture_copy(tex) : NULL;
    sfSprite *s = init_sprite_from_texture(cpy);

    if (win->is_transition)
        update_transition(win, s);
    sfRenderWindow_drawSprite(win->win, s, NULL);
    if (win->state == GAME && !GET_GAME(win)->is_flashing &&
    !GET_GAME(win)->is_paused && !GET_GAME(win)->splash && !win->is_transition)
        move_pl(win);
    sfRenderWindow_display(win->win);
    sfTexture_destroy(cpy);
    sfSprite_destroy(s);
    sfRenderWindow_clear(win->win, sfBlack);
}

void set_next_win_state(window_t *win, int next)
{
    game_t *game = win->menus[GAME];

    win->next_state = next;
    win->is_transition = 1;
    if (next == EXIT && win->close_sfx)
        sfSound_play(win->close_sfx);
    if (next == GAME && game->ambient_music)
        sfMusic_play(game->ambient_music);
    else if (game->ambient_music)
        sfMusic_pause(game->ambient_music);
    if (next == FIGHT && game->rush_music)
        sfMusic_stop(game->rush_music);
    if (next == HOME && win->music)
        sfMusic_play(win->music);
}

static void poll_events(window_t *win)
{
    sfEvent ev;

    while (sfRenderWindow_pollEvent(win->win, &ev)) {
        if (win->is_transition)
            continue;
        if (ev.type == sfEvtClosed)
            set_next_win_state(win, EXIT);
        if (win->event[win->state])
            win->event[win->state](win, ev);
    }
    if (win->state == SETTINGS && !win->is_transition)
        check_sound_repeat(win, &ev);
}

int main(void)
{
    window_t *win;

    if (!are_all_textures_valid())
        return 84;
    my_srand();
    win = window_create();
    window(win);
    lazy_room(win);
    while (sfRenderWindow_isOpen(win->win)) {
        poll_events(win);
        draw(win);
    }
    win_destroy(win);
    sfFont_destroy(global_font());
    free_textures();
    destroy_clocks();
    return 0;
}
