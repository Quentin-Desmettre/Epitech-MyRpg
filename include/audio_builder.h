/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** audio_builder.h
*/

#ifndef AUDIO_BUILDER_H
    #define AUDIO_BUILDER_H
    #include "libmy.h"
    #include <SFML/Audio.h>

void set_sounds_volume(float volume);
void destroy_sound(sfSound *s);
void destroy_sounds(void);
sfSound *create_sound(char const *source);

void set_musics_volume(float volume);
void destroy_music(sfMusic *s);
void destroy_musics(void);
sfMusic *create_music(char const *source);

list_t **sound_list(void);
list_t **music_list(void);
float music_vol(int change, float new);
float sound_vol(int change, float new);

#endif
