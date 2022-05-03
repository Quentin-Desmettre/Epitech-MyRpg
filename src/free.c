/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** free.c
*/

#include "rpg.h"

void free_textures(void)
{
    while (*textures_list())
        remove_node(textures_list(), 0, destroy_texture);
    sfTexture_destroy(global_texture());
}
