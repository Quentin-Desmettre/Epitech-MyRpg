/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pause.c
*/

#include "rpg.h"
#include "pause.h"

static void switch_clocks(void)
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

void pause_resume(void *win)
{
    window_t *w = win;

    switch_clocks();
    GET_GAME(w)->is_paused = 0;
}

void pause_exit(void *win)
{
    window_t *w = win;

    switch_clocks();
    GET_GAME(w)->is_paused = 0;
    lazy_room(win);
    set_next_win_state(win, HOME);
}

void draw_pause(pause_t *p, sfRenderTexture *rtex)
{
    sfRenderTexture_drawRectangleShape(rtex, p->hider, NULL);
    for (int i = 0; i < 3; i++)
        draw_button_to_rtex(p->buttons[i], rtex);
}

void create_resume_exit(pause_t *p, sfVector2f size)
{
    float but_size;

    for (int i = 0; i < 2; i++)
        p->buttons[i] = build_button("sf,pf,ff,base_size,text,texture,rect,"
        "p_sf,r_sf,release", (sfVector2f){0.3, 0.15},
        (sfVector2f){0.5, 0.4 + i * 0.3}, 0.6, size,
        !i ? "Resume :)" : "Exit :(", global_texture(), button_rect,
        BUTTON_PRESS, BUTTON_RELEASE, !i ? pause_resume : pause_exit);
    p->buttons[2] = build_button("sf,pf,ff,base_size,text,texture,rect,p_sf"
    ",r_sf", (sfVector2f){0.1, 0.07}, (sfVector2f){0.07, 0.07}, 1.0, size, "?",
    global_texture(), button_rect, BUTTON_PRESS, BUTTON_RELEASE);
    but_size = p->buttons[2]->size.x;
    p->buttons[2]->size.y = but_size;
    set_sprite_size(p->buttons[2]->sprite, p->buttons[2]->size);
    p->buttons[2]->pos.y = p->buttons[2]->pos.x;
    sfSprite_setPosition(p->buttons[2]->sprite, p->buttons[2]->pos);
}

pause_t *create_pause(window_t *win)
{
    pause_t *p = malloc(sizeof(pause_t));
    sfVector2f size = win_size(win);

    p->hider = sfRectangleShape_create();
    sfRectangleShape_setFillColor(p->hider, (sfColor){0, 0, 0, 180});
    sfRectangleShape_setSize(p->hider, size);
    create_resume_exit(p, size);
    return p;
}
