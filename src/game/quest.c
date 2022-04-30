/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** game
*/

#include "rpg.h"
#include "player.h"

static const char *name_qst[6] = {
    "Welcome",
    "Stay =)",
    "Good bye",
    "Beat em up",
    "Drink",
    "Pills !!!"
};

static const char *desc_qst[6] = {
    "Hey welcome in the backrooms.\n The backrooms are safe. Be quiet\n"
    "Try to exit\n Good luck !\n\n Have fun =)",
    "Congraluration !\n"
    "You success to exit the level 0.\n"
    "Try to exit this level\nor you can stay here with me\nand my friends =)",
    "You are in the level 2 it's the last one\n"
    "I hope\n""Try to exit\nbut don't try to go to the next level !\n"
    "Search the level fun =)",
    "Kill 10 entity !\n It's fun and healthy !\n   =)",
    "Do you like almond water?\n I could drink dozens"
    "\n Try to drink 10 bottles !",
    "Apparently overdoses are bad.\n Try anyway take 10 pills !\n\n"
    "                  =)"
};

void secev_quest(game_t *game, sfRenderWindow *win)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win);
    sfVector2u size = sfRenderWindow_getSize(win);
    float tmp = pos.y - size.y / 5;
    tmp /= (116.0 / 1080.0 * size.y);
    if ((int)tmp < 6 && (int)tmp >= 0) {
        for (int i = 0; i < 6; i++)
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

    sfRectangleShape_setPosition(game->quest->selec, (sfVector2f){size.x / 2 - (
    455 / 1080.0 * size.y),
        size.y / 5 + nb * (116 / 1080.0 * size.y) - (10 / 1080.0 * size.y)});
    sfText_setString(game->quest->desc, desc_qst[nb]);
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
    for (int i = 0; i < 6; i++) {
        sfText_setString(game->quest->name, name_qst[i]);
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

void quest_init(game_t *game)
{
    game->quest = malloc(sizeof(quest_data_t));
    game->quest->draw = 0;
    game->quest->selec = create_rectangle((sfVector2f){0, 0}, sfWhite
    , 0, sfBlack);
    game->quest->name = init_text(0, 50);
    game->quest->desc = init_text(0, 30);
    for (int i = 0; i < 6; i++) {
        game->quest->quests[i].check = 0;
        game->quest->quests[i].finish = 0;
    }
    game->quest->quests[0].check = 1;
    game->quest->textr = sfTexture_createFromFile("assets/quest.png", NULL);
    game->quest->back = sfSprite_create();
    sfSprite_setTexture(game->quest->back, game->quest->textr, sfTrue);
    sfSprite_setOrigin(game->quest->back, (sfVector2f){942 / 2, 720 / 2});
}
