/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** inter_npc
*/

#ifndef INTER_NPC_H_
    #define INTER_NPC_H_

    #define PNJ_SPRITE "assets/pnj.png"
    #define PNJ_TALK_BOX "assets/pnj_box.png"
    #define TALK 0
    #define QUEST 1
    #define OPT_DIALOG "assets/pnj_opt_box.png"
    #define ARROW_PNG "assets/arrow.png"
    #define NB_TEXTS 5

    #include "rpg.h"
    #include "light.h"
    #include "player.h"

typedef struct inter_c {
    npc_t *npc;
    sfSprite *dialog_box;
    sfSprite *dialog_arrow;
    sfSprite *dialog_choose_box;
    sfText *current_dialog;
    char **dialog;
    int cur_diag_i;

    char const *base_dialog;

    int has_query;
    int is_querying;
    char const *query_dialog;
    sfText *option_dialogs[2];
    char const *second_dialogs[2];

    int type;
    int quest_to_give;
} interactive_npc_t;

sfVector2f rnd_point(game_t *g, ray_c *data, npc_t *npc);

interactive_npc_t *create_quest_npc(int dialog, game_t *g, ray_c *r);
interactive_npc_t *create_talk_npc(game_t *g, ray_c *r);
void go_to_next_str(interactive_npc_t *npc, game_t *g);
void draw_npc(game_t *g, ray_c *r);
void npc_ev(game_t *g, sfEvent ev);
void set_current_string(sfText *text, char **words, int index);
void set_string(interactive_npc_t *i, char const *dialog);


sfTexture *dialog_box(void);
sfTexture *arrow_tex(void);
sfTexture *opt_diag_box(void);

#endif /* !INTER_NPC_H_ */
