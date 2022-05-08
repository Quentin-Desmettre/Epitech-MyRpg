/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** save_player
*/

#include "rpg.h"

void update_quests(player_info_t *infos)
{
    game_t *g = GET_GAME(window(NULL));

    for (int i = 0; i < 4; i++) {
        infos->name_qst[i] =
        index_str_in_array(name_qst, g->quest->name_qst[i]);
        infos->desc_qst[i] =
        index_str_in_array(desc_qst, g->quest->desc_qst[i]);
    }
    my_memcpy(infos->progress, g->quest->progress, sizeof(int [4][2]));
}

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
    update_quests(infos);
    infos->room_level = ((ray_c *)win->menus[LIGHT])->lvl;
    write(fd, infos, sizeof(player_info_t));
    close(fd);
}
