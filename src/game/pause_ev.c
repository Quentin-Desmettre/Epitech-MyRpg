/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pause_ev.c
*/

#include "rpg.h"

void draw_pause(pause_t *p, sfRenderTexture *rtex)
{
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
    if (ev.type == sfEvtMouseMoved)
        check_button_move(g->pause->buttons, 3, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(g->pause->buttons, 3,
        ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_button_release(g->pause->buttons, 3,
        (sfVector2f){ev.mouseButton.x, ev.mouseButton.y}, win);
    if (ev.type == sfEvtKeyReleased && ev.key.code == sfKeyEscape) {
        switch_clocks();
        g->is_paused = !g->is_paused;
    }
}

int check_pause(sfEvent ev, game_t *game)
{
    if (ev.type == sfEvtKeyReleased && ev.key.code == sfKeyEscape) {
        switch_clocks();
        game->is_paused = !game->is_paused;
        return 1;
    }
    return 0;
}
