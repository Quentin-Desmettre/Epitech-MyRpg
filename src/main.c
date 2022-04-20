/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"
#include "player.h"

void move_pl(window_t *win);

static void win_destroy(window_t *win)
{
    sfRenderWindow_destroy(win->win);
    save_settings(win->menus[SETTINGS]);
    destroy_settings(win->menus[SETTINGS]);
    destroy_main_menu(win->menus[HOME]);
    dest_light(win->menus[LIGHT]);
    destroy_game(win->menus[GAME]);
    sfClock_destroy(win->lum_clock);
    free_choose_save(win->menus[SELECT_SAVE]);
    free(win);
}

static void draw(window_t *win)
{
    const sfTexture* tex = win->draw[win->state] ?
    win->draw[win->state](win) : NULL;
    sfTexture *cpy = tex ? sfTexture_copy(tex) : NULL;
    sfSprite *s = init_sprite_from_texture(cpy);

    if (win->is_transition)
        update_transition(win, s);
    sfRenderWindow_drawSprite(win->win, s, NULL);
    if (win->state == GAME) {
        draw_room(win->menus[LIGHT], win->menus[GAME], win->win);
        draw_map(win->menus[LIGHT], win->menus[GAME], win->win);
        //draw_inventory(win->menus[GAME], win->win);
    }
    move_pl(win);
    sfRenderWindow_display(win->win);
    sfTexture_destroy(cpy);
    sfSprite_destroy(s);
    sfRenderWindow_clear(win->win, sfBlack);
}

void set_next_win_state(window_t *win, int next)
{
    win->next_state = next;
    win->is_transition = 1;
}

sfFloatRect get_npc_hitbox(npc_t *player)
{
    sfFloatRect whole = sfSprite_getGlobalBounds(player->sprite);
    float width_fac = 0.45;

    whole.left += whole.width * ((1 - width_fac) / 2.0);
    whole.width *= width_fac;
    whole.top += whole.height * 0.37;
    whole.height *= 0.8;
    return whole;
}

void draw_float_rect(sfRenderWindow *win, sfFloatRect rect, sfColor col)
{
    sfRectangleShape *r = create_rectangle((sfVector2f){rect.width, rect.height}, col, 0, sfWhite);

    sfRectangleShape_setPosition(r, (sfVector2f){rect.left, rect.top});
    sfRenderWindow_drawRectangleShape(win, r, NULL);
    sfRectangleShape_destroy(r);
}

int is_pnj_colliding(ray_c *data, npc_t *player, level_t *level)
{
    coo_t size = level->size;
    sfFloatRect hitbox = get_npc_hitbox(player);
    sfFloatRect wall_hitbox;
    sfSprite *wall = init_sprite(data->wall_tex,
    (sfIntRect){64, 0, 64, 64}, get_sprite_size(data->wall));

    for (int i = 0; i < size.y + 2; i++) {
        for (int j = 0; j < size.x + 2; j++) {
            if (data->map[i][j] == '1') {
                sfSprite_setPosition(wall,
                (sfVector2f){i * data->cell, j * data->cell + data->cell / 2});
                wall_hitbox = sfSprite_getGlobalBounds(wall);
                if (sfFloatRect_intersects(&hitbox, &wall_hitbox, NULL)) {
                    sfSprite_destroy(wall);
                    return 1;
                }
            }
        }
    }
    sfSprite_destroy(wall);
    return 0;
}

int dir_from_v2f(sfVector2f vf)
{
    int dir = IDLE;

    if (vf.y < 0)
        dir = UP;
    else if (vf.y > 0)
        dir = DOWN;
    if (vf.x < 0)
        dir = LEFT;
    else if (vf.x > 0)
        dir = RIGHT;
    return dir;
}

sfVector2f get_player_movement(void)
{
    sfVector2f movement = {0, 0};

    if (sfKeyboard_isKeyPressed(sfKeyZ))
        movement.y = -2;
    if (sfKeyboard_isKeyPressed(sfKeyS) && !sfKeyboard_isKeyPressed(sfKeyZ))
        movement.y = 2;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        movement.x = -2;
    if (sfKeyboard_isKeyPressed(sfKeyD) && !sfKeyboard_isKeyPressed(sfKeyQ))
        movement.x = 2;
    return movement;
}

void move_along_vector(game_t *game, sfVector2f movement, window_t *win)
{
    sfSprite_move(game->player->sprite, (sfVector2f){movement.x, 0});
    if (is_pnj_colliding(win->menus[LIGHT],
    game->player, game->level))
        sfSprite_move(game->player->sprite,
        (sfVector2f){-movement.x, 0});
    sfSprite_move(game->player->sprite, (sfVector2f){0, movement.y});
    if (is_pnj_colliding(win->menus[LIGHT],
    game->player, game->level))
        sfSprite_move(game->player->sprite,
        (sfVector2f){0, -movement.y});
}

void move_pl(window_t *win)
{
    game_t *game = win->menus[GAME];
    sfVector2f movement = get_player_movement();

    move_along_vector(game, movement, win);

    game->player->dir = dir_from_v2f(movement);
}

static void poll_events(window_t *win)
{
    sfEvent ev;

    while (sfRenderWindow_pollEvent(win->win, &ev)) {
        if (ev.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
            set_next_win_state(win, EXIT);
        if (win->event[win->state])
            win->event[win->state](win, ev);
    }
    if (win->state == SETTINGS)
        check_sound_repeat(win, &ev);
}

int main(void)
{
    window_t *win;

    if (!global_texture() || !global_font())
        return 84;
    win = window_create();
    while (sfRenderWindow_isOpen(win->win)) {
        poll_events(win);
        move_pl(win);
        draw(win);
    }
    win_destroy(win);
    sfFont_destroy(global_font());
    sfTexture_destroy(global_texture());
    sfTexture_destroy(player_texture());
    sfTexture_destroy(bars_texture());
    return 0;
}
