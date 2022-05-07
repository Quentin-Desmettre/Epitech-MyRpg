/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "player.h"

static void quit_ev(void *w)
{
    window_t *win = w;
    end_t *d = win->menus[END];

    if (d->music)
        sfMusic_stop(d->music);
    delete_selected(w);
    set_next_win_state(w, HOME);
}

static void setup_end(end_t *d, int has_died, sfVector2f size, sfVector2f win_s)
{
    d->rects = has_died ? died_rect : pl_rect_dance;
    d->nb_rect = has_died ? 6 : 7;
    d->cur_rect = 0;
    sfSprite_setTextureRect(d->player, d->rects[0]);
    set_sprite_size(d->player, (sfVector2f){size.x * 2.5, size.y * 2.5});
    center_sprite(d->player);
    sfSprite_setPosition(d->player, (sfVector2f){win_s.x * 0.5, win_s.y * 0.5});
    set_next_win_state(window(NULL), END);
    d->music = create_music(has_died ? DIED_MUSIC : WON_MUSIC);
}

void end_game(int has_died)
{
    end_t *d = window(NULL)->menus[END];
    sfVector2f win_s = win_size(window(NULL));
    sfVector2f size = get_sprite_size(GET_GAME(window(NULL))->player->sprite);

    destroy_end(d);
    d = create_died(window(NULL));
    sfText_setString(d->text, has_died ? "You died =)" : "You won =(");
    sfText_setCharacterSize(d->text, win_s.y * 0.1);
    center_text(d->text);
    sfText_setPosition(d->text, (sfVector2f){win_s.x * 0.5, win_s.y * 0.2});
    setup_end(d, has_died, size, win_s);
    window(NULL)->menus[END] = d;
    if (d->music)
        sfMusic_play(d->music);
    d->is_dying = has_died;
}

const sfTexture *draw_end(window_t *win)
{
    end_t *d = win->menus[END];

    sfRenderTexture_clear(d->rtex, sfBlack);
    sfRenderTexture_drawText(d->rtex, d->text, NULL);
    draw_button_to_rtex(d->quit, d->rtex);
    sfRenderTexture_drawSprite(d->rtex, d->player, NULL);
    if (get_elapsed_time(d->clock) > 100000 + d->is_dying * 50000 && d->anim) {
        d->cur_rect = (d->cur_rect + 1) % d->nb_rect;
        if (d->is_dying && !d->cur_rect) {
            d->anim = 0;
            d->cur_rect = d->nb_rect - 1;
        }
        restart_clock(d->clock);
    }
    sfSprite_setTextureRect(d->player, d->rects[d->cur_rect]);
    sfRenderTexture_display(d->rtex);
    return sfRenderTexture_getTexture(d->rtex);
}

end_t *create_died(window_t *win)
{
    sfVector2f win_s = win_size(win);
    end_t *d = malloc(sizeof(end_t));

    memset(d, 0, sizeof(end_t));
    d->rtex = sfRenderTexture_create(win_s.x, win_s.y, 0);
    d->text = init_text("", win_s.y * 0.1);
    d->quit = build_button("sf,pf,release,base_size,ff,text,texture,rect,"
    "p_sf,r_sf", (sfVector2f){0.25, 0.15}, (sfVector2f){0.5, 0.8}, quit_ev,
    win_s, 0.6, "Quit", global_texture(), button_rect, BUTTON_PRESS,
    BUTTON_RELEASE);
    d->player = init_sprite_from_texture(
    get_texture_by_name("assets/player.png"));
    d->clock = create_clock();
    d->anim = 1;
    return d;
}
