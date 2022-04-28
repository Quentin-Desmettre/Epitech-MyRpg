/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** cry
*/

#include "rpg.h"
#include "skills.h"

void cry_event(game_t *game)
{
    if (game->skills->data->tab[CRY] > 0 && C_TIME(game) > 60 SEC) {
        // cry action
        restart_clock(game->skills->clocks[CRY]);
    }
}

void draw_cry_sec(game_t *game, sfVector2f size)
{
    char *str = nbr_to_str(60 - C_TIME(game) / 1000000);
    char *concat = str_concat(2, str, "  sec");
    sfText *text = init_text(concat, size.y / 40);

    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 880.0 * SCALE(size), size.y / 2 + 242.0 * SCALE(size)});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    my_free("pp", concat, str);
}

void draw_cry(game_t *game, sfVector2f size)
{
    sfSprite *sprite = game->skills->sk_sprites[CRY][C_TIME(game) > 60 SEC];
    sfText *text = init_text("Press C", size.y / 40);

    sfSprite_setScale(sprite, (sfVector2f){SCALE(size) / 2, SCALE(size) / 2});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 950.0 * SCALE(size), size.y / 2 + 230.0 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 880.0 * SCALE(size), size.y / 2 + 242.0 * SCALE(size)});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    if (!game->skills->sprint && C_TIME(game) > 60 SEC)
        sfRenderTexture_drawText(game->rtex, text, NULL);
    else
        draw_cry_sec(game, size);
    sfText_destroy(text);
}
