/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** quest_progress
*/

#include "rpg.h"

int is_to_draw(game_t *game)
{
    const char *str = sfText_getString(game->quest->name);

    for (int i = 1; i < 4; i++) {
        if (!my_strcmp(str, name_qst[i]))
            return i;
    }
    return 0;
}

void draw_quest_prog(game_t *game, sfVector2u size)
{
    sfText *text = init_text("dtfyguhi", size.y / 40);
    char *str = nbr_to_str(game->quest->progress[is_to_draw(game)][0]);
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
    int idx_qst = index_str_in_array(game->quest->desc_qst, desc_qst[quest]);

    if (!game->quest->is_quest_used[quest] || idx_qst < 0 || idx_qst > 4 ||
    game->quest->quests[idx_qst].finish)
        return;
    game->quest->progress[quest][0] += nb;
    if (game->quest->progress[quest][0] >= game->quest->progress[quest][1]) {
        game->quest->quests[idx_qst].finish = 1;
        game->quest->is_quest_used[quest] = 0;
        for (int i = idx_qst; i < 3; i++) {
            game->quest->name_qst[i] = game->quest->name_qst[i + 1];
            game->quest->desc_qst[i] = game->quest->desc_qst[i + 1];
        }
        game->quest->name_qst[3] = "";
        game->quest->desc_qst[3] = "";
        game->quest->progress[quest][0] = 0;
        game->quest->quests[idx_qst].finish = 0;
        add_xp(game, quest == 1 ? 15 : 5);
    }
}
