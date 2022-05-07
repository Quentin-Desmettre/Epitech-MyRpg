/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** quest_progress
*/

#include "rpg.h"

void draw_quest_prog(game_t *game, sfVector2u size, int nb)
{
    sfText *text = init_text("dtfyguhi", size.y / 40);
    char *str = nbr_to_str(game->quest->progress[nb][0]);
    char *concat;

    concat = str_concat(3, "Progression :  ", str, " / 10");
    sfText_setString(text, concat);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, (sfVector2f){size.x / 2 -
    (120 / 1080.0 * size.y), size.y * 0.7});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    my_free("pp", str, concat);
    sfText_destroy(text);
}

void add_quest_prog(game_t *game, int quest, int nb)
{
    if (!game->quest->is_quest_used || game->quest->quests[quest].finish)
        return;
    game->quest->progress[quest][0] += nb;
    if (game->quest->progress[quest][0] >= game->quest->progress[quest][1]) {
        game->quest->progress[quest][0] = 0;
        game->quest->quests[quest].finish = 1;
        add_xp(game, quest == 1 ? 15 : 5);
    }
}
