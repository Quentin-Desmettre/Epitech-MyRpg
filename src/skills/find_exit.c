/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** find_exit
*/

#include "rpg.h"
#include "skills.h"

int find_exit_two(ray_c *data, game_t *game, int i)
{
    for (int j = 0; j < game->level->size.x + 2; j++) {
        if (data->map[i][j] == '2') {
            game->yes ? sfSound_play(game->yes) : 0;
            return 1;
        }
    }
    return 0;
}

void find_exit_event(game_t *game)
{
    ray_c *data = window(NULL)->menus[LIGHT];

    if (!(game->skills->data->tab[FIND_EXIT] > 0 && F_TIME(game) >
    F_WAIT(game->skills->data->tab[FIND_EXIT]) SEC))
        return;
    restart_clock(game->skills->clocks[FIND_EXIT]);
    for (int i = 0; i < game->level->size.y + 2; i++) {
        if (find_exit_two(data, game, i))
            return;
    }
    if (game->no)
        sfSound_play(game->no);
}

void draw_find_exit_sec(game_t *game, sfVector2f size)
{
    char *str = nbr_to_str(F_WAIT(game->skills->data->tab[FIND_EXIT]) -
    F_TIME(game) / 1000000);
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
    [FIND_EXIT][F_TIME(game) > F_WAIT(game->skills->data->tab[FIND_EXIT]) SEC];
    sfText *text = init_text("Press F", size.y / 40);

    sfSprite_setScale(sprite, (sfVector2f){SCALE(size) / 2, SCALE(size) / 2});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 0.495 * size.x, size.y / 2 + 180.0 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 192.0 * SCALE(size)});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    if (F_TIME(game) > F_WAIT(game->skills->data->tab[FIND_EXIT]) SEC)
        sfRenderTexture_drawText(game->rtex, text, NULL);
    else
        draw_find_exit_sec(game, size);
    sfText_destroy(text);
}
