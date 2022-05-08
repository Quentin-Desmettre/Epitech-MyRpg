/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rotate_vector.c
*/

#include <SFML/Graphics.h>
#include "rpg.h"

int are_all_textures_valid(void)
{
    if (!global_texture())
        return !dprint(2, "ERROR: Cannot load 'assets/texture.png'."
        " Exiting program.\n");
    if (!global_font()) {
        sfTexture_destroy(global_texture());
        return !dprint(2, "ERROR: Cannot load 'assets/font.tff'."
        " Exiting program.\n");
    }
    for (int i = 0; all_assets[i]; i++) {
        if (!get_texture_by_name(all_assets[i])) {
            sfFont_destroy(global_font());
            free_textures();
            dprint(2, "ERROR: Cannot load '%s'. Exiting program.\n",
            all_assets[i]);
            return 0;
        }
    }
    return 1;
}

void rotate_vector(sfVector2f *vec, float degree)
{
    sfVector2f new;

    degree = deg_to_rad(degree);
    new.x = cos(degree) * vec->x - sin(degree) * vec->y;
    new.y = sin(degree) * vec->x + cos(degree) * vec->y;
    vec->x = new.x;
    vec->y = new.y;
}

sfVector2i sprite_pos(sfSprite *s)
{
    sfVector2f pos = sfSprite_getPosition(s);

    return (sfVector2i){pos.x, pos.y};
}
