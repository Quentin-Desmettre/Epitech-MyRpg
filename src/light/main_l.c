/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
#include "light.h"
#include "rpg.h"
#define ABS(x) ((x) < 0 ? -(x) : (x))

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

void draw_line(all_t *data, coo_t p_pos, coo_t vraydir, float dis)
{
    coo_t vinter = {p_pos.x + vraydir.x * dis, p_pos.y + vraydir.y *
    dis};

    data->light->vertex.position = (coo_t){vinter.x * data->cell, vinter.y *
    data->cell};
    data->light->vertex.texCoords = (coo_t){vinter.x * data->cell, vinter.y *
    data->cell};
    sfVertexArray_append(data->light->array, data->light->vertex);
}

void find_wall(all_t *data, coo_t p_pos, coo_t p_dir, float intens)
{
    coo_t r_dir = norm((coo_t){p_dir.x - p_pos.x, p_dir.y - p_pos.y});
    coo_t v_ray_step = {sqrt(1 + (r_dir.y / r_dir.x) * (r_dir.y /
    r_dir.x)), sqrt(1 + (r_dir.x / r_dir.y) * (r_dir.x / r_dir.y))};
    coo_t v_mapcheck = p_pos;
    coo_t vstep;
    coo_t v_raylen = step(&vstep, r_dir, p_pos, v_ray_step);
    float dis = 0.0;
    while (dis <= intens) {
        if (v_raylen.x < v_raylen.y) {
            v_mapcheck.x += vstep.x;
            dis = v_raylen.x;
            v_raylen.x += v_ray_step.x;
        } else {
            v_mapcheck.y += vstep.y;
            dis = v_raylen.y;
            v_raylen.y += v_ray_step.y;
        }
        if (_UNDER(v_mapcheck.x, MAP_S) && _UNDER(v_mapcheck.y, MAP_H)
        && data->map[(int)v_mapcheck.x][(int)v_mapcheck.y] == '1')
            break;
    }
    dis = (dis > intens) ? intens : dis;
    data->light->vertex.color.a = (255 - dis / intens * 255) / (15 - intens);
    draw_line(data, p_pos, r_dir, dis);
}

void add_light(all_t *data, sfVector2i pos, float intens, sfRenderWindow *win)
{
    coo_t v_mouse_cell = {(float)(pos.x) / data->cell, (float)(pos.y) / data->cell};
    coo_t p_pos = {(float)(pos.x) / data->cell + 0.05, (float)(pos.y) / data->cell};

    data->light->vertex.position = (coo_t){(p_pos.x) * data->cell, (p_pos.y) *
    data->cell};
    sfCircleShape_setFillColor(data->light->circle, sfGreen);
    for (int j = 0; j < 6; j++) {
        data->light->vertex.position = (coo_t){(p_pos.x) * data->cell, (p_pos.y) *
        data->cell};
        data->light->vertex.texCoords = (coo_t){(p_pos.x) * data->cell, (p_pos.y) *
        data->cell};
        data->light->vertex.color = sfColor_fromRGBA(255, 255, 255, 255 /
        (15 - intens));
        sfVertexArray_append(data->light->array, data->light->vertex);
        sort_angle(data, p_pos);
        lunch_lines(data, p_pos, intens);
        p_pos = rotate(v_mouse_cell, p_pos, 60);
        sfRenderWindow_drawVertexArray(win, data->light->array, &data->state);
        sfVertexArray_clear(data->light->array);
    }
}

void draw_light(all_t *data, game_t *game, sfRenderWindow *win)
{
    sfVector2i tmp = sfMouse_getPositionRenderWindow(win);

    data->cell = sfRenderWindow_getSize(win).y / (game->level->size.x + 2);
    printf("%f\n", data->cell);
    data->state.texture = sfTexture_createFromImage(data->img_rpg, 0);
    add_light(data, tmp, 6, win);
}
