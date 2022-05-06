/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc
*/

#include "rpg.h"

void destroy_npc(npc_t *n)
{
    sfSprite_destroy(n->sprite);
    destroy_clock(n->move_clock);
    destroy_clock(n->anim_clock);
    free(n->nb_frames);
    for (int i = 0; i < n->nb_rects; i++)
        free(n->rects[i]);
    free(n->rects);
    free(n);
}

static npc_t *init_npc(void)
{
    npc_t *npc = malloc(sizeof(npc_t));

    memset(npc, 0, sizeof(npc_t));
    npc->sprite = sfSprite_create();
    sfSprite_setPosition(npc->sprite, (sfVector2f){0, 0});
    npc->dir = RIGHT;
    npc->thirst = 100;
    npc->attack = 10;
    npc->defense = 10;
    npc->speed = 10;
    npc->level = 1;
    npc->xp_limit = 5;
    npc->pos = (sfVector2f){0, 0};
    npc->move_clock = create_clock();
    npc->anim_clock = create_clock();
    return npc;
}

void anim_npc(npc_t *npc)
{
    sfInt64 time = get_elapsed_time(npc->anim_clock);
    float seconds = time / 1000000.0;

    if (seconds > 0.1) {
        npc->frame++;
        if (npc->frame >= npc->nb_frames[npc->dir])
            npc->frame = 0;
        sfSprite_setTextureRect(npc->sprite,
        npc->rects[npc->dir][npc->frame]);
        restart_clock(npc->anim_clock);
    }
}

npc_t *npc_create(char *params, ...)
{
    va_list va;
    npc_t *npc = init_npc();
    static void (*npc_setters[])(npc_t *, va_list) = {
        set_npc_txt, set_npc_frames, set_npc_rects, set_npc_dir, set_npc_grp,
        set_npc_initframe, set_npc_health, set_npc_atk, set_npc_def,
        set_npc_spd, set_npc_pos, set_npc_scale, set_npc_level, set_npc_xp
    };

    va_start(va, params);
    for (int i = 0, index = 0; params[i]; i++) {
        index = index_of(params[i], NPC_PARAMS);
        if (index > -1)
            npc_setters[index](npc, va);
    }
    sfSprite_setTextureRect(npc->sprite, npc->rects[npc->dir][npc->frame]);
    va_end(va);
    return npc;
}
