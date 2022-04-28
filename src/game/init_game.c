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
    destroy_clock(game->clock);
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

void check_flash(game_t *game, sfRectangleShape *rect)
{
    if (get_elapsed_time(game->flash_clock) > 100000) {
        sfRectangleShape_setFillColor(rect, (sfColor){255, 0, 0, 64});
        sfRectangleShape_setSize(rect,
        (sfVector2f){sfRenderTexture_getSize(game->rtex).x,
        sfRenderTexture_getSize(game->rtex).y});
    }
    if (game->is_flashing && get_elapsed_time(game->flash_clock) > 200000) {
        game->nb_flash--;
        restart_clock(game->flash_clock);
    }
}

const sfTexture *draw_game(window_t *win)
{
    game_t *game = win->menus[GAME];
    sfRectangleShape *rect = sfRectangleShape_create();

    if (!game->is_flashing && !game->is_paused)
        anim_npc(game->player);
    else if (!game->is_paused)
        check_flash(game, rect);
    sfRenderTexture_clear(game->rtex, sfBlack);
    draw_room(win->menus[LIGHT], win->menus[GAME], win);
    draw_enemies(game, win->menus[LIGHT], win);
    draw_map(win->menus[LIGHT], win->menus[GAME], win);
    draw_xp(win->menus[GAME], win);
    draw_inventory(win->menus[GAME], win);
    draw_quest(win->menus[GAME], win->win);
    draw_skills(win->menus[GAME], win);
    sfRenderTexture_drawRectangleShape(game->rtex, rect, NULL);
    sfRectangleShape_destroy(rect);
    if (game->is_paused)
        draw_pause(game->pause, game->rtex);
    sfRenderTexture_display(game->rtex);
    if (game->nb_flash == 0 && game->is_flashing)
        game->is_flashing = 0;
    return sfRenderTexture_getTexture(game->rtex);
}

game_t *game_create(void)
{
    game_t *game = malloc(sizeof(game_t));
    int test[6] = {9, 9, 9, 9, 2, 0};
    static const sfIntRect *pl_rects[5] = {
        pl_rect_top, pl_rect_down, pl_rect_left, pl_rect_right, pl_rect_idle
    };

    memset(game, 0, sizeof(game_t));
    quest_init(game);
    game->rtex = sfRenderTexture_create(1920, 1080, 0);
    game->player = npc_create("tnicp", "./assets/player.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, (sfVector2f){128, 128});
    sfSprite_setOrigin(game->player->sprite, (sfVector2f){32, 32});
    game->level = level_create("dnts", 0, LOBBY_NAME, LOBBY_TEXT, BIG);
    game->inventory = inventory_create();
    game->skills = skills_create();
    game->clock = create_clock();
    game->flash_clock = create_clock();
    game->is_paused = 0;
    return game;
}
