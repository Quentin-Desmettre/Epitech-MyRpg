/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/

#include <stdio.h>
#include "rpg.h"

void set_light(ray_c *data)
{
    data->map[MAP_S] = 0;
    data->state.shader = 0;
    data->state.blendMode = sfBlendAlpha;
    data->state.transform = sfTransform_Identity;
    data->light->array = sfVertexArray_create();
    data->light->circle = sfCircleShape_create();
    data->light->vertex.color = sfWhite;
    sfCircleShape_setFillColor(data->light->circle, sfRed);
    sfCircleShape_setRadius(data->light->circle, 12.5);
    sfCircleShape_setOrigin(data->light->circle, (sfVector2f){12.5, 12.5});
    sfVertexArray_setPrimitiveType(data->light->array, sfTriangleFan);
    data->angles = malloc(sizeof(dir_t) * MAP_S * MAP_S);
    data->buffer = malloc(sizeof(dir_t) * MAP_S * MAP_S);
    data->light->index = 0;
    for (int i = 0; i < MAP_S; i++)
        for (int j = 0; j < MAP_H; j++)
            find_angles(i, j, data);
    wall_light(data);
}

void set_room_map(ray_c *data)
{
    data->lvl = 0;
    data->tex_light = sfRenderTexture_create(1920 * 2, 1080 * 2, 0);
    data->floor = sfSprite_create();
    data->wall = sfSprite_create();
    set_wall(data);
    sfSprite_setScale(data->wall, (sfVector2f){1, 0.5});
    data->noise_sp = sfSprite_create();
    data->noise = get_texture_by_name(NOISE_PNG);
    sfSprite_setTexture(data->noise_sp, data->noise, 0);
    sfSprite_setScale(data->noise_sp, (sfVector2f){2.75, 2.75});
    sfSprite_setColor(data->noise_sp, (sfColor){255, 255, 255, 30});
    sfSprite_setTexture(data->floor, data->floor_tex[0], 0);
    sfSprite_setTexture(data->wall, data->wall_tex[0], 0);
    data->off_view = (coo_t){0, 0};
    data->time = create_clock();
}

char choose_item(int i, int j, char c, game_t *game)
{
    int random = rand() % 2000;
    item_t *tmp = 0;

    if (c == 'X')
        return '1';
    if (random < 8) {
        tmp = malloc(sizeof(item_t));
        tmp->type = 0;
        tmp->pos = (coo_t){i, j};
        append_node(&game->items, tmp);
    } else if (random < 16) {
        tmp = malloc(sizeof(item_t));
        tmp->type = 1;
        tmp->pos = (coo_t){i, j};
        append_node(&game->items, tmp);
    }
    return (random == 69 || random == 420) ? '2' : '0';
}

int set_game_light(ray_c *new, game_t *map)
{
    if (new == 0)
        return 0;
    new->map = malloc(sizeof(char *) * (MAP_S + 1));
    new->light = malloc(sizeof(light_t));
    if (new->map == 0 || new->light == 0)
        return 0;
    for (int i = 0; i < MAP_S; i++) {
        new->map[i] = malloc(sizeof(char) * (MAP_H + 1));
        if (new->map[i] == 0)
            return 0;
        for (int j = 0; j < MAP_H; j++)
            new->map[i][j] = '0';
        new->map[i][MAP_H] = '\0';
    }
    for (int i = 0; i < map->level->size.y + 2; i++)
        for (int j = 0; j < map->level->size.x + 2; j++)
            new->map[i][j] = choose_item(i, j, map->level->room[j][i], map);
    set_light(new);
    set_room_map(new);
    return 1;
}

void dest_light(ray_c *data)
{
    sfVertexArray_destroy(data->light->array);
    sfCircleShape_destroy(data->light->circle);
    free(data->light);
    sfSprite_destroy(data->floor);
    sfSprite_destroy(data->wall);
    sfSprite_destroy(data->noise_sp);
    for (int i = 0; data->map[i] != 0; i++)
        free(data->map[i]);
    free(data->map);
    free(data->angles);
    free(data->buffer);
    destroy_clock(data->time);
    sfRenderTexture_destroy(data->tex_light);
    free(data);
}
