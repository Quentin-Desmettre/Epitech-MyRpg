/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "rpg.h"
#include "player.h"

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
    if (win->music)
        destroy_music(win->music);
    if (win->close_sfx)
        destroy_sound(win->close_sfx);
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
    if (win->state == GAME && !((game_t *)win->menus[GAME])->is_flashing)
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
    if (next == EXIT && win->close_sfx)
        sfSound_play(win->close_sfx);
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

sfVector2f max = (sfVector2f){4, 4};
sfInt64 dur = 500000;

int main(void)
{
    window_t *win;
    list_t *particle_l = NULL;
    particle_t *tmp;

    append_node(&particle_l, build_particle(dur, rectangle, max, -60));
    tmp = particle_l->prev->data;
    sfRectangleShape_setPosition(tmp->sprite, (sfVector2f){400, 300});
    append_node(&particle_l, build_particle(dur, rectangle, max, -120));
    tmp = particle_l->prev->data;
    sfRectangleShape_setPosition(tmp->sprite, (sfVector2f){400, 300});

    // for each particle:
        // if it has been alive for more than n seconds and it doenst have a child,
        //     make it have 2 childs with half velocity; one to the left and one to the right
        // if it has been alive for more than it's life span, destroy it
        // else, divide it's X-velocity by some constant end reduce it's Y-velocity by another constant
        // anyway, move it, update it's size, draw it

    int nb_particles = 48;
    particle_t *particles[nb_particles];
    float angles[48];
    sfEvent ev;

    for (int i = 0; i < 48; i++)
        angles[i] = 360.0 / nb_particles * i;
    win = window_create();
    for (int i = 0; i < nb_particles; i++) {
        particles[i] = 0;
    }
    sfClock *anim_dur = sfClock_create();
    int nb_node = 2;
    while (sfRenderWindow_isOpen(win->win)) {
        while (sfRenderWindow_pollEvent(win->win, &ev)) {
            if (ev.type == sfEvtClosed)
                exit(0);
            // if (ev.type == sfEvtMouseButtonPressed && ev.mouseButton.button == sfMouseLeft)
            //     if (!particles[0] || get_elapsed_time(particles[0]->duration) > dur)
            //         for (int i = 0; i < nb_particles; i++) {
            //             particles[i] = build_particle(dur, rectangle, max, angles[i]);
            //             sfRectangleShape_setPosition(particles[i]->sprite, (sfVector2f){ev.mouseButton.x, ev.mouseButton.y});
            //         }
        }
        // for (int i = 0; i < nb_particles && particles[0]; i++) {
        //     update_particle(particles[i]);
        //     if (get_elapsed_time(particles[0]->duration) < dur)
        //         draw_particle(particles[i], win->win);
        // }
        list_t *begin = particle_l;
        particle_t *tmp2;
        int i = 0;

        // check_for_childs(&particles);
        // check_for_dead(&particles);
        // draw_rects(particles);
        do {
            if (!begin)
                break;
            tmp2 = begin->data;
            if (get_elapsed_time(tmp2->duration) > 200000 && !tmp2->has_child
            && get_elapsed_time(tmp2->duration) < tmp2->max_dur &&
            tmp2->has_parent < 1) {
                nb_node += 2;
                sfVector2f pos = sfRectangleShape_getPosition(tmp2->sprite);

                particle_t *new = build_particle(dur, rectangle, max, -60);
                sfRectangleShape_setPosition(new->sprite, pos);
                new->vector.x /= 1.5;
                new->vector.y /= 1.7;
                new->has_parent = tmp2->has_parent + 1;
                append_node(&particle_l, new);

                new = build_particle(dur, rectangle, max, -120);
                sfRectangleShape_setPosition(new->sprite, pos);
                new->vector.x /= 1.5;
                new->vector.y /= 1.7;
                new->has_parent = tmp2->has_parent + 1;
                append_node(&particle_l, new);

                tmp2->has_child = 1;
                begin = begin->next;
                sfRenderWindow_drawRectangleShape(win->win, tmp2->sprite, NULL);
                continue;
            }

            if (sfClock_getElapsedTime(tmp2->delta_t).microseconds > 33333) {
                sfRectangleShape_move(tmp2->sprite, (sfVector2f){tmp2->vector.x, tmp2->vector.y * 0.1});
                sfClock_restart(tmp2->delta_t);
                tmp2->vector.x /= 1.1;
                tmp2->vector.y += 2;
                sfRectangleShape_scale(tmp2->sprite, (sfVector2f){0.95, 0.95});
            }
            if (get_elapsed_time(tmp2->duration) < tmp2->max_dur)
                sfRenderWindow_drawRectangleShape(win->win, tmp2->sprite, NULL);
            i++;
            begin = begin ? begin->next : NULL;
        } while (begin != particle_l && begin);
        if (sfClock_getElapsedTime(anim_dur).microseconds > 100000) {
            nb_node += 2;
            sfClock_restart(anim_dur);

            particle_t *new = build_particle(dur, rectangle, max, -60);
            sfRectangleShape_setPosition(new->sprite, (sfVector2f){400, 300});
            new->vector.x /= 1.5;
            new->vector.y /= 1.2;
            append_node(&particle_l, new);

            new = build_particle(dur, rectangle, max, -120);
            sfRectangleShape_setPosition(new->sprite, (sfVector2f){400, 300});
            new->vector.x /= 1.5;
            new->vector.y /= 1.2;
            append_node(&particle_l, new);
        }
        sfRenderWindow_display(win->win);
        sfRenderWindow_clear(win->win, sfBlack);
        // poll_events(win);
        // draw(win);
    }
    win_destroy(win);
    sfFont_destroy(global_font());
    sfTexture_destroy(global_texture());
    sfTexture_destroy(player_texture());
    sfTexture_destroy(bars_texture());
    return 0;
}
