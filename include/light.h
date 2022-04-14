/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** my.h
*/

#ifndef STRUCT_
    #define STRUCT_
    #include <unistd.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <math.h>
    #include <time.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>
    #include "rpg.h"
    #include "npc.h"
    #include "lobby.h"
    #define W_ 1920
    #define CONST 0b10000000
    #define H_ 1080
    #define _A 255
    #define PI 3.14159265359
    #define _SIZE 60.0
    #define MAP_S 40
    #define MAP_W 40
    #define MAP_H 30
    #define _UNDER(x, max) x >= 0 && x < max

typedef struct back {
} back;

typedef struct light_t {
    sfVertex vertex;
    sfVertexArray *array;
    sfCircleShape *circle;
    int index;
} light_t;

typedef struct dir_t {
    float angle;
    sfVector2f coo;
    int is_triple;
} dir_t;

typedef sfVector2f coo_t;

typedef struct all_t {
    int offset;
    dir_t *angles;
    dir_t *buffer;
    float cell;
    light_t *light;
    sfRenderWindow *win;
    sfRenderTexture *tex_light;
    sfImage *img_rpg;
    sfTexture *wall_tex;
    sfTexture *noise;
    sfTexture *floor_tex;
    sfSprite *noise_sp;
    sfSprite *wall;
    sfSprite *floor;
    char **map;
    sfRenderStates state;
} all_t;

int set_game_light(all_t *new, game_t *map);

void radix_sort(void *toSort2, size_t sizes[2],
size_t offset_in_struct, void *buffer2);

void add_light(all_t *data, sfVector2i pos, float intens, sfRenderWindow *win);

void my_memcpy(void *dest, const void *src, size_t n);

int my_memcmp(void *aa, void *bb, size_t size);

coo_t rotate(coo_t center, coo_t rt, float angle);

void draw_map(all_t *data, game_t *game, sfRenderWindow *win);

coo_t norm(coo_t vector);
coo_t rotate(coo_t center, coo_t rt, float angle);
void lunch_lines(all_t *data, coo_t p_pos, float intens);
void sort_angle(all_t *data, coo_t p_pos);
void find_wall(all_t *data, coo_t p_pos, coo_t p_dir, float intens);
void dest_light(all_t *data);
void find_angle_n(int i, int j, int l, all_t *data);
void find_angles(int i, int j, all_t *data);
void wall_light(all_t *data);

#endif
