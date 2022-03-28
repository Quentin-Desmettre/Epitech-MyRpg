/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"
#include "game.h"

void game_ev(window_t *win, sfEvent ev)
{
    game_t *game = win->menus[GAME];
    npc_t *player = game->player;

    if (sfKeyboard_isKeyPressed(sfKeyD)){
        player->dir = RIGHT;
        player->frame++;
        if (player->frame >= player->nb_frames[RIGHT])
            player->frame = 0;
        sfSprite_setTextureRect(player->sprite,
        player->rects[player->dir][player->frame]);
    }

}

const sfTexture *draw_game(window_t *win)
{
    game_t *game = win->menus[GAME];
    settings_t *se = win->menus[SETTINGS];

    sfRenderTexture_clear(game->rtex, sfBlack);
    sfRenderTexture_drawSprite(game->rtex, game->player->sprite, NULL);
    draw_set_button(game->rtex, se->framerate_button);
    sfRenderTexture_display(game->rtex);
    return sfRenderTexture_getTexture(game->rtex);
}

game_t *game_create(window_t *win)
{
    game_t *game = malloc(sizeof(game_t));

    memset(game, 0, sizeof(game_t));
    game->rtex = sfRenderTexture_create(win->mode.width, win->mode.height, 0);
    game->player = npc_create("tnihafv", P_TEXT, p_frames, p_rects,
    P_HEALTH, P_ATK, P_DEF, P_SPD);
    return game;
}
