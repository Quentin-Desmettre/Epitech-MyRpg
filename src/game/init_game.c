/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"
#include "player.h"

void destroy_game(game_t *game)
{
    sfRenderTexture_destroy(game->rtex);
    sfClock_destroy(game->clock);
    sfSprite_destroy(game->level->sprite);
    sfTexture_destroy(game->level->texture);
    sfSprite_destroy(game->player->sprite);
    sfTexture_destroy(game->player->texture);
    for (int i = 0; i < game->level->size.x + 3; i++)
        free(game->level->room[i]);
    for (int i = 0; i < game->player->nb_rects; i++)
        free(game->player->rects[i]);
    free(game->player->nb_frames);
    free(game->player->rects);
    free(game->level->room);
    free(game->player);
    free(game->level);
    free(game);
}

void game_ev(window_t *win, sfEvent ev)
{
    game_t *game = win->menus[GAME];

    if (ev.type == sfEvtKeyReleased) {
        if (ev.key.code == sfKeyZ)
            game->player->dir = UP;
        if (ev.key.code == sfKeyQ)
            game->player->dir = LEFT;
        if (ev.key.code == sfKeyS)
            game->player->dir = DOWN;
        if (ev.key.code == sfKeyD)
            game->player->dir = RIGHT;
        if (ev.key.code == sfKeyR)
            new_room(game->level, win->menus[LIGHT]);
    }
}

void anim_game(game_t *game)
{
    sfTime time = sfClock_getElapsedTime(game->clock);
    float seconds = time.microseconds / 1000000.0;

    if (seconds > 0.5) {
        game->player->frame++;
        if (game->player->frame >= game->player->nb_frames[game->player->dir])
            game->player->frame = 0;
        sfSprite_setTextureRect(game->player->sprite,
        game->player->rects[game->player->dir][game->player->frame]);
        sfClock_restart(game->clock);
    }
}

const sfTexture *draw_game(window_t *win)
{
    game_t *game = win->menus[GAME];

    anim_game(game);
    sfRenderTexture_clear(game->rtex, sfBlack);
    // sfRenderTexture_drawSprite(game->rtex, game->player->sprite, NULL);
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
    game->level = level_create("dnts", 0, LOBBY_NAME, LOBBY_TEXT, BIG);
    game->clock = sfClock_create();
    return game;
}
