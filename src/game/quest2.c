/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"

int nb_used(quest_data_t *q)
{
    int nb = 0;

    for (int i = 0; i < 4; i++)
        if (q->is_quest_used[i])
            nb++;
    return nb;
}

void give_quest(quest_data_t *q, int d)
{
    int nb = nb_used(q);

    q->is_quest_used[d] = 1;
    q->desc_qst[nb] = desc_qst[d];
    q->name_qst[nb] = name_qst[d];
}

int rnd_quest(quest_data_t *current_quests)
{
    int *used = current_quests->is_quest_used;
    int quest = 0;

    if (current_quests->name_qst[3][0])
        return -1;
    while (used[quest])
        quest = rand() % 4;
    return quest;
}

void init_quests(quest_data_t *quest)
{
    for (int i = 0; i < 4; i++) {
        quest->is_quest_used[i] = 0;
        quest->name_qst[i] = "";
        quest->desc_qst[i] = "";
        quest->progress[i][0] = 0;
        quest->progress[i][1] = QUEST_MAX;
    }
    quest->desc_qst[4] = NULL;

    quest->name_qst[0] = name_qst[0];
    quest->desc_qst[0] = desc_qst[0];
    quest->is_quest_used[0] = 1;
}

void quest_init(game_t *game)
{
    quest_data_t *quest = malloc(sizeof(quest_data_t));

    quest->draw = 0;
    quest->selec = create_rectangle((sfVector2f){0, 0},
    sfWhite, 0, sfBlack);
    init_quests(quest);
    quest->name = init_text(0, 45);
    quest->desc = init_text(0, 30);
    for (int i = 0; i < 4; i++) {
        quest->quests[i].check = 0;
        quest->quests[i].finish = 0;
    }
    quest->quests[0].check = 1;
    quest->textr = get_texture_by_name(QUEST_PNG);
    quest->back = sfSprite_create();
    sfSprite_setTexture(quest->back, quest->textr, sfTrue);
    sfSprite_setOrigin(quest->back, (sfVector2f){942 / 2, 720 / 2});
    game->quest = quest;
}
