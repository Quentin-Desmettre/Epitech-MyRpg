/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** can_rush.c
*/

#include "rpg.h"

static sfVector2f *is_intersect(sfVector2f p0, sfVector2f p1,
sfVector2f p2, sfVector2f p3)
{
    float s1_x = p1.x - p0.x;
    float s1_y = p1.y - p0.y;
    float s2_x = p3.x - p2.x;
    float s2_y = p3.y - p2.y;
    float s;
    float t;
    float divisor;

    divisor = (-s2_x * s1_y + s1_x * s2_y);
    if (divisor == 0)
        return NULL;
    s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / divisor;
    t = ( s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / divisor;
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        return alloc_v2f(p0.y + (t * s1_y), p0.y + (t * s1_y));
    return NULL;
}

static sfVector2f *can_reach_player(sfVector2f e_pos,
sfVector2f vector, npc_t *player)
{
    sfFloatRect bounds = get_npc_hitbox(player);
    sfVector2f a0 = e_pos;
    sfVector2f a1 = {e_pos.x + vector.x, e_pos.y + vector.y};
    sfVector2f b0[2] = {
        {bounds.left, bounds.top},
        {bounds.left + bounds.width, bounds.top + bounds.height}
    };
    sfVector2f b1[2] = {
        {bounds.left, bounds.top + bounds.height},
        {bounds.left + bounds.width, bounds.top}
    };
    sfVector2f *inter;

    if ((inter = is_intersect(a0, a1, b0[0], b1[1])) ||
        (inter = is_intersect(a0, a1, b0[0], b1[0])) ||
        (inter = is_intersect(a0, a1, b0[1], b1[0])) ||
        (inter = is_intersect(a0, a1, b0[1], b1[1])))
        return inter;
    return NULL;
}

static sfVector2f get_vision_vector(float const vis_dist, int const dir)
{
    sfVector2f vision = {0, 0};

    if (dir == LEFT)
        vision.x = -vis_dist;
    if (dir == RIGHT)
        vision.x = vis_dist;
    if (dir == UP)
        vision.y = -vis_dist;
    if (dir == DOWN || dir == IDLE)
        vision.y = vis_dist;
    rotate_vector(&vision, -VISION_ANGLE / 2.0);
    return vision;
}

static int has_path_to_player(enemy_t *e, game_t *game,
ray_c *data, window_t *win)
{
    sfVector2f vector;

    if (win->state != GAME)
        return 0;
    vector = vector_to_objective(e, game, data, win_size(win));
    return vector.x || vector.y;
}

int can_rush(enemy_t *e, ray_c *data, npc_t *player, window_t *win)
{
    float const vision_distance = data->cell * 2.5;
    float const increment = VISION_ANGLE / NB_RAY;
    sfVector2f e_pos = sfSprite_getPosition(e->enemy->sprite);
    sfVector2f vector = get_vision_vector(vision_distance, e->enemy->dir);
    sfVector2f *inter;

    for (int i = 0; i < NB_RAY; i++) {
        if ((inter = can_reach_player(e_pos, vector, player))) {
            free(inter);
            return has_path_to_player(e, win->menus[GAME], data, win);
        }
        rotate_vector(&vector, increment);
    }
    return 0;
}
