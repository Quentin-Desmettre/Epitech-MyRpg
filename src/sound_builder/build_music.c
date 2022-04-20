/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** build_music.c
*/

#include "rpg.h"
#ifdef sfMusic_createFromFile
    #undef sfMusic_createFromFile
#endif

void set_musics_volume(float volume)
{
    list_t *list = *music_list();
    list_t *begin = list;

    if (!begin)
        return;
    do {
        sfMusic_setVolume(list->data, volume);
        list = list->next;
    } while (list != begin);
}

void destroy_music(sfMusic *s)
{
    list_t *list = *music_list();
    list_t *begin = list;
    int index = 0;

    if (!begin)
        return;
    do {
        if (list->data == s) {
            sfMusic_destroy(s);
            remove_node(music_list(), index, 0);
            return;
        }
        list = list->next;
        index++;
    } while (list != begin);
}

void destroy_musics(void)
{
    while (*music_list())
        destroy_music((*music_list())->data);
}

sfMusic *create_music(char const *source)
{
    sfMusic *m = sfMusic_createFromFile(source);

    if (!m) {
        dprint(2, "Error: Cannot load file '%s'.\n", source);
        return NULL;
    }
    sfMusic_setVolume(m, get_music_vol());
    append_node(music_list(), m);
    return m;
}
