/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include <fcntl.h>

void go_back_to_main(void *win)
{
    (void)win;
}

void delete_selected(void *win)
{
    (void)win;
}

void launch_create_file(void *win)
{
    (void)win;
}

void launch_file(void *win)
{
    (void)win;
}

choose_save_t *create_choose_save(sfVector2f win_size)
{
    choose_save_t *c = malloc(sizeof(choose_save_t));
    char const *texts[] = {"Cancel", "Delete", "Create", "Launch"};
    void (*functions[4])(void *) = {go_back_to_main,
    delete_selected, launch_create_file, launch_file};
    char *files[3] = {"./saves/save1", "./saves/save2", "./saves/save3"};

    c->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    for (int i = 0; i < 4; i++)
        c->buttons[i] = build_button("sf,pf,base_size,"
        "text,texture,rect,release,ff", (sfVector2f){0.2, 0.1},
        (sfVector2f){0.14 + 0.24 * i, 0.9},
        win_size, texts[i], global_texture(), (sfIntRect){0, 81, 315, 80},
        functions[i], 0.65);
    c->hider = sfSprite_create();
    sfSprite_setTexture(c->hider,
    sfTexture_createFromFile(GLOBAL_TEXTURE, &hider_rect), 0);
    sfTexture_setRepeated((sfTexture *)sfSprite_getTexture(c->hider), 1);
    for (int i = 0; i < 3; i++)
        c->saves[i] = create_gui_player(files[i], win_size);
    return c;
}
