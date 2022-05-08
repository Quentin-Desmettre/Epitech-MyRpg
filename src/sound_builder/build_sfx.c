/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** build_sfx.c
*/

#include "rpg.h"

void set_sounds_volume(float volume)
{
    list_t *list = *sound_list();
    list_t *begin = list;

    if (!begin)
        return;
    do {
        sfSound_setVolume(list->data, volume);
        list = list->next;
    } while (list != begin);
}

void destroy_sound(sfSound *s)
{
    list_t *list = *sound_list();
    list_t *begin = list;
    int index = 0;

    if (!begin)
        return;
    do {
        if (list->data == s) {
            sfSoundBuffer_destroy(
            (sfSoundBuffer *)sfSound_getBuffer(list->data));
            sfSound_destroy(list->data);
            remove_node(sound_list(), index, NULL);
            return;
        }
        list = list->next;
        index++;
    } while (list != begin);
}

void destroy_sounds(void)
{
    while (*sound_list())
        destroy_sound((*sound_list())->data);
}

sfSound *create_sound(char const *source)
{
    sfSound *sound = sfSound_create();
    sfSoundBuffer *buf = sfSoundBuffer_createFromFile(source);

    if (!buf) {
        sfSound_destroy(sound);
        return NULL;
    }
    sfSound_setBuffer(sound, buf);
    sfSound_setVolume(sound, get_sound_vol());
    append_node(sound_list(), sound);
    return sound;
}
