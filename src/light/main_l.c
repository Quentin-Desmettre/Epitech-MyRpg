/*
** EPITECH PROJECT, 2021
** my_printf.c
** File description:
** my_printf.c
*/
#include <stdio.h>
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

    data->light->vertex.position = (coo_t){vinter.x * data->cell + data->offset + data->off_view.x, vinter.y *
    data->cell + data->off_view.y};
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
    coo_t v_mouse_cell = {(float)(pos.x) / data->cell, (float)(pos.y) / data->
    cell};
    coo_t p_pos = {(float)(pos.x) / data->cell + 0.1, (float)(pos.y) / data->
    cell};

    data->light->vertex.position = (coo_t){(p_pos.x) * data->cell, (p_pos.y) *
    data->cell};
    for (int j = 0; j < 6; j++) {
        data->light->vertex.position = (coo_t){(p_pos.x) * data->cell +
        data->offset + data->off_view.x, (p_pos.y) * data->cell + data->off_view.y};
        data->light->vertex.texCoords = (coo_t){(p_pos.x) * data->cell,
        (p_pos.y) * data->cell};
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

void draw_map(all_t *data, game_t *game, sfRenderWindow *win)
{
    // sfVector2i tmp = sfMouse_getPositionRenderWindow(win);
    sfVector2f pos = sfSprite_getPosition(game->player->sprite);
    sfVector2i tmp = (sfVector2i){pos.x, pos.y};
    sfVector2u size_win = sfRenderWindow_getSize(win);

    sfSprite_setScale(game->player->sprite, (sfVector2f){1.2 / 1080 * size_win.y,  1.2 / 1080 * size_win.y});
    data->offset = (size_win.x - ((size_win.y) / 600.0 * 800.0)) / 2.0;
    if (tmp.y > size_win.y && -data->off_view.y < size_win.y)
        data->off_view.y -= 5;
    else if (tmp.y < size_win.y && -data->off_view.y > 0)
        data->off_view.y += 5;
    if (tmp.x > (int)(size_win.x) - data->offset * 2 && -data->off_view.x
    < (int)(size_win.x) - data->offset * 2)
        data->off_view.x -= 5;
    else if (tmp.x < (int)(size_win.x) - data->offset * 2 && -data->off_view.x > 0)
        data->off_view.x += 5;
    data->off_view.y;
    data->cell = sfRenderWindow_getSize(win).y / (15);
    sfSprite_setScale(data->floor, (sfVector2f){data->cell / 64, data->cell
    / 64});
    sfSprite_setScale(data->wall, (sfVector2f){data->cell / 64, data->cell
    / 128});
    data->state.texture = sfRenderTexture_getTexture(data->tex_light);
    add_light(data, tmp, 5, win);
}
