/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw
*/

#include "rpg.h"

void create_skill_desc(sfText *text, int item, sfVector2f size)
{
    char *str;
    const char *tmp;
    sfFloatRect pos = sfText_getGlobalBounds(text);
    char **words = my_str_to_word_array(skills_txt(item), " ");

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
    sfText *text = init_text(skills_title(skill), size.y / 40);
    sfSprite *sprite = game->skills->sk_sprites[skill][1];

    sfSprite_setScale(sprite, (sfVector2f)
    {2.5 * SCALE(size), 2.5 * SCALE(size)});
    sfSprite_setPosition(sprite, (sfVector2f)
    {size.x / 2 - 600 / 1080.0 * size.y, 583 * SCALE(size)});
    sfText_setPosition(text, (sfVector2f){size.x / 2, 640 * SCALE(size)});
    center_text(text);
    sfRenderTexture_drawText(game->rtex, text, NULL);
    create_skill_desc(text, skill, size);
    sfText_setCharacterSize(text, size.y / 45);
    sfText_setPosition(text, (sfVector2f){size.x / 2, 690 * SCALE(size)});
    center_text(text);
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    sfText_destroy(text);
}

void draw_points(game_t *game, sfVector2f size, int indent)
{
    char *str;
    sfText *text = init_text("", size.y / 30);

    for (int i = 0; i < NB_SKILLS; i++) {
        str = nbr_to_str(game->skills->data->tab[i]);
        sftext_set_string_malloc(text, str_concat(2, "level ", str));
        free(str);
        sfText_setPosition(text, (sfVector2f)
        {S_POS_X(size, indent * i), 452 * SCALE(size)});
        sfRenderTexture_drawText(game->rtex, text, NULL);
    }
    str = nbr_to_str(game->skills->data->pc);
    sfText_setCharacterSize(text, size.y / 20);
    sftext_set_string_malloc(text, str_concat(2, "Points\nleft : ", str));
    free(str);
    sfText_setPosition(text, (sfVector2f)
    {S_POS_X(size, indent * 3.3), 292 * SCALE(size)});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfText_destroy(text);
}

void draw_skills2(game_t *game, sfVector2f size, int indent)
{
    sfText *text = init_text("Upgrade (-2 pts)", size.y / 35);
    int unlocked = 0;

    for (int i = 0; i < NB_SKILLS; i++) {
        unlocked = game->skills->data->tab[i] != 0;
        sfRectangleShape_setPosition(game->skills->rect,
        (sfVector2f){S_POS_X(size, indent * i), 333 * size.y / 1080.0});
        sfSprite_setPosition(game->skills->sk_sprites[i][unlocked],
        (sfVector2f){S_POS_X(size, indent * i), 333 * size.y / 1080.0});
        sfRenderTexture_drawSprite(game->rtex,
        game->skills->sk_sprites[i][unlocked], 0);
        game->skills->skill_selected != i ? sfRenderTexture_drawRectangleShape
        (game->rtex, game->skills->rect, 0) : 0;
    }
    sfText_setPosition(text, (sfVector2f)
    {size.x / 2 + 325 / 1080.0 * size.y, 530 * SCALE(size)});
    sfRenderTexture_drawText(game->rtex, text, NULL);
    sfText_destroy(text);
    if (game->skills->skill_selected != -1)
        draw_skill_desc(game, size, game->skills->skill_selected);
}

void draw_skills(game_t *game, window_t *win)
{
    sfVector2f size = win_size(win);
    float indent = 244 * (SCALE(size));
    float s = 118 * SCALE(size);

    if (!game->skills->draw)
        return;
    scale_draw(game, (sfVector2f){SCALE(size), SCALE(size)});
    sfSprite_setPosition(game->skills->sprite,
    (sfVector2f){size.x / 2, size.y / 2});
    sfRenderTexture_drawSprite(game->rtex, game->skills->sprite, NULL);
    sfSprite_setPosition(game->skills->button,
    (sfVector2f){size.x / 2 + 292 / 1080.0 * size.y, size.y * 0.475});
    sfRenderTexture_drawSprite(game->rtex, game->skills->button, NULL);
    sfRectangleShape_setSize(game->skills->rect, (sfVector2f){s, s});
    draw_skills2(game, size, indent);
    draw_points(game, size, indent);
}
