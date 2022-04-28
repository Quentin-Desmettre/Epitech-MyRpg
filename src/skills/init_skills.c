/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** init_skills
*/

#include "rpg.h"
#include "skills.h"
#include "skills_static.h"

void scale_draw(game_t *game, sfVector2f scale)
{
    sfSprite_setScale(game->skills->sprite, scale);
    sfSprite_setScale(game->skills->button, scale);
    for (int i = 0; i < NB_SKILLS; i++) {
        sfSprite_setScale(game->skills->sk_sprites[i][0], scale);
        sfSprite_setScale(game->skills->sk_sprites[i][1], scale);
    }
}

void skills_events(game_t *game, sfEvent ev, sfVector2f size)
{
    int selected = game->skills->skill_selected;
    sfFloatRect mouse = {ev.mouseButton.x, ev.mouseButton.y, 1, 1};
    sfFloatRect button = {S_POS_X(size, 0), 333 * size.y / 1080.0,
    118 * (SCALE(size)), 118 * (SCALE(size))};

    for (int i = 0; i < NB_SKILLS; i++, button.left += 244 * (SCALE(size)))
        if (sfFloatRect_intersects(&mouse, &button, 0)) {
            game->skills->skill_selected = i;
            return;
        }
    button = sfSprite_getGlobalBounds(game->skills->button);
    if (selected >= 0 && sfFloatRect_intersects(&mouse, &button, 0) &&
    game->skills->data->pc > 1 && game->skills->data->tab[selected] < 2) {
        if (selected != 0 && game->skills->data->tab[selected - 1] == 0)
            return;
        game->skills->data->pc -= 2;
        !game->skills->data->tab[selected] ?
        restart_clock(game->skills->clocks[selected]) : 0;
        game->skills->data->tab[selected]++;
    }
}

void skills_create2(skills_t *skills)
{
    sfTexture *texture = sfTexture_createFromFile(S_BUTTON_PATH, NULL);

    skills->skill_selected = -1;
    skills->button = sfSprite_create();
    sfSprite_setTexture(skills->button, texture, sfTrue);
    skills->rect = sfRectangleShape_create();
    sfRectangleShape_setFillColor(skills->rect, (sfColor){128, 128, 128, 128});
    for (int i = 0; i < NB_SKILLS; i++)
        skills->clocks[i] = create_clock();
}

skills_t *skills_create(void)
{
    sfTexture *texture;
    skills_t *skills = malloc(sizeof(skills_t));

    memset(skills, 0, sizeof(skills_t));
    skills->data = malloc(sizeof(skills_data_t));
    memset(skills->data, 0, sizeof(skills_data_t));
    skills->sprite = sfSprite_create();
    skills->texture = sfTexture_createFromFile(SKILLS_PATH, NULL);
    sfSprite_setTexture(skills->sprite, skills->texture, sfTrue);
    sfSprite_setOrigin(skills->sprite, (sfVector2f){sfTexture_getSize
    (skills->texture).x / 2, sfTexture_getSize(skills->texture).y / 2});
    for (int i = 0; i < NB_SKILLS; i++) {
        skills->sk_sprites[i][0] = sfSprite_create();
        skills->sk_sprites[i][1] = sfSprite_create();
        texture = sfTexture_createFromFile(sk_white_paths[i], NULL);
        sfSprite_setTexture(skills->sk_sprites[i][0], texture, sfTrue);
        texture = sfTexture_createFromFile(sk_paths[i], NULL);
        sfSprite_setTexture(skills->sk_sprites[i][1], texture, sfTrue);
    }
    skills_create2(skills);
    return skills;
}
