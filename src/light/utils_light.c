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


coo_t norm(coo_t vector)
{
    float w = sqrt(vector.x * vector.x + vector.y * vector.y);
    vector.x /= w;
    vector.y /= w;
    return vector;
}

coo_t rotate(coo_t center, coo_t rt, float angle)
{
    float p_angle = angle * (PI / 180);
    float s = sin(p_angle);
    float c = cos(p_angle);
    float xnew;
    float ynew;

    rt.x -= center.x;
    rt.y -= center.y;
    xnew = rt.x * c - rt.y * s;
    ynew = rt.x * s + rt.y * c;
    rt.x = xnew + center.x;
    rt.y = ynew + center.y;
    return rt;
}


void lunch_lines(all_t *data, coo_t p_pos, float intens)
{
    coo_t dir;

    for (int i = 0; i < data->light->index; i++) {
        if (data->angles[i].is_triple == 1) {
            dir = data->angles[i].coo;
            find_wall(data, p_pos, rotate(p_pos, dir, -0.00001), intens);
            find_wall(data, p_pos, dir, intens);
            find_wall(data, p_pos, rotate(p_pos, dir, 0.00001), intens);
        } else
            find_wall(data, p_pos, data->angles[i].coo, intens);
    }
    find_wall(data, p_pos, rotate(p_pos, data->angles->coo, -0.00001), intens);
}

void sort_angle(all_t *data, coo_t p_pos)
{
    coo_t tmp;
    float o;
    float h;

    for (int i = 0; i < data->light->index; i++) {
        tmp = data->angles[i].coo;
        o = ABS(p_pos.x - tmp.x);
        h = sqrtf(powf(p_pos.x - tmp.x, 2) + powf(p_pos.y - tmp.y, 2));
        data->angles[i].angle = asinf(o / h);
        if (p_pos.y < tmp.y && p_pos.x <= tmp.x) {
            data->angles[i].angle = PI - data->angles[i].angle;
            continue;
        }
        if (p_pos.y < tmp.y && p_pos.x >= tmp.x) {
            data->angles[i].angle += PI;
        } else if (p_pos.y >= tmp.y && p_pos.x >= tmp.x)
            data->angles[i].angle = 2 * PI - data->angles[i].angle;
    }
    radix_sort(data->angles, (size_t [2]){sizeof(dir_t)
    , (data->light->index)}, (size_t)&((dir_t *)0)->angle, data->buffer);
}
