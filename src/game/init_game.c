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

    if (ev.type == sfEvtKeyReleased && !game->is_flashing) {
        if (ev.key.code == sfKeyE)
            take_item(win, win->menus[GAME], win->menus[LIGHT]);
        (ev.key.code == sfKeyI) ? (game->quest->draw = 0),
        (game->inventory->draw = !game->inventory->draw) : 0;
        (ev.key.code == sfKeyTab) ? (game->inventory->draw = 0),
        (game->quest->draw = !game->quest->draw) : 0;
        if (ev.key.code == sfKeyJ)
            game->skills->draw = !game->skills->draw;
        if (ev.key.code == sfKeyR)
            new_room(win->menus[GAME], win->menus[LIGHT]);
        if (ev.key.code == sfKeyB)
            remove_xp(game, 1);
        if (ev.key.code == sfKeyN)
            add_xp(game, 1);
        if (ev.key.code == sfKeyAdd)
            next_level(win->menus[LIGHT]);
    }
    if (ev.type == sfEvtMouseButtonReleased &&
    ev.mouseButton.button == sfMouseLeft) {
        game->inventory->draw ? inventory_events(game, ev, win) : 0;
        game->skills->draw ? skills_events(game, ev, win) : 0;
    }
    ev_quest(game, ev, win->win);
}

void check_flash(game_t *game, sfRectangleShape *rect)
{
    if (sfClock_getElapsedTime(game->flash_clock).microseconds > 100000) {
        sfRectangleShape_setFillColor(rect, (sfColor){255, 0, 0, 64});
        sfRectangleShape_setSize(rect,
        (sfVector2f){sfRenderTexture_getSize(game->rtex).x,
        sfRenderTexture_getSize(game->rtex).y});
    }
    if (game->is_flashing &&
    sfClock_getElapsedTime(game->flash_clock).microseconds > 200000) {
        game->nb_flash--;
        sfClock_restart(game->flash_clock);
    }
}

const sfTexture *draw_game(window_t *win)
{
    game_t *game = win->menus[GAME];
    sfRectangleShape *rect = sfRectangleShape_create();

    if (!game->is_flashing)
        anim_npc(game->player);
    else
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
    game->clock = sfClock_create();
    game->flash_clock = sfClock_create();
    return game;
}
