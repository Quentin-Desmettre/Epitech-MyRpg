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
    destroy_game(win->menus[GAME]);
    sfClock_destroy(win->lum_clock);
    free_choose_save(win->menus[SELECT_SAVE]);
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
    if (win->state == GAME) {
        draw_room(win->menus[LIGHT], win->menus[GAME]);
        draw_map(win->menus[LIGHT], win->menus[GAME], win->win);
    }
    sfRenderWindow_display(win->win);
    sfTexture_destroy(cpy);
    sfSprite_destroy(s);
    sfRenderWindow_clear(win->win, sfBlack);
}

void set_next_win_state(window_t *win, int next)
{
    win->next_state = next;
    win->is_transition = 1;
}

static void poll_events(window_t *win)
{
    sfEvent ev;

    while (sfRenderWindow_pollEvent(win->win, &ev)) {
        if (ev.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
            set_next_win_state(win, EXIT);
        if (win->event[win->state])
            win->event[win->state](win, ev);
    }
    if (win->state == SETTINGS)
        check_sound_repeat(win, &ev);
    if (win->state == GAME)
        game_ev(win, ev);
}

void move_pl(window_t *win)
{
    game_t *game = win->menus[GAME];
    int tmp = 0;

    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        sfSprite_move(game->player->sprite, (sfVector2f){0, -3});
        game->player->dir = UP;
        tmp = 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) && !sfKeyboard_isKeyPressed(sfKeyZ)) {
        sfSprite_move(game->player->sprite, (sfVector2f){0, 3});
        game->player->dir = DOWN;
        tmp = 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        sfSprite_move(game->player->sprite, (sfVector2f){-3, 0});
        game->player->dir = LEFT;
        tmp = 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD) && !sfKeyboard_isKeyPressed(sfKeyQ)) {
        sfSprite_move(game->player->sprite, (sfVector2f){3, 0});
        game->player->dir = RIGHT;
        tmp = 1;
    }
    if (tmp == 0)
        game->player->dir = 4;
    if (sfKeyboard_isKeyPressed(sfKeyR))
        new_room(game->level, win->menus[LIGHT]);
}

int main(void)
{
    // player_info_t infos;

    // memset(&infos, 0, sizeof(player_info_t));
    // infos.health_percent = 35;
    // infos.m_health_percent = 76;
    // infos.mental_stability = 13;
    // my_strcpy(infos.player_name, "wesh_wesh");
    // infos.skin_comb = sfWhite;
    // infos.speed = 69;
    // infos.stamina = 42;
    // infos.strength = 3;

    // int fd = open("./saves/save1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // return write(fd, &infos, sizeof(player_info_t));
    window_t *win;

    if (!global_texture() || !global_font())
        return 84;
    win = window_create();
    while (sfRenderWindow_isOpen(win->win)) {
        poll_events(win);
        move_pl(win);
        draw(win);
    }
    win_destroy(win);
    sfFont_destroy(global_font());
    sfTexture_destroy(global_texture());
    sfTexture_destroy(player_texture());
    return 0;
}
