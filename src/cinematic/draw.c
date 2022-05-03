/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw
*/

#include "rpg.h"

void cine_flash(cinematic_t *cine)
{
    if (get_elapsed_time(cine->clock) > 0.1 SEC) {
        sfRectangleShape_setFillColor(cine->rect, (sfColor){255, 0, 0, 64});
        sfRectangleShape_setSize(cine->rect, (sfVector2f){1920, 1080});
        sfRenderTexture_drawRectangleShape(cine->rtex, cine->rect, 0);
    } else
        sfRectangleShape_setFillColor(cine->rect, sfTransparent);
    if (get_elapsed_time(cine->clock) > 0.2 SEC) {
        cine->nb_flash--;
        restart_clock(cine->clock);
    }
}

void update_cine_sprites(window_t *win, float size)
{
    cinematic_t *cine = win->menus[CINE];
    float t = sfSprite_getGlobalBounds(cine->npc[0]->sprite).top;

    sfRenderTexture_clear(cine->rtex, sfBlack);
    sfSprite_setTextureRect(cine->npc[0]->sprite,
    cine->npc[0]->rects[cine->npc[0]->dir][cine->npc[0]->frame]);
    sfSprite_setTextureRect(cine->npc[1]->sprite,
    cine->npc[1]->rects[cine->npc[1]->dir][cine->npc[1]->frame]);
    sfSprite_setScale(cine->npc[0]->sprite, (sfVector2f)
    {1.2 * size, 1.2 * size});
    sfSprite_setScale(cine->npc[1]->sprite, (sfVector2f)
    {1.2 * size, 1.2 * size});
    if (cine->player_state != 5)
        sfSprite_setPosition(cine->npc[1]->sprite,
        (sfVector2f){100 * size, 500 * size});
    if (cine->player_state == 0)
        sfSprite_setPosition(cine->npc[0]->sprite, (sfVector2f){250 * size, t});
    sfSprite_setScale(cine->wall, (sfVector2f){size, 0.5 * size});
}

const sfTexture *draw_cinematic(window_t *win)
{
    cinematic_t *cine = win->menus[CINE];
    float cell = win_size(win).y / (17.0);
    sfSprite *sprite;
    int floor;

    update_cine_sprites(win, SCALE(win_size(win)));
    for (int i = 8; i > 5; i--) {
        for (int j = cine->level->size.y; j >= 0; j--) {
            floor = cine->level->room[i][j] == '*';
            sprite = floor ? cine->floor : cine->wall;
            sfSprite_setPosition(sprite, (sfVector2f)
            {j * cell, (i + !floor) * cell + cell / (2 + !floor)});
            sfRenderTexture_drawSprite(cine->rtex, sprite, 0);
        }
    }
    sfRenderTexture_drawSprite(cine->rtex, cine->npc[0]->sprite, 0);
    sfRenderTexture_drawSprite(cine->rtex, cine->npc[1]->sprite, 0);
    anim_cine(cine, win, SCALE(win_size(win)));
    sfRenderTexture_display(cine->rtex);
    return sfRenderTexture_getTexture(cine->rtex);
}
