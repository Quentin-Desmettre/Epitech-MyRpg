/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create_npc.c
*/

#include "rpg.h"
#include "npc_texts.h"

void destroy_interactive_npc(interactive_npc_t *i)
{
    if (!i)
        return;
    if (i->dialog)
        my_free("P", i->dialog);
    sfText_destroy(i->current_dialog);
    sfSprite_destroy(i->dialog_arrow);
    sfSprite_destroy(i->dialog_box);
    sfSprite_destroy(i->dialog_choose_box);
    destroy_npc(i->npc);
    sfText_destroy(i->option_dialogs[0]);
    sfText_destroy(i->option_dialogs[1]);
    free(i);
}

static void setup_base(interactive_npc_t *i, game_t *g, ray_c *r)
{
    sfVector2f win_s = win_size(window(NULL));
    sfFloatRect bounds;
    int test[6] = {9, 9, 9, 9, 2, 0};

    i->current_dialog = init_text("", 10);
    i->npc = npc_create("tnicd", "assets/npc.png", test, pl_rects
    , (sfVector2f){1.2, 1.2}, IDLE);
    sfSprite_setOrigin(i->npc->sprite, (sfVector2f){32, 32});
    sfSprite_setPosition(i->npc->sprite, rnd_point(g, r, i->npc));
    i->dialog_box = init_sprite_from_texture(get_texture_by_name(PNJ_TALK_BOX));
    set_sprite_size(i->dialog_box, (sfVector2f){win_s.x * 0.7, win_s.y * 0.2});
    center_sprite(i->dialog_box);
    sfSprite_setPosition(i->dialog_box,
    (sfVector2f){win_s.x * 0.57, win_s.y * 0.86});
    bounds = sfSprite_getGlobalBounds(i->dialog_box);
    sfText_setCharacterSize(i->current_dialog, win_s.y * 0.2 * 0.2);
    sfText_setPosition(i->current_dialog, (sfVector2f){bounds.left +
    bounds.width * 0.06, bounds.top + bounds.height * 0.13});
    set_string(i, i->base_dialog);
}

static void quest_npc_create(interactive_npc_t *i, int dialog, sfVector2f win_s)
{
    i->has_query = (dialog > 0) ? 1 : 0;
    i->query_dialog = quest_query;
    i->dialog_choose_box = sfSprite_create();
    sfSprite_setTexture(i->dialog_choose_box,
    get_texture_by_name(OPT_DIALOG), 0);
    set_sprite_size(i->dialog_choose_box,
    (sfVector2f){win_s.x * 0.2,win_s.x * 0.15});
    sfSprite_setPosition(i->dialog_choose_box,
    (sfVector2f){win_s.x * 0.75, win_s.y * 0.65});
    i->dialog_arrow = sfSprite_create();
    sfSprite_setTexture(i->dialog_arrow, get_texture_by_name(ARROW_PNG), 0);
    set_sprite_size(i->dialog_arrow,
    (sfVector2f){win_s.x * 0.06, win_s.x * (0.06 * 453 / 796.0)});
    sfSprite_setPosition(i->dialog_arrow,
    (sfVector2f){win_s.x * 0.77, win_s.y * 0.685});
}

interactive_npc_t *create_quest_npc(int dialog, game_t *g, ray_c *r)
{
    interactive_npc_t *i = malloc(sizeof(interactive_npc_t));
    sfVector2f win_s = win_size(window(NULL));

    memset(i, 0, sizeof(interactive_npc_t));
    i->base_dialog = (dialog > 0) ? quests_texts[dialog - 1] : no_quests;
    setup_base(i, g, r);
    quest_npc_create(i, dialog, win_s);
    for (int j = 0; j < 2; j++) {
        i->option_dialogs[j] = init_text(j ? "No" : "Yes", win_s.x * 0.04);
        sfText_setPosition(i->option_dialogs[j],
        (sfVector2f){win_s.x * 0.84, win_s.y * 0.68 + win_s.x * 0.05 * j});
        i->second_dialogs[j] = (j ? quest_canceled : quest_accepted);
    }
    i->quest_to_give = dialog;
    i->type = QUEST;
    sfSprite_setScale(i->npc->sprite, (sfVector2f){1.2 / 1080 * win_s.y
    , 1.2 / 1080 * win_s.y});
    return i;
}

interactive_npc_t *create_talk_npc(game_t *g, ray_c *r)
{
    interactive_npc_t *i = malloc(sizeof(interactive_npc_t));
    sfVector2f size_win = win_size(window(NULL));

    memset(i, 0, sizeof(interactive_npc_t));
    i->base_dialog = npc_texts[rand() % NB_TEXTS];
    setup_base(i, g, r);
    sfSprite_setScale(i->npc->sprite, (sfVector2f){1.2 / 1080 * size_win.y
    , 1.2 / 1080 * size_win.y});
    i->type = TALK;
    return i;
}
