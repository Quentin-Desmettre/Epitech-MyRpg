/*
** EPITECH PROJECT, 2019
** project
** File description:
** project
*/

#include "include/my.h"

sfRenderWindow *create_window(char *title, int x, int y)
{
    sfVideoMode video_mode = {x, y, 32};
    sfRenderWindow *window;
    window = sfRenderWindow_create(video_mode, title, sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 30);
    return (window);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    sfRenderWindow *window = create_window("rpg", 1500, 800);
    sfEvent event;

    player_t *p = malloc(sizeof(player_t));

    p->texture = sfTexture_createFromFile("png/pf_persos.png", NULL);
    p->sprite = sfSprite_create();
    sfSprite_setTexture(p->sprite, p->texture, sfFalse);
    p->rect.top = 640;
    p->rect.left = 0;
    p->rect.height = 64;
    p->rect.width = 64;
    sfSprite_setTextureRect(p->sprite, p->rect);
    p->pos.x = 0;
    p->pos.y = 0;
    sfSprite_setPosition(p->sprite, p->pos);
    p->clock_n_walk = sfClock_create();

    p->in_game = 1;
    p->speed = 100;
    p->moral = 100;

    while (sfRenderWindow_isOpen(window))
    {
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
        check_move(p);
        sfRenderWindow_drawSprite(window, p->sprite, NULL);
        while (sfRenderWindow_pollEvent(window, &event) == sfTrue) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }
    }
    return (0);
}