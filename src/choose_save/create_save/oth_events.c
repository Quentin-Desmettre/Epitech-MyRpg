/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** oth_events.c
*/

#include "rpg.h"

void load_saves(choose_save_t *c)
{
    sfVector2u win = sfRenderTexture_getSize(c->rtex);
    sfVector2f win_size = {win.x, win.y};
    char const *files[3] = {"./saves/save1", "./saves/save2", "./saves/save3"};

    for (int i = 0; i < 3; i++) {
        free_save(c->saves[i]);
        c->saves[i] = create_gui_player(files[i], win_size);
        rescale_gui_player(c->saves[i], win_size);
    }
    update_buttons_colors(c);
}

void copy_data(player_info_t *infos, create_save_t *c)
{
    memset(infos, 0, sizeof(player_info_t));
    infos->health_percent = 100;
    infos->m_health_percent = 100;
    my_strcpy(infos->player_name, get_text(c->name));
    infos->mental_stability = getnbr_sftext(c->stats_val[3]);
    infos->speed = getnbr_sftext(c->stats_val[1]);
    infos->strength = getnbr_sftext(c->stats_val[0]);
    infos->stamina = getnbr_sftext(c->stats_val[2]);
    infos->skin_comb = sfSprite_getColor(c->skin);
}

void create_file(create_save_t *c, window_t *win)
{
    char *f_no = nbr_to_str(c->f_no + 1);
    char *file_name = str_concat(2, "./saves/save", f_no);
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    player_info_t infos;

    free(f_no);
    free(file_name);
    if (fd < 0)
        return;
    copy_data(&infos, c);
    write(fd, &infos, sizeof(player_info_t));
    set_next_win_state(win, SELECT_SAVE);
    load_saves(win->menus[SELECT_SAVE]);
}

void update_player_color(create_save_t *c)
{
    int colors[3];
    sfColor col;
    int err;

    for (int i = 0; i < 3; i++)
        colors[i] = my_getnbr(sfText_getString(c->col_vals[i]), &err);

    col.r = colors[0];
    col.g = colors[1];
    col.b = colors[2];
    col.a = 255;
    sfSprite_setColor(c->skin, col);
}

void change_color(create_save_t *c, int button)
{
    int row = button / 2;
    int offset = button % 2 ? 1 : -1;
    int error;
    int cur_val = my_getnbr(sfText_getString(c->col_vals[row]), &error);
    int new_val = cur_val + offset;
    char *new_str;

    if (new_val < 42 || new_val > 255)
        return;
    new_str = nbr_to_str(new_val);
    sfText_setString(c->col_vals[row], new_str);
    center_text(c->col_vals[row]);
    free(new_str);
    update_player_color(c);
}
