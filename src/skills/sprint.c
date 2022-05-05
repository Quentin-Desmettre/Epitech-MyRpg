/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** sprint
*/

#include "rpg.h"
#include "skills.h"

void sprint_event(game_t *game)
{
    int speed_bonus = 100;
    static int bonus_given = 0;

    if (game->skills->data->tab[SPRINT] > 0 && S_TIME(game) > 30 SEC
    && !game->skills->sprint) {
        game->skills->sprint = 1;
        bonus_given = game->player->speed;
        game->player->speed *= 1 + speed_bonus / 100;
        bonus_given = game->player->speed - bonus_given;
        restart_clock(game->skills->clocks[SPRINT]);
    }
    if (game->skills->sprint && S_TIME(game) >
    game->skills->data->tab[SPRINT] * 5 SEC) {
        game->skills->sprint = 0;
        game->player->speed -= bonus_given;
        restart_clock(game->skills->clocks[SPRINT]);
    }
}

void draw_sprint_sec(game_t *game, sfVector2f size)
{
    char *str = nbr_to_str((game->skills->sprint ? game->skills->
    data->tab[SPRINT] * 5 : 30) - S_TIME(game) / 1000000);
    char *concat = str_concat(2, str, "  sec");
    sfText *text = init_text(concat, size.y / 40);

    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 292.0 * SCALE(size)});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfText_destroy(text);
    my_free("pp", concat, str);
}

void draw_sprint(game_t *game, sfVector2f size)
{
    sfSprite *sprite = game->skills->sk_sprites[SPRINT]
    [S_TIME(game) > 30 SEC || game->skills->sprint];
    sfText *text = init_text("Press L-Shift", size.y / 40);

    if (game->skills->sprint)
        sprint_event(game);
    sfSprite_setScale(sprite, (sfVector2f){SCALE(size) / 2, SCALE(size) / 2});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 0.495 * size.x, size.y / 2 + 280.0 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 292.0 * SCALE(size)});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    if (!game->skills->sprint && S_TIME(game) > 30 SEC)
        sfRenderTexture_drawText(game->rtex, text, NULL);
    else
        draw_sprint_sec(game, size);
    sfText_destroy(text);
}
