/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/fight.h"

void set_blocks(fight_t *fight)
{
    int randy = 0;

    for (int i = 0; i < DMG; i++) {
        fight->dmg[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(fight->dmg[i], (sfVector2f){50, 50});
        sfRectangleShape_setFillColor(fight->dmg[i], sfRed);
        fight->rand_time[i] = 0;
        fight->time[i] = sfClock_create();
    }
    for (int i = 0; i < 20; i++) {
        randy = 6 + rand() % 6;
        fight->solid[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(fight->solid[i], (sfVector2f){200, 100});
        sfRectangleShape_setFillColor(fight->solid[i], sfWhite);
        sfRectangleShape_setPosition(fight->solid[i], (sfVector2f){100 * (1 + rand()
        % 18), 100 * (randy == 6 ? 6 + rand() % 6 : randy)});
    }
}

fight_t *init_fight(void)
{
    fight_t *fight = malloc(sizeof(fight_t));

    fight->sprt = sfSprite_create();
    fight->fall = 0;
    fight->tex = sfRenderTexture_create(1920, 1080, 0);
    fight->player = sfRectangleShape_create();
    sfRectangleShape_setSize(fight->player, (sfVector2f){100, 100});
    sfRectangleShape_setFillColor(fight->player, sfGreen);
    sfRectangleShape_setPosition(fight->player, (sfVector2f){900, 500});
    set_blocks(fight);
    sfRectangleShape_setSize(fight->solid[0], (sfVector2f){500, 100});
    sfRectangleShape_setPosition(fight->solid[0], (sfVector2f){100 * (7), 100 * (9)});
    fight->test = 0;
    fight->dir = malloc(sizeof(sfVector2f) * DMG);
    fight->clock_zigzag = sfClock_create();
    fight->clock_square = sfClock_create();
    fight->zz = create_zigzag_pattern();
    fight->square = create_square_pattern();
    return (fight);
}

void destroy_fight(fight_t *fight)
{
    for (int i = 0; i < DMG; i++) {
        sfClock_destroy(fight->time[i]);
        sfRectangleShape_destroy(fight->dmg[i]);
    }
    for (int i = 0; i < 20; i++)
        sfRectangleShape_destroy(fight->solid[i]);
    sfClock_destroy(fight->clock_zigzag);
    sfClock_destroy(fight->clock_square);
    sfSprite_destroy(fight->sprt);
    sfRenderTexture_destroy(fight->tex);
    sfRectangleShape_destroy(fight->player);
    free(fight->dir);
    free(fight);
}