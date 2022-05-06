/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** musics
*/

#include "rpg.h"

void init_musics(game_t *game)
{
    game->rush_music = create_music(RUSH_MUSIC);
    if (game->rush_music)
        sfMusic_setLoop(game->rush_music, 1);
    game->ambient_music = create_music(AMBIENT_MUSIC);
    if (game->ambient_music)
        sfMusic_setLoop(game->rush_music, 1);
    game->sounds[0] = create_sound(LAUGH);
    game->sounds[1] = create_sound(LV_UP);
    game->sounds[2] = create_sound(UPGRADE);
    game->yes = create_sound("assets/audio/yes.ogg");
    game->no = create_sound("assets/audio/no.ogg");
}
