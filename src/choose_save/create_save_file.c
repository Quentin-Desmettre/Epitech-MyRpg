/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create_save_file.c
*/

#include "rpg.h"
#include <fcntl.h>
#include "player.h"

static void set_texts(gui_player_t *g, sfVector2f size)
{
    if (!my_strcmp(sfText_getString(g->stats), "Empty file")) {
        sfText_setCharacterSize(g->stats, size.x * 0.13);
        center_text(g->stats);
        sfText_setPosition(g->stats, (sfVector2f){size.x * 0.5, size.y * 0.5});
    } else {
        sfText_setCharacterSize(g->stats, (size.y * ((0.9 - 0.7)) / 3));
        sfText_setPosition(g->stats,
        (sfVector2f){size.x * 0.1 + size.y * 0.1, size.y * 0.67});
    }
}

void rescale_gui_player(gui_player_t *g, sfVector2f win_size)
{
    sfVector2f size = {win_size.x * ((1 - SPACING * 4) / 3), win_size.y * 0.7};
    sfVector2f sk_size = {win_size.y * 0.3, win_size.y * 0.3};

    sfRenderTexture_destroy(g->rtex);
    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    sfSprite_setTextureRect(g->border,
    (sfIntRect){0, 0, size.x, size.y});
    set_sprite_size(g->skin, sk_size);
    center_sprite(g->skin);
    sfSprite_setPosition(g->skin, (sfVector2f){size.x * 0.5, size.y * 0.24});
    set_sprite_size(g->stats_img, (sfVector2f){size.y * 0.066, size.y * 0.066});
    sfText_setCharacterSize(g->name, size.x * 0.13);
    center_text(g->name);
    sfText_setPosition(g->name, (sfVector2f){size.x * 0.5, size.y * 0.06});
    set_texts(g, size);
}

static char *tooltip_str(player_info_t *infos)
{
    char *values[4] = {
        nbr_to_str(infos->strength),
        nbr_to_str(infos->speed),
        nbr_to_str(infos->defense),
        nbr_to_str(infos->thirst_res)
    };
    char *final = str_concat(7,
    values[0], "\n", values[1], "\n", values[2], "\n", values[3]);

    for (int i = 0; i < 4; i++)
        free(values[i]);
    return final;
}

void init_from_file(gui_player_t *g,
char const *file, sfVector2f size)
{
    int fd = file ? open(file, O_RDONLY) : -1;
    char tmp;
    char *str;
    if (fd < 0 || read(fd, &g->infos, sizeof(player_info_t)) !=
    sizeof(player_info_t) || read(fd, &tmp, 1) > 0) {
        sfText_setString(g->stats, "Empty file");
        sfText_setCharacterSize(g->stats, size.x * 0.13);
        center_text(g->stats);
        sfText_setPosition(g->stats, (sfVector2f){size.x * 0.4, size.y * 0.6});
        return;
    }
    str = tooltip_str(&g->infos);
    sfText_setString(g->stats, str);
    free(str);
    sfText_setPosition(g->stats,
    (sfVector2f){size.x * 0.6, size.y * 0.5});
    sfText_setCharacterSize(g->stats, size.y * 0.1);
    sfText_setString(g->name, g->infos.player_name);
    sfText_setCharacterSize(g->name, size.y * 0.1);
    sfSprite_setColor(g->skin, g->infos.skin_comb);
}

gui_player_t *create_gui_player(char const *file, sfVector2f win_size)
{
    gui_player_t *g = malloc(sizeof(gui_player_t));
    sfVector2f size = {win_size.x * ((1 - SPACING * 4) / 3), win_size.y * 0.65};
    sfTexture *tex = get_texture_by_name(FLOOR_OFFICE);

    sfTexture_setRepeated(tex, 1);
    g->border = init_sprite(tex, (sfIntRect){0, 0, size.x, size.y}, size);
    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    g->skin = init_sprite(get_texture_by_name("assets/player.png"),
    pl_rect_idle[0], (sfVector2f){1, 1});
    g->stats_img = sfSprite_create();
    sfSprite_setTexture(g->stats_img, global_texture(), 0);
    g->name = sfText_create();
    sfText_setFont(g->name, global_font());
    memset(&g->infos, 0, sizeof(player_info_t));
    g->stats = sfText_create();
    sfText_setFont(g->stats, global_font());
    init_from_file(g, file, size);
    return g;
}
