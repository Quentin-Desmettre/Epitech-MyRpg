/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include <fcntl.h>

save_file_t load_save(unsigned index)
{
    char *str_index = nbr_to_str(index);
    char *file = str_concat(3, "saves/", str_index, ".data");
    int fd = open(file, O_RDONLY);
    save_file_t n = {"", 0, 0, {0, 0, 0}, {0, 0, 0}};
    save_file_t save;

    free(file);
    free(str_index);
    if (fd < 0)
        return n;
    if (read(fd, &save, sizeof(save_file_t)) != sizeof(save_file_t))
        return n;
    return save;
}

gui_save_file_t *load_gui_save(unsigned index, sfVector2f size)
{
    gui_save_file_t *save = malloc(sizeof(gui_save_file_t));

    save->rtex = sfRenderTexture_create(size.x, size.y, 0);
    save->save = load_save(index);
    if (!save->save.player_name[0])
        save->is_new = 1;
    save->player_name = init_text(save->is_new ?
    "New file" : save->save.player_name, size.y * 0.1);
    save->player = init_sprite(global_texture(), (sfIntRect){0, 0, 1, 1},
    (sfVector2f){size.x * 0.2, size.x * 0.2});
    save->stage = init_sprite(global_texture(), (sfIntRect){1, 0, 1, 1},
    (sfVector2f){size.x * 0.8, size.x * 0.8});
    save->bar_icon = sfSprite_create();
    save->bar_fill = sfRectangleShape_create();
    save->bar_empty = sfRectangleShape_create();
    save->stat_icon = sfSprite_create();
    save->stat_txt = sfText_create();
    return save;
}

choose_save_t *create_choose_save(sfVector2f win_size)
{
    choose_save_t *c = malloc(sizeof(choose_save_t));
    sfVector2f entry_size = {win_size.x * 0.25, win_size.y * 0.7};

    for (int i = 0; i < 3; i++) {
        c->saves[i] = load_gui_save(i, entry_size);
        c->buttons[i] = build_button("");
    }
}