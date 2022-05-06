/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** find_exit
*/

#include "rpg.h"
#include "skills.h"

void find_exit_event(game_t *game)
{
    if (game->skills->data->tab[FIND_EXIT] > 0 && F_TIME(game) > 60 SEC) {
        // find_exit  action
        restart_clock(game->skills->clocks[FIND_EXIT]);
    }
}

void draw_find_exit_sec(game_t *game, sfVector2f size)
{
    char *str = nbr_to_str(60 - F_TIME(game) / 1000000);
    char *concat = str_concat(2, str, "  sec");
    sfText *text = init_text(concat, size.y / 40);

    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 192.0 * SCALE(size)});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    my_free("pp", concat, str);
    sfText_destroy(text);
}

void draw_find_exit(game_t *game, sfVector2f size)
{
    sfSprite *sprite = game->skills->sk_sprites
    [FIND_EXIT][F_TIME(game) > 60 SEC];
    sfText *text = init_text("Press F", size.y / 40);

    sfSprite_setScale(sprite, (sfVector2f){SCALE(size) / 2, SCALE(size) / 2});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 0.495 * size.x, size.y / 2 + 180.0 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 192.0 * SCALE(size)});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    if (F_TIME(game) > 60 SEC)
        sfRenderTexture_drawText(game->rtex, text, NULL);
    else
        draw_find_exit_sec(game, size);
    sfText_destroy(text);
}
