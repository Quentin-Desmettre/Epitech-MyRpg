/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** draw2
*/

#include "rpg.h"
#include "inventory.h"

void draw_item(game_t *game, int item, int box, sfVector2f size)
{
    int col = box % 3;
    int line = box / 3;
    float indent = 114 * (SCALE(size));
    sfSprite *sprite = game->inventory->items_sprite[item];
    sfText *text = init_text(nbr_to_str(game->inventory->data->nb_items[box]),
    1080 / 40);

    game->inventory->items_pos[box] = (sfFloatRect){POS_X(size, indent, col),
    POS_Y(size, indent, line), 100 * (SCALE(size)), 100 * (SCALE(size))};
    sfText_setPosition(text, (sfVector2f){877 + 114 * col, 363 + 114 * line});
    sfSprite_setScale(sprite, (sfVector2f){(SCALE(size)), (SCALE(size))});
    sfSprite_setPosition(sprite, (sfVector2f)
    {POS_X(size, indent, col), POS_Y(size, indent, line)});
    sfRenderTexture_drawSprite(game->rtex, sprite, NULL);
    sfRenderTexture_drawText(game->inventory->rtex, text, NULL);
    sfText_destroy(text);
}

void create_desc(sfText *text, int item)
{
    char **words = my_str_to_word_array(ITEM_TXT(item), " ");
    sfFloatRect pos = sfText_getGlobalBounds(text);
    char *str;
    const char *tmp;

    sfText_setString(text, "");
    for (int i = 0; words[i]; i++) {
        tmp = sfText_getString(text);
        str = str_concat(3, tmp, words[i], " ");
        sfText_setString(text, str);
        free(str);
        pos = sfText_getGlobalBounds(text);
        if (pos.left + pos.width > 1715) {
            str = str_concat(2, tmp, "\n");
            sfText_setString(text, str);
            free(str);
            i--;
        }
    }
    my_free("P", words);
}

void draw_item_info(game_t *game, int item, sfVector2u size)
{
    sfText *text = init_text(ITEM_TITLE(item), size.y / 40);
    sfSprite *sprite = game->inventory->items_sprite[item];

    sfSprite_setScale(sprite, (sfVector2f){2.5, 2.5});
    sfSprite_setPosition(sprite, (sfVector2f){1242, 233});
    sfText_setPosition(text, (sfVector2f){1330, 450});
    sfRenderTexture_drawText(game->inventory->rtex, text, NULL);
    create_desc(text, item);
    sfText_setCharacterSize(text, size.y / 45);
    sfText_setPosition(text, (sfVector2f){1200, 500});
    sfRenderTexture_drawText(game->inventory->rtex, text, NULL);
    sfRenderTexture_drawSprite(game->inventory->rtex, sprite, NULL);
    sfText_destroy(text);
}
