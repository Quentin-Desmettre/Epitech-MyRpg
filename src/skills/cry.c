/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** cry
*/

#include "rpg.h"
#include "skills.h"

item_t *create_item(int type, sfVector2f pos)
{
    item_t *i = malloc(sizeof(item_t));

    i->pos = pos;
    i->type = type;
    return i;
}

void put_wall_around(path_t *p, sfVector2u pos)
{
    sfVector2u poss[24] = {
        {pos.x - 2, pos.y - 2}, {pos.x - 1, pos.y - 2}, {pos.x, pos.y - 2},
        {pos.x + 1, pos.y - 2}, {pos.x + 2, pos.y - 2}, {pos.x - 2, pos.y - 1},
        {pos.x - 1, pos.y - 1}, {pos.x, pos.y - 1}, {pos.x + 1, pos.y - 1},
        {pos.x + 2, pos.y - 1}, {pos.x - 2, pos.y}, {pos.x - 1, pos.y},
        {pos.x + 1, pos.y}, {pos.x + 2, pos.y}, {pos.x - 2, pos.y + 1},
        {pos.x - 1, pos.y + 1}, {pos.x, pos.y + 1}, {pos.x + 1, pos.y + 1},
        {pos.x + 2, pos.y + 1}, {pos.x - 2, pos.y + 2}, {pos.x - 1, pos.y + 2},
        {pos.x, pos.y + 2}, {pos.x + 1, pos.y + 2}, {pos.x + 2, pos.y + 2}
    };

    for (int i = 0; i < 24; i++)
        if (poss[i].x < p->size.y && poss[i].y < p->size.x)
            p->map[poss[i].x][poss[i].y] = -1;
}

void cry_event(game_t *game)
{
    sfVector2f pos = sfSprite_getPosition(game->player->sprite);
    window_t *win = window(NULL);
    ray_c *r = win->menus[LIGHT];
    float height = get_npc_hitbox(game->player).height;
    choose_save_t *c = win->menus[SELECT_SAVE];
    player_info_t *infos = &c->saves[c->primary]->infos;

    if (game->skills->data->tab[CRY] > 0 && C_TIME(game) > 60 /
    game->skills->data->tab[CRY] SEC && infos->thirst_percent > 40) {
        restart_clock(game->skills->clocks[CRY]);
        append_node(&game->items, create_item(2,
        (sfVector2f){pos.x, pos.y + height * 0.35}));
        update_path(game->path, game->level, r, pos);
        infos->thirst_percent -= 40;
    }
}

void draw_cry_sec(game_t *game, sfVector2f size)
{
    char *str = nbr_to_str(60 / game->skills->data->tab[CRY] -
    C_TIME(game) / 1000000);
    char *concat = str_concat(2, str, "  sec");
    sfText *text = init_text(concat, size.y / 40);

    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 242.0 * SCALE(size)});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfText_destroy(text);
    my_free("pp", concat, str);
}

void draw_cry(game_t *game, sfVector2f size)
{
    sfSprite *sprite = game->skills->sk_sprites[CRY][C_TIME(game) >
    60 / game->skills->data->tab[CRY] SEC];
    sfText *text = init_text("Press C", size.y / 40);

    sfSprite_setScale(sprite, (sfVector2f){SCALE(size) / 2, SCALE(size) / 2});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 0.495 * size.x, size.y / 2 + 230.0 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 - 0.45 * size.x, size.y / 2 + 242.0 * SCALE(size)});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    if (C_TIME(game) > 60 / game->skills->data->tab[CRY] SEC)
        sfRenderTexture_drawText(game->rtex, text, NULL);
    else
        draw_cry_sec(game, size);
    sfText_destroy(text);
}
