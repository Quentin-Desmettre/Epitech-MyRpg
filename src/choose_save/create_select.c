/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include <fcntl.h>
#include "file_select.h"

void go_back_to_main(void *win)
{
    set_next_win_state(win, HOME);
}

void delete_selected(void *win)
{
    window_t *w = win;
    choose_save_t *s = w->menus[SELECT_SAVE];
    char const *files[3] = {"./saves/save1", "./saves/save2", "./saves/save3"};
    int fd = open(files[s->primary], O_WRONLY | O_TRUNC);

    close(fd);
    load_saves(s);
}

void launch_create_file(void *win)
{
    window_t *w = win;
    choose_save_t *c = w->menus[SELECT_SAVE];

    set_next_win_state(win, CREATE_SAVE);
    if (w->menus[CREATE_SAVE])
        destroy_create_save(&w->menus[CREATE_SAVE]);
    w->menus[CREATE_SAVE] = create_create_save(win_size(w), c->primary);
}

void launch_file(void *win)
{
    window_t *w = win;
    choose_save_t *c = w->menus[SELECT_SAVE];
    game_t *g = w->menus[GAME];
    player_info_t infos = c->saves[c->primary]->infos;

    sfSprite_setColor(g->player->sprite, infos.skin_comb);
    sfMusic_stop(w->music);
    g->player->speed = infos.speed;
    g->player->attack = infos.strength;
    g->player->defense = infos.stamina;
    g->player->health = infos.health_percent;
    set_next_win_state(win, GAME);
    lazy_room(win);
}

choose_save_t *create_choose_save(sfVector2f win_size)
{
    choose_save_t *c = malloc(sizeof(choose_save_t));

    c->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    for (int i = 0; i < 4; i++)
        c->buttons[i] = build_button("sf,pf,base_size,"
        "text,texture,rect,release,ff,p_sf,r_sf", (sfVector2f){0.2, 0.1},
        (sfVector2f){0.14 + 0.24 * i, 0.9}, win_size, texts[i], global_texture()
        , button_rect, functions[i], 0.65, BUTTON_PRESS, BUTTON_RELEASE);
    c->hider = sfSprite_create();
    sfSprite_setTexture(c->hider,
    sfTexture_createFromFile(GLOBAL_TEXTURE, &hider_rect), 0);
    sfTexture_setRepeated((sfTexture *)sfSprite_getTexture(c->hider), 1);
    for (int i = 0; i < 3; i++)
        c->saves[i] = create_gui_player(files[i], win_size);
    c->primary = -1;
    c->secondary = -1;
    update_buttons_colors(c);
    c->create_save = NULL;
    return c;
}
