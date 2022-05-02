/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/rpg.h"

void change_pos(fight_t *fight)
{
    int randy = 0;

    for (int i = 0; i < 20; i++) {
        randy = 6 + rand() % 6;
        sfRectangleShape_setPosition(fight->solid[i], (sfVector2f){100 * (1 +
        rand() % 12) + 20, 100 * (randy == 6 ? 6 + rand() % 6 : randy)});
    }
    for (int i = 0; i < DMG; i++) {
        do {
            sfRectangleShape_setPosition(fight->dmg[i], (sfVector2f){50 * (2 +
            rand() % 24) + 20, 50 * (1 + rand() % 7)});
        } while (touch_solid(sfRectangleShape_getGlobalBounds(fight->dmg[i]),
        fight));
    }
    sfRectangleShape_setSize(fight->solid[0], (sfVector2f){0, 100});
    sfRectangleShape_setPosition(fight->solid[0], (sfVector2f){700 + 20, 900
    + 20});
    sfRectangleShape_setSize(fight->solid[1], (sfVector2f){1440, 100});
    sfRectangleShape_setPosition(fight->solid[1], (sfVector2f){0, 100 * 10});
    sfRectangleShape_setPosition(fight->player, (sfVector2f){900, 500});
}

void set_blocks(fight_t *fight)
{
    int randy = 0;

    for (int i = 0; i < 20; i++) {
        randy = 6 + rand() % 6;
        fight->solid[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(fight->solid[i], (sfVector2f){200, 100});
        sfRectangleShape_setFillColor(fight->solid[i], sfWhite);
    }
    for (int i = 0; i < DMG; i++) {
        fight->dmg[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(fight->dmg[i], (sfVector2f){50, 50});
        sfRectangleShape_setFillColor(fight->dmg[i], sfRed);
        fight->rand_time[i] = 0;
        fight->time[i] = create_clock();
    }
    fight->circle = sfCircleShape_create();
    sfCircleShape_setRadius(fight->circle, 75);
    sfCircleShape_setOrigin(fight->circle, (sfVector2f){75, 75});
    sfCircleShape_setFillColor(fight->circle, sfColor_fromRGB(254, 159, 5));
    change_pos(fight);
}

fight_t *init_fight(void)
{
    fight_t *fight = malloc(sizeof(fight_t));
    sfFloatRect rect;

    fight->fall = 0;
    fight->tex = sfRenderTexture_create(1920, 1080, 0);
    fight->player = sfRectangleShape_create();
    sfRectangleShape_setSize(fight->player, (sfVector2f){100, 100});
    sfRectangleShape_setFillColor(fight->player, sfGreen);
    set_blocks(fight);
    fight->nme = 100;
    for (int i = 0; i == 0 || touch_solid(rect, fight); i++) {
        sfCircleShape_setPosition(fight->circle, (sfVector2f){120, 100 *
        (9 - i)});
        rect = sfCircleShape_getGlobalBounds(fight->circle);
        rect.height += 100;
        rect.top -= 100;
    }
    fight->speed = create_clock();
    return (fight);
}

void destroy_fight(fight_t *fight)
{
    for (int i = 0; i < 20; i++)
        sfRectangleShape_destroy(fight->solid[i]);
    for (int i = 0; i < DMG; i++) {
        sfRectangleShape_destroy(fight->dmg[i]);
    }
    sfRenderTexture_destroy(fight->tex);
    sfRectangleShape_destroy(fight->player);
    sfCircleShape_destroy(fight->circle);
    free(fight);
}