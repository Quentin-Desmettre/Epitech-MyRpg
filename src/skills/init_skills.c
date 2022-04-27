/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** init_skills
*/

#include "rpg.h"
#include "skills.h"
#include "skills_static.h"

void skills_events(game_t *game, sfEvent ev, window_t *win)
{
    sfVector2f size = win_size(win);
    float indent = 244 * (SCALE(size));
    sfFloatRect mouse = {ev.mouseButton.x, ev.mouseButton.y, 1, 1};
    sfFloatRect button = {S_POS_X(size, 0), 333 * size.y / 1080.0,
    118 * (SCALE(size)), 118 * (SCALE(size))};

    for (int i = 0; i < NB_SKILLS; i++) {
        if (sfFloatRect_intersects(&mouse, &button, 0)) {
            game->skills->skill_selected = i;
            return;
        }
        button.left += indent;
    }
}

void scale_draw(game_t *game, sfVector2f scale)
{
    sfSprite_setScale(game->skills->sprite, scale);
    sfSprite_setScale(game->skills->button, scale);
    for (int i = 0; i < NB_SKILLS; i++)
        sfSprite_setScale(game->skills->sk_sprites[i], scale);
}

void create_skill_desc(sfText *text, int item, sfVector2f size)
{
    char *str;
    const char *tmp;
    sfFloatRect pos = sfText_getGlobalBounds(text);
    char **words = my_str_to_word_array(SKILLS_TXT(item), " ");

    sfText_setString(text, "");
    for (int i = 0; words[i]; i++) {
        tmp = sfText_getString(text);
        str = str_concat(3, tmp, words[i], " ");
        sfText_setString(text, str);
        free(str);
        pos = sfText_getGlobalBounds(text);
        if (pos.left + pos.width > 1715 / 1080.0 * size.y) {
            str = str_concat(2, tmp, "\n");
            sfText_setString(text, str);
            free(str);
            i--;
        }
    }
    my_free("P", words);
}

void draw_skill_desc(game_t *game, sfVector2f size, int skill)
{
    sfText *text = init_text(SKILLS_TITLE(skill), size.y / 40);
    sfSprite *sprite = game->skills->sk_sprites[skill];

    sfSprite_setScale(sprite, (sfVector2f)
    {2.5 * SCALE(size), 2.5 * SCALE(size)});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 620 / 1080.0 * size.y, 583 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 + 0 / 1080.0 * size.y, 640 * SCALE(size)});
    center_text(text);
    sfRenderTexture_drawText(game->rtex, text, NULL);
    create_skill_desc(text, skill, size);
    sfText_setCharacterSize(text, size.y / 45);
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 + 0 / 1080.0 * size.y, 690 * SCALE(size)});
    center_text(text);
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    sfText_destroy(text);
}

void draw_skills(game_t *game, window_t *win)
{
    sfVector2f size = win_size(win);
    float indent = 244 * (SCALE(size));

    if (!game->skills->draw)
        return;
    scale_draw(game, (sfVector2f){SCALE(size), SCALE(size)});
    sfSprite_setPosition(game->skills->sprite,
    (sfVector2f){size.x * 0.5, size.y * 0.5});
    sfRenderTexture_drawSprite(game->rtex, game->skills->sprite, NULL);
    sfSprite_setPosition(game->skills->button,
    (sfVector2f){size.x / 2 + 292 / 1080.0 * size.y, size.y * 0.475});
    sfRenderTexture_drawSprite(game->rtex, game->skills->button, NULL);
    for (int i = 0; i < NB_SKILLS; i++) {
        sfSprite_setPosition(game->skills->sk_sprites[i],
        (sfVector2f){S_POS_X(size, indent * i), 333 * size.y / 1080.0});
        sfRenderTexture_drawSprite(game->rtex, game->skills->sk_sprites[i],
        NULL);
    }
    if (game->skills->skill_selected != -1)
        draw_skill_desc(game, size, game->skills->skill_selected);
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
        skills->sk_sprites[i] = sfSprite_create();
        texture = sfTexture_createFromFile(sk_paths[i], NULL);
        sfSprite_setTexture(skills->sk_sprites[i], texture, sfTrue);
    }
    texture = sfTexture_createFromFile(S_BUTTON_PATH, NULL);
    skills->button = sfSprite_create();
    sfSprite_setTexture(skills->button, texture, sfTrue);
    skills->skill_selected = -1;
    return skills;
}
