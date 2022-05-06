/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** save_player
*/

#include "rpg.h"

void save_player(window_t *win)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    if (c->primary == -1)
        return;
    player_info_t *infos = &c->saves[c->primary]->infos;
    char *str = nbr_to_str(c->primary + 1);
    char *file_name = str_concat(2, "saves/save", str);
    int fd = open(file_name, O_RDWR | O_CREAT, 0666);

    if (fd < 0)
        return free(str);
    write(fd, infos, sizeof(player_info_t));
    free(file_name);
    close(fd);
    free(str);
}
