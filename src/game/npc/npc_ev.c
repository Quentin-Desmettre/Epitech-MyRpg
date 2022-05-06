/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc.c
*/

#include "rpg.h"
#include "npc_texts.h"

static void move_arrow(interactive_npc_t *n, int dir)
{
    sfVector2f win_s = win_size(window(NULL));
    int index;

    n->is_querying += dir;
    if (n->is_querying > 2)
        n->is_querying = 1;
    else if (n->is_querying < 1)
        n->is_querying = 2;
    index = n->is_querying - 1;
    sfSprite_setPosition(n->dialog_arrow,
    (sfVector2f){win_s.x * 0.77, win_s.y * 0.685 + index * win_s.x * 0.055});
}

static void check_query(interactive_npc_t *n, game_t *g)
{
    set_string(n, n->second_dialogs[n->is_querying - 1]);
    if (n->is_querying == 1) {
        n->has_query = 0;
        give_quest(g->quest, n->quest_to_give);
        n->base_dialog = "Quests shall give you XP.";
    } else
        n->has_query = 1;
    n->is_querying = 0;
}

void go_to_next_str(interactive_npc_t *npc, game_t *g)
{
    interactive_npc_t *n = npc;

    if (n->is_querying)
        return check_query(n, g);
    if (!n->dialog[n->cur_diag_i + 1] ||
    !n->dialog[n->cur_diag_i + 2] || !n->dialog[n->cur_diag_i + 3]) {
        if (!n->has_query ||
        !my_strncmp(sfText_getString(n->current_dialog), quest_canceled, 10)) {
            g->is_talking = 0;
            switch_clocks();
        } else {
            set_string(n, n->query_dialog);
            n->is_querying = 1;
            move_arrow(n, 0);
        }
    } else {
        n->cur_diag_i += 3;
        set_current_string(n->current_dialog, n->dialog, n->cur_diag_i);
    }
}

void draw_npc(game_t *g, ray_c *r)
{
    interactive_npc_t *npc = g->npc;
    sfVector2f pos = sfSprite_getPosition(npc->npc->sprite);

    sfRenderTexture_drawSprite(r->tex_light, npc->npc->sprite, NULL);
    add_light(r, (sfVector2i){pos.x, pos.y}, 1.5, g->rtex);
    if (!g->is_talking)
        return;
    sfRenderTexture_drawSprite(g->rtex, npc->dialog_box, NULL);
    sfRenderTexture_drawText(g->rtex, npc->current_dialog, NULL);
    if (npc->is_querying) {
        sfRenderTexture_drawSprite(g->rtex, npc->dialog_choose_box, NULL);
        sfRenderTexture_drawText(g->rtex, npc->option_dialogs[0], NULL);
        sfRenderTexture_drawText(g->rtex, npc->option_dialogs[1], NULL);
        sfRenderTexture_drawSprite(g->rtex, npc->dialog_arrow, NULL);
    }
}

void npc_ev(game_t *g, sfEvent ev, int tmp)
{
    interactive_npc_t *npc = g->npc;

    if (ev.key.code == sfKeyEnter && !g->is_talking && !other_are_rushing(g->
    enemies, NULL) && dist_between(npc->npc->sprite, g->player->sprite) < 30) {
        switch_clocks();
        if (npc->type == QUEST && npc->quest_to_give < 0) {
            tmp = rnd_quest(g->quest);
            npc->base_dialog = (tmp > 0) ? quests_texts[tmp - 1] : no_quests;
            npc->has_query = (tmp > 0) ? 1 : 0;
            npc->quest_to_give = tmp;
        }
        if (npc->type == TALK)
            npc->base_dialog = npc_texts[rand() % NB_TEXTS];
        npc->cur_diag_i = 0;
        set_string(npc, npc->base_dialog);
        g->is_talking = 1;
    } else if (ev.key.code == sfKeyEnter && g->is_talking)
        go_to_next_str(npc, g);
    if ((ev.key.code == 73 || ev.key.code == 74) && npc->is_querying)
        move_arrow(npc, (ev.key.code == 73) ? -1 : 1);
}
