/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** sounds.c
*/

#include "rpg.h"

list_t **sound_list(void)
{
    static list_t *sounds = NULL;

    return &sounds;
}

list_t **music_list(void)
{
    static list_t *musics = NULL;

    return &musics;
}

float music_vol(int change, float new)
{
    static float vol = 100;

    if (change) {
        set_musics_volume(new);
        vol = new;
    }
    return vol;
}

float sound_vol(int change, float new)
{
    static float vol = 100;

    if (change) {
        set_sounds_volume(new);
        vol = new;
    }
    return vol;
}
