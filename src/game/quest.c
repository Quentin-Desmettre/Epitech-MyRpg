/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"
#include "player.h"

void secev_quest(game_t *game, sfRenderWindow *win)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win);
    sfVector2u size = sfRenderWindow_getSize(win);
    float tmp = pos.y - size.y / 5;
    tmp /= (116.0 / 1080.0 * size.y);
    if ((int)tmp < 4 && (int)tmp >= 0) {
        for (int i = 0; i < 4; i++)
            game->quest->quests[i].check = 0;
        game->quest->quests[(int)tmp].check = 1;
    }
}

void ev_quest(game_t *game, sfEvent ev, sfRenderWindow *win)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win);
    sfVector2u size = sfRenderWindow_getSize(win);

    if (ev.mouseButton.button == sfMouseLeft) {
        if (pos.x > size.x / 2 - (440 / 1080.0 * size.y) && pos.x < size.x / 2 -
        (195 / 1080.0 * size.y)) {
            secev_quest(game, win);
        }
    }
}

void desc_draw(game_t *game, sfRenderWindow *win, int nb)
{
    sfVector2u size = sfRenderWindow_getSize(win);

    if (game->quest->quests[nb].check == 0)
        return;
    sfText_setPosition(game->quest->name, (sfVector2f){size.x / 2 +
    (50 / 1080.0 * size.y), size.y / 5});
    sfText_setPosition(game->quest->desc, (sfVector2f){size.x / 2 -
    (120 / 1080.0 * size.y), size.y / 3});

    sfRectangleShape_setPosition(game->quest->selec, (sfVector2f){size.x / 2 -
    (455 / 1080.0 * size.y), size.y / 5 + nb * (116 / 1080.0 * size.y) -
    (10 / 1080.0 * size.y)});
    sfText_setString(game->quest->desc, game->quest->desc_qst[nb]);
    sfRenderTexture_drawRectangleShape(game->rtex, game->quest->selec, NULL);
    sfRenderTexture_drawText(game->rtex, game->quest->name, NULL);
    sfRenderTexture_drawText(game->rtex, game->quest->desc, NULL);
}

void draw_quest(game_t *game, sfRenderWindow *win)
{
    sfVector2u size = sfRenderWindow_getSize(win);

    if (game->quest->draw == 0)
        return;
    sfRectangleShape_setSize(game->quest->selec, (sfVector2f){10 / 1080.0 * size
    .y, 95 / 1080.0 * size.y});
    sfText_setScale(game->quest->name, (sfVector2f){size.y / 1080.0, size.y /
    1080.0});
    sfSprite_setPosition(game->quest->back, (sfVector2f){size.x / 2,
    size.y / 2});
    sfSprite_setScale(game->quest->back, (sfVector2f){size.y / 1080.0, size.y /
    1080.0});
    sfRenderTexture_drawSprite(game->rtex, game->quest->back, NULL);
    for (int i = 0; i < 4; i++) {
        sfText_setScale(game->quest->desc, (sfVector2f){size.y / 1080.0,
        size.y / 1080.0});
        sfText_setString(game->quest->name, game->quest->name_qst[i]);
        sfText_setPosition(game->quest->name, (sfVector2f){size.x / 2 - (430 /
        1080.0 * size.y),
        size.y / 5 + i * (116 / 1080.0 * size.y)});
        if (game->quest->quests[i].finish == 1)
            sfText_setColor(game->quest->name, sfGreen);
        sfRenderTexture_drawText(game->rtex, game->quest->name, NULL);

        desc_draw(game, win, i);
        sfText_setColor(game->quest->name, sfWhite);
    }
}

void quest_destroy(quest_data_t *q)
{
    sfTexture_destroy(q->textr);
    sfSprite_destroy(q->back);
    sfText_destroy(q->name);
    sfText_destroy(q->desc);
    sfRectangleShape_destroy(q->selec);
    free(q);
}

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
    }

    quest->name_qst[0] = name_qst[0];
    quest->desc_qst[0] = desc_qst[0];
    quest->is_quest_used[0] = 1;
}

void quest_init(game_t *game)
{
    quest_data_t *quest = malloc(sizeof(quest_data_t));

    quest = malloc(sizeof(quest_data_t));
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
    quest->textr = sfTexture_createFromFile("assets/quest.png", NULL);
    quest->back = sfSprite_create();
    sfSprite_setTexture(quest->back, quest->textr, sfTrue);
    sfSprite_setOrigin(quest->back, (sfVector2f){942 / 2, 720 / 2});
    game->quest = quest;
}
