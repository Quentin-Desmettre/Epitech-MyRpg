/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pause.c
*/

#include "rpg.h"
#include "pause.h"

void destroy_pause(pause_t *p)
{
    sfRectangleShape_destroy(p->hider);
    for (int i = 0; i < 3; i++)
        destroy_button(p->buttons[i]);
    free(p);
}

void pause_resume(void *win)
{
    window_t *w = win;
    game_t *g = w->menus[GAME];

    switch_clocks();
    g->is_paused = 0;
    if (g->rush_music && sfMusic_getStatus(g->rush_music) == sfPaused)
        sfMusic_play(g->rush_music);
}

void pause_exit(void *win)
{
    window_t *w = win;

    switch_clocks();
    if (GET_GAME(w)->rush_music)
        sfMusic_stop(GET_GAME(w)->rush_music);
    save_player(win);
    GET_GAME(w)->is_paused = 0;
    lazy_room(win);
    sfSprite_setPosition(GET_GAME(w)->player->sprite, (sfVector2f){128, 128});
    destroy_cinematic(w->menus[CINE]);
    w->menus[CINE] = create_cinematic(sfWhite);
    set_next_win_state(win, HOME);
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
    ",r_sf,release", (sfVector2f){0.1, 0.07}, (sfVector2f){0.07, 0.07}, 1.0,
    size, "?",
    global_texture(), button_rect, BUTTON_PRESS, BUTTON_RELEASE, go_to_htp);
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
