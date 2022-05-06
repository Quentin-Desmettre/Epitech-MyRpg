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
    int p = c->primary;
    player_info_t *infos = (p >= 0) ? &c->saves[c->primary]->infos : NULL;
    char *file_names[3] = {"saves/save1", "saves/save2", "saves/save3"};
    int fd = (p >= 0 ? open(file_names[p], O_RDWR | O_CREAT, 0666) : -1);

    if (fd < 0)
        return;
    update_inventory();
    update_skills();
    update_xp();
    infos->room_level = ((ray_c *)win->menus[LIGHT])->lvl;
    write(fd, infos, sizeof(player_info_t));
    close(fd);
}
