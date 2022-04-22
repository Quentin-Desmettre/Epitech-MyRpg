/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc_collisions
*/

#include "rpg.h"
#include "player.h"

sfFloatRect get_npc_hitbox(npc_t *player)
{
    sfFloatRect whole = sfSprite_getGlobalBounds(player->sprite);
    float width_fac = 0.45;

    whole.left += whole.width * ((1 - width_fac) / 2.0);
    whole.width *= width_fac;
    whole.top += whole.height * 0.37;
    whole.height *= 0.8;
    return whole;
}

int pnj_colliding2(npc_t *player, int i, int j, ray_c *data)
{
    sfFloatRect wall_hitbox;
    sfFloatRect hitbox = get_npc_hitbox(player);

    if (data->map[i][j] == '1') {
        sfSprite_setPosition(data->wall,
        (sfVector2f){i * data->cell, j * data->cell + data->cell / 2});
        wall_hitbox = sfSprite_getGlobalBounds(data->wall);
        if (sfFloatRect_intersects(&hitbox, &wall_hitbox, NULL))
            return 1;
    }
    return 0;
}

int is_pnj_colliding(ray_c *data, npc_t *player, level_t *level)
{
    coo_t size = level->size;
    int to_return = 0;

    for (int i = 0; i < size.y + 2 && !to_return; i++) {
        for (int j = 0; j < size.x + 2 && !to_return; j++)
            to_return = pnj_colliding2(player, i, j, data);
    }
    return to_return;
}
