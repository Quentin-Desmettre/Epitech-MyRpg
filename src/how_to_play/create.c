/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"

void quit_htp(void *win)
{
    window_t *w = win;
    how_to_play_t *h = w->menus[HTP];

    set_next_win_state(win, h->from);
}

void next_page(void *win)
{
    window_t *w = win;
    how_to_play_t *h = w->menus[HTP];

    h->pages = h->pages->next;
}

void prev_page(void *win)
{
    window_t *w = win;
    how_to_play_t *h = w->menus[HTP];

    h->pages = h->pages->prev;
}

void destroy_htp(how_to_play_t *h)
{
    while (h->pages)
        remove_node(&h->pages, 0, (void (*)(void *))sfSprite_destroy);
    destroy_button(h->quit);
    destroy_button(h->prev);
    destroy_button(h->next);
    sfRenderTexture_destroy(h->rtex);
    free(h);
}

how_to_play_t *create_how_to_play(void)
{
    how_to_play_t *h = malloc(sizeof(how_to_play_t));

    h->rtex = sfRenderTexture_create(1, 1, 0);
    h->pages = NULL;
    h->quit = build_button("sf,texture,base_size,release,rect,p_sf,r_sf",
    (sfVector2f){0.08, 0}, global_texture(), (sfVector2f){1, 1}, quit_htp,
    exit_rect, BUTTON_PRESS, BUTTON_RELEASE);
    h->next = build_button("sf,texture,base_size,release,rect,p_sf,r_sf,text,"
    "ff", (sfVector2f){0.2, 0.1}, global_texture(), (sfVector2f){1, 1},
    next_page, button_rect, BUTTON_PRESS, BUTTON_RELEASE, "Next", 0.8);
    h->prev = build_button("sf,texture,base_size,release,rect,p_sf,r_sf,text,"
    "ff", (sfVector2f){0.2, 0.1}, global_texture(), (sfVector2f){1, 1},
    prev_page, button_rect, BUTTON_PRESS, BUTTON_RELEASE, "Previous", 0.6);
    h->from = HOME;
    for (int i = 0; pages[i]; i++)
        append_node(&h->pages,
        init_sprite_from_texture(get_texture_by_name(pages[i])));
    return h;
}
