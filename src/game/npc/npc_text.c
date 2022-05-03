/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc_text.c
*/

#include "rpg.h"
#include "npc_texts.h"

static sfFloatRect get_new_string_bounds(char const **tmp, sfText *text,
char **str, char *words_i)
{
    *tmp = sfText_getString(text);
    *str = str_concat(3, *tmp, words_i, " ");
    sfText_setString(text, *str);
    free(*str);
    return sfText_getGlobalBounds(text);
}

static char *get_split_string(sfText *text, char const *full_str, float max)
{
    char **words = my_str_to_word_array(full_str, " ");
    sfFloatRect pos;
    char *str;
    const char *tmp;
    char *base = my_strdup(sfText_getString(text));

    sfText_setString(text, "");
    for (int i = 0; words[i]; i++) {
        pos = get_new_string_bounds(&tmp, text, &str, words[i]);
        if (pos.left + pos.width > max) {
            str = str_concat(2, tmp, "\n");
            sfText_setString(text, str);
            free(str);
            i--;
        }
    }
    my_free("P", words);
    str = my_strdup(sfText_getString(text));
    sftext_set_string_malloc(text, base);
    return str;
}

void set_current_string(sfText *text, char **words, int index)
{
    char *string;

    if (words[index + 1] && words[index + 2])
        string = str_concat(5, words[index], "\n",
        words[index + 1], "\n", words[index + 2]);
    else if (words[index + 1])
        string = str_concat(3, words[index], "\n", words[index + 1]);
    else
        string = my_strdup(words[index]);

    sfText_setString(text, string);
    free(string);
}

void set_string(interactive_npc_t *i, char const *dialog)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(i->dialog_box);
    float max = bounds.left + bounds.width * 0.94;
    char *split = get_split_string(i->current_dialog, dialog, max);
    char **words = my_str_to_word_array(split, "\n");

    free(split);
    if (i->dialog)
        free_str_array(i->dialog, 1);
    i->dialog = words;
    i->cur_diag_i = 0;
    set_current_string(i->current_dialog, words, 0);
}
