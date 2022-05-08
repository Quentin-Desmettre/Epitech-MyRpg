/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pause_ev.c
*/

#include "rpg.h"

void scale_pause(pause_t *p)
{
    sfVector2f win_s = win_size(window(NULL));
    float but_size;

    sfRectangleShape_setSize(p->hider, win_s);
    for (int i = 0; i < 3; i++) {
        p->buttons[i]->container_size = win_s;
        update_button(p->buttons[i]);
    }
    but_size = p->buttons[2]->size.x;
    p->buttons[2]->size.y = but_size;
    set_sprite_size(p->buttons[2]->sprite, p->buttons[2]->size);
    p->buttons[2]->pos.y = p->buttons[2]->pos.x;
    sfSprite_setPosition(p->buttons[2]->sprite, p->buttons[2]->pos);
}

void draw_pause(pause_t *p, sfRenderTexture *rtex)
{
    scale_pause(p);
    sfRenderTexture_drawRectangleShape(rtex, p->hider, NULL);
    for (int i = 0; i < 3; i++)
        draw_button_to_rtex(p->buttons[i], rtex);
}

void switch_clocks(void)
{
    static uint64_t nb_call = 0;

    nb_call++;
    if (nb_call % 2)
        pause_clocks();
    else
        resume_clocks();
}

void pause_events(game_t *g, window_t *win, sfEvent ev)
{
    sfVector2f p = {ev.mouseButton.x, ev.mouseButton.y};

    if (ev.type == sfEvtMouseMoved)
        check_button_move(g->pause->buttons, 3, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(g->pause->buttons, 3, p.x, p.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_button_release(g->pause->buttons, 3, p, win);
    if (ev.type == sfEvtKeyReleased && ev.key.code == sfKeyEscape) {
        switch_clocks();
        g->is_paused = !g->is_paused;
        (g->is_paused && g->rush_music) ? sfMusic_pause(g->rush_music) : 0;
        if (!g->is_paused && g->rush_music &&
        sfMusic_getStatus(g->rush_music) == sfPaused)
            sfMusic_play(g->rush_music);
    }
    (g->is_paused && g->ambient_music) ? sfMusic_pause(g->ambient_music) : 0;
    if (!g->is_paused && g->ambient_music && win->next_state == GAME)
        sfMusic_play(g->ambient_music);
}

int check_pause(sfEvent ev, game_t *game)
{
    if (ev.type == sfEvtKeyReleased && ev.key.code == sfKeyEscape) {
        switch_clocks();
        game->is_paused = !game->is_paused;
        if (game->is_paused && game->rush_music)
            sfMusic_pause(game->rush_music);
        if (!game->is_paused && game->rush_music &&
        sfMusic_getStatus(game->rush_music) == sfPaused)
            sfMusic_play(game->rush_music);
        if (game->is_paused && game->ambient_music)
            sfMusic_pause(game->ambient_music);
        if (!game->is_paused && game->ambient_music)
            sfMusic_play(game->ambient_music);
        return 1;
    }
    return 0;
}
