/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** anim
*/

#include "rpg.h"

void anim_run(cinematic_t *cine, window_t *win, float size)
{
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t *infos = &c->saves[c->primary]->infos;

    if (get_elapsed_time(cine->clock) > 0.05 SEC && cine->player_state == 5) {
        cine->npc[0]->dir = 1;
        for (int i = 0; i < 2; i++) {
            cine->npc[i]->frame++;
            cine->npc[i]->frame %= cine->npc[i]->nb_frames[cine->npc[i]->dir];
        }
        restart_clock(cine->clock);
    }
    if (get_elapsed_time(cine->run_clock) > 0.01 SEC
    && cine->player_state == 5) {
        sfSprite_move(cine->npc[0]->sprite, (sfVector2f){10 * size, 0});
        sfSprite_move(cine->npc[1]->sprite, (sfVector2f){8 * size, 0});
        if (sfSprite_getGlobalBounds(cine->npc[0]->sprite).left > 1600 * size)
            set_next_win_state(win, GAME);
        infos->show_intro = 0;
        restart_clock(cine->run_clock);
    }
}

void anim_jumpscare(cinematic_t *cine, window_t *win, float size)
{
    if (get_elapsed_time(cine->clock) > 1 SEC && cine->player_state == 2) {
        cine->npc[0]->dir = 0;
        cine->player_state = 3;
        restart_clock(cine->clock);
    }
    if (get_elapsed_time(cine->clock) > 0.5 SEC && cine->player_state == 3) {
        cine->player_state = 4;
        restart_clock(cine->clock);
    }
    if (cine->player_state == 4) {
        cine_flash(cine);
        if (cine->nb_flash == 0) {
            cine->player_state = 5;
            cine->npc[0]->frame = 0;
        }
    }
    if (cine->player_state == 5)
        anim_run(cine, win, size);
}

void anim_cine(cinematic_t *cine, window_t *win, float size)
{
    if (get_elapsed_time(cine->clock) > 0.03 SEC && cine->player_state == 0) {
        sfSprite_move(cine->npc[0]->sprite, (sfVector2f){0, 10});
        restart_clock(cine->clock);
        if (sfSprite_getGlobalBounds(cine->npc[0]->sprite).top >= 500 * size)
            cine->player_state = 1;
    }
    if (get_elapsed_time(cine->clock) >
    (cine->npc[0]->frame == 5 ? 1 : 0.2) SEC && cine->player_state == 1) {
        cine->npc[0]->frame--;
        restart_clock(cine->clock);
        if (cine->npc[0]->frame == 0)
            cine->player_state = 2;
    }
    anim_jumpscare(cine, win, size);
}
