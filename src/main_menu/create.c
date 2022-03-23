/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"

main_menu_t *create_main_menu(sfVector2f win_size)
{
    main_menu_t *m = malloc(sizeof(main_menu_t));
    char *texts[] = {
        "Load save", "Create map", "Play online", "Settings", "Exit"
    };
    sfVector2f pf[5] = {
        {}, {}, {}, {}, {}
    };
    sfVector2f sf[5] = {
        {}, {}, {}, {}, {}
    };

    m->background = init_sprite(global_texture(), back_rect, win_size);
    for (int i = 0; i < 5; i++) {
    }
    return m;
}
