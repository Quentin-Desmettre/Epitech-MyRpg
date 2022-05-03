/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create
*/

#include "rpg.h"
#include "player.h"
#include "player_cine.h"
#include "cinematic.h"

void destroy_cinematic(cinematic_t *cin)
{
    sfRenderTexture_destroy(cin->rtex);
    destroy_npc(cin->npc[0]);
    destroy_npc(cin->npc[1]);
    destroy_clock(cin->clock);
    destroy_clock(cin->run_clock);
    sfRectangleShape_destroy(cin->rect);
    destroy_level(cin->level);
    sfSprite_destroy(cin->wall);
    sfSprite_destroy(cin->floor);
    free(cin);
}

void create_cine_level(cinematic_t *cinematic)
{
    cinematic->level = level_create("dnts", 0, LOBBY_NAME, LOBBY_TEXT, BIG);
    cinematic->wall = sfSprite_create();
    cinematic->floor = sfSprite_create();
    sfSprite_setTexture(cinematic->wall,
    get_texture_by_name("assets/floor_wall/wall_lvl.png"), sfTrue);
    sfSprite_setTexture(cinematic->floor,
    get_texture_by_name("assets/floor_wall/floor_lvl1.png"), sfTrue);
    sfSprite_setTextureRect(cinematic->wall, (sfIntRect){64, 0, 64, 64});
    for (int i = 0; i < cinematic->level->size.x + 1; i++) {
        for (int j = 0; j < cinematic->level->size.y + 1; j++)
            cinematic->level->room[i][j] = 'X';
    }
    for (int i = 0; i < cinematic->level->size.y + 1; i++) {
        cinematic->level->room[7][i] = '*';
        cinematic->level->room[8][i] = '*';
    }
}

cinematic_t *create_cinematic(sfColor pl_color)
{
    cinematic_t *cinematic = malloc(sizeof(cinematic_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    static const sfIntRect *pl_rects[5] = {
        pl_rect_top, pl_rect_down, pl_rect_left, pl_rect_right, pl_rect_idle
    };

    memset(cinematic, 0, sizeof(cinematic_t));
    cinematic->rtex = sfRenderTexture_create(1920, 1080, 0);
    cinematic->npc[0] = npc_create("tnids", "assets/player.png", cine_frames
    , cine_rects, 2, 5);
    create_cine_level(cinematic);
    cinematic->npc[1] = npc_create("tni", "assets/party.png", test, pl_rects);
    cinematic->clock = p_clock_create();
    cinematic->run_clock = p_clock_create();
    cinematic->rect = sfRectangleShape_create();
    cinematic->nb_flash = 3;
    sfSprite_setColor(cinematic->npc[0]->sprite, pl_color);
    return cinematic;
}
