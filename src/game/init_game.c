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
    destroy_npc(game->player);
    destroy_level(game->level);
    destroy_inventory(game->inventory);
    while (game->enemies)
        remove_node(&game->enemies, 0, destroy_enemy);
    destroy_clock(game->flash_clock);
    while (game->items)
        remove_node(&game->items, 0, free);
    destroy_pause(game->pause);
    destroy_skills(game->skills);
    quest_destroy(game->quest);
    destroy_path(game->path);
    destroy_interactive_npc(game->npc);
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

void draw_menus(game_t *game, window_t *win)
{
    ray_c *r = win->menus[LIGHT];
    choose_save_t *c = win->menus[SELECT_SAVE];
    int pr = c->primary;

    draw_room(r, win->menus[GAME], win);
    draw_enemies(game, r, win);
    if (game->splash && !draw_circular_splash(&game->splash, r->tex_light))
        set_next_win_state(win, FIGHT);
    draw_map(r, win->menus[GAME], win);
    draw_xp(win->menus[GAME], win);
    draw_inventory(win->menus[GAME], win);
    draw_quest(win->menus[GAME], win);
    draw_skills(win->menus[GAME], win);
    draw_npc(game, r);
    if (pr >= 0 && c->saves[c->primary]->infos.health_percent <= 0)
        end_game(1);
}

const sfTexture *draw_game(window_t *win)
{
    game_t *game = win->menus[GAME];
    sfRectangleShape *rect = sfRectangleShape_create();

    if ((rand() % 3000) == 3 && game->sounds[0] && !game->is_paused &&
    sfSound_getStatus(game->sounds[0]) != sfPlaying)
        sfSound_play(game->sounds[0]);
    if (!game->is_flashing && !game->is_paused)
        anim_npc(game->player);
    else if (!game->is_paused)
        check_flash(game, rect);
    sfRenderTexture_clear(game->rtex, sfBlack);
    draw_menus(game, win);
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
    game->player = npc_create("tnicp", "assets/player.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, (sfVector2f){128, 128});
    sfSprite_setOrigin(game->player->sprite, (sfVector2f){32, 32});
    game->level = level_create("dnts", 0, LOBBY_NAME, LOBBY_TEXT, BIG);
    game->inventory = inventory_create();
    game->skills = skills_create();
    game->clock = create_clock();
    game->flash_clock = create_clock();
    game->thirst_clock = create_clock();
    init_musics(game);
    return game;
}
