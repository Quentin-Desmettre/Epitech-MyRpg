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
    sfSprite_destroy(game->inventory->sprite);
    sfTexture_destroy(game->inventory->texture);
    free(game->inventory->data);
    free(game->inventory);
    free(game);
}

void game_ev(window_t *win, sfEvent ev)
{
    game_t *game = win->menus[GAME];

    if (ev.type == sfEvtKeyReleased) {
        if (ev.key.code == sfKeyE)
            take_item(win, win->menus[GAME], win->menus[LIGHT]);
        if (ev.key.code == sfKeyU)
            game->inventory->item_selected = WATER;
        if (ev.key.code == sfKeyJ)
            game->inventory->item_selected = PILLS;
        if (ev.key.code == sfKeyN)
            game->inventory->item_selected = -1;
        if (ev.key.code == sfKeyI)
            game->inventory->draw = !game->inventory->draw;
        if (ev.key.code == sfKeyR)
            new_room(win->menus[GAME], win->menus[LIGHT]);
    }
}

const sfTexture *draw_game(window_t *win)
{
    game_t *game = win->menus[GAME];

    anim_npc(game->player);
    sfRenderTexture_clear(game->rtex, sfBlack);
    draw_room(win->menus[LIGHT], win->menus[GAME], win->win);
    draw_enemies(game, win->menus[LIGHT]);
    draw_map(win->menus[LIGHT], win->menus[GAME], win->win);
    draw_inventory(win->menus[GAME], win);
    sfRenderTexture_display(game->rtex);
    return sfRenderTexture_getTexture(game->rtex);
}

game_t *game_create(void)
{
    game_t *game = malloc(sizeof(game_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    static const sfIntRect *pl_rects[5] = {
        pl_rect_top,
        pl_rect_down,
        pl_rect_left,
        pl_rect_right,
        pl_rect_idle
    };

    memset(game, 0, sizeof(game_t));
    game->rtex = sfRenderTexture_create(1920, 1080, 0);
    game->player = npc_create("tnicp", "./assets/player.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, (sfVector2f){128, 128});
    sfSprite_setOrigin(game->player->sprite, (sfVector2f){32, 32});
    game->level = level_create("dnts", 0, LOBBY_NAME, LOBBY_TEXT, BIG);
    game->inventory = inventory_create();
    game->clock = sfClock_create();
    game->enemies = NULL;
    return game;
}
