/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** free.c
*/

#include "rpg.h"

void destroy_end(end_t *g)
{
    sfRenderTexture_destroy(g->rtex);
    sfText_destroy(g->text);
    sfSprite_destroy(g->player);
    destroy_clock(g->clock);
    destroy_music(g->music);
    destroy_button(g->quit);
    free(g);
}

void update_skills(void)
{
    window_t *win = window(NULL);
    game_t *g = win->menus[GAME];
    choose_save_t *c = win->menus[SELECT_SAVE];
    int prim = c->primary;

    if (prim < 0)
        return;
    c->saves[prim]->infos.skills = *g->skills->data;
}

int is_on_water(npc_t *enemy, list_t *items, sfSprite *item)
{
    sfFloatRect bounds = get_npc_hitbox(enemy);
    sfFloatRect it_bounds;
    list_t *base = items;
    item_t *it;

    if (!base)
        return 0;
    do {
        it = items->data;
        if (it->type != 2) {
            items = items->next;
            continue;
        }
        sfSprite_setPosition(item, it->pos);
        it_bounds = sfSprite_getGlobalBounds(item);
        if (sfFloatRect_intersects(&it_bounds, &bounds, NULL))
            return 1;
        items = items->next;
    } while (base != items);
    return 0;
}

sfVector2u get_graphic_pos(sfVector2f pos, game_t *game, ray_c *r)
{
    return graphic_pos_to_map(pos,
    get_graphic_size(game->level, r), game->path->size, r->cell);
}

void free_textures(void)
{
    while (*textures_list())
        remove_node(textures_list(), 0, destroy_texture);
    sfTexture_destroy(global_texture());
}
