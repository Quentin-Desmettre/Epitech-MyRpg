/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "rpg.h"

coo_t step(coo_t *vstep, coo_t vraydir
, coo_t p_pos, coo_t v_ray_step)
{
    coo_t v_raylen;

    if (vraydir.x < 0) {
        vstep->x = -1;
        v_raylen.x = ((p_pos.x) - (int)p_pos.x) * v_ray_step.x;
    } else {
        vstep->x = 1;
        v_raylen.x = ((int)(p_pos.x + 1.0) - p_pos.x) * v_ray_step.x;
    }
    if (vraydir.y < 0) {
        vstep->y = -1;
        v_raylen.y = ((p_pos.y) - (int)p_pos.y) * v_ray_step.y;
    } else {
        vstep->y = 1;
        v_raylen.y = ((int)(p_pos.y + 1.0) - p_pos.y) * v_ray_step.y;
    }
    return v_raylen;
}

void draw_line(ray_c *data, coo_t p_pos, coo_t vraydir, float dis)
{
    coo_t vinter = {p_pos.x + vraydir.x * dis, p_pos.y + vraydir.y *
    dis};

    data->light->vertex.position = (coo_t){vinter.x *
    data->cell + data->off_view.x, vinter.y *
    data->cell + data->off_view.y};
    data->light->vertex.texCoords = (coo_t){vinter.x * data->cell, vinter.y *
    data->cell};
    sfVertexArray_append(data->light->array, data->light->vertex);
}

void find_wall(ray_c *data, coo_t p_pos, coo_t p_dir, float intens)
{
    coo_t r_dir = norm((coo_t){p_dir.x - p_pos.x, p_dir.y - p_pos.y});
    coo_t v_ray_step = {sqrt(1 + (r_dir.y / r_dir.x) * (r_dir.y /
    r_dir.x)), sqrt(1 + (r_dir.x / r_dir.y) * (r_dir.x / r_dir.y))};
    coo_t mapcheck = p_pos;
    coo_t vstep;
    coo_t v_raylen = step(&vstep, r_dir, p_pos, v_ray_step);
    float dis = loop_find_wall(data, intens, (coo_t [3]){vstep, v_ray_step,
    v_raylen}, mapcheck);

    dis = (dis > intens) ? intens : dis;
    data->light->vertex.color.a = (255 - dis / intens * 255) / (12 - intens);
    draw_line(data, p_pos, r_dir, dis);
}

void add_light(ray_c *data, sfVector2i pos, float intens, sfRenderTexture *win)
{
    coo_t v_mouse_cell = {(pos.x) / data->cell, (pos.y) / data->cell};
    coo_t p_pos = {(float)(pos.x) / data->cell + 0.05, (float)(pos.y) / data->
    cell};

    data->light->vertex.position = (coo_t){(p_pos.x) * data->cell, (p_pos.y) *
    data->cell};
    for (int j = 0; j < 5; j++) {
        data->light->vertex.position = (coo_t){(p_pos.x) * data->cell
        + data->off_view.x, (p_pos.y) * data->cell + data->off_view.y};
        data->light->vertex.texCoords = (coo_t){(p_pos.x) * data->cell,
        (p_pos.y) * data->cell};
        data->light->vertex.color = sfColor_fromRGBA(255, 255, 255, 255 /
        (12 - intens));
        sfVertexArray_append(data->light->array, data->light->vertex);
        sort_angle(data, p_pos);
        lunch_lines(data, p_pos, intens);
        p_pos = rotate(v_mouse_cell, p_pos, 72);
        sfRenderTexture_drawVertexArray(win, data->light->array, &data->state);
        sfVertexArray_clear(data->light->array);
    }
}

void draw_map(ray_c *data, game_t *game, window_t *win)
{
    sfVector2f pos = sfSprite_getPosition(game->player->sprite);
    sfVector2i tmp = (sfVector2i){pos.x, pos.y};
    sfVector2u size_win = sfRenderWindow_getSize(win->win);

    change_form(game, size_win, tmp, data);
    data->state.texture = sfRenderTexture_getTexture(data->tex_light);
    if (data->map[(int)(pos.x / data->cell)] &&
    data->map[(int)(pos.x / data->cell)][(int)(pos.y / data->cell)] == '2') {
        next_level(win);
        new_room(game, data);
    }
    if (win->state == GAME)
        add_light(data, tmp, 5, game->rtex);
    change_room(game, data, pos);
}
