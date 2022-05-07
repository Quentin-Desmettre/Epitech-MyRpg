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

    if (game->quest->quests[nb].finish == 1)
        sfText_setColor(game->quest->name, sfGreen);
    sfRenderTexture_drawText(game->rtex, game->quest->name, NULL);
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
    if (is_to_draw(game))
        draw_quest_prog(game, size);
}

void draw_quest(game_t *game, window_t *win)
{
    sfVector2u size = sfRenderWindow_getSize(win->win);

    if (game->quest->draw == 0)
        return;
    sfRectangleShape_setSize(game->quest->selec, (coo_t){10 / 1080.0 * size
    .y, 95 / 1080.0 * size.y});
    sfText_setScale(game->quest->name, (coo_t){PROP, PROP});
    sfSprite_setPosition(game->quest->back, (coo_t){size.x / 2, size.y / 2});
    sfSprite_setScale(game->quest->back, (coo_t){PROP, PROP});
    sfRenderTexture_drawSprite(game->rtex, game->quest->back, NULL);
    for (int i = 0; i < 4; i++) {
        sfText_setScale(game->quest->desc, (coo_t){size.y / 1080.0,
        size.y / 1080.0});
        sfText_setString(game->quest->name, game->quest->name_qst[i]);
        sfText_setPosition(game->quest->name, (coo_t){size.x / 2 - (430 /
        1080.0 * size.y),
        size.y / 5 + i * (116 / 1080.0 * size.y)});
        desc_draw(game, win->win, i);
        sfText_setColor(game->quest->name, sfWhite);
    }
}

void quest_destroy(quest_data_t *q)
{
    sfSprite_destroy(q->back);
    sfText_destroy(q->name);
    sfText_destroy(q->desc);
    sfRectangleShape_destroy(q->selec);
    free(q);
}
