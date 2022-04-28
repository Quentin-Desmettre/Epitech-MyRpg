/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** main.c
*/

#include "../include/fight.h"

void inverse_pattern(int *pattern, int size)
{
    int *inverse = malloc(sizeof(int) * size);
    int index = 0;
    for (int i = (size - 1); i >= 0; i--) {
        inverse[index] = pattern[i];
        index++;
    }
    for (int i = 0; i < size; i++) {
        pattern[i] = inverse[i];
    }
    free(inverse);
}

int *create_square_pattern(void)
{
    int *square = malloc(sizeof(int) * 13);
    square[0] = 0;
    square[1] = 1;
    square[2] = 0;
    square[3] = 0;
    square[4] = 1;
    square[5] = 0;
    square[6] = 0;
    square[7] = 1;
    square[8] = 0;
    square[9] = 0;
    square[10] = 1;
    square[11] = 0;
    square[12] = 0;
    return (square);
}

// void pattern_square(fight_t *fight, int start)
// {
//     // int square[13] = {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0};
//     sfTime time_square = sfClock_getElapsedTime(fight->clock_square);
//     float seconds = time_square.microseconds / 1000000.0;
//     static int count = 0;
//     for (int i = start; i < 20; i++) {
//         int save_x = fight->x[i];
//         int save_y = fight->y[i];
//         if (seconds > 0.5) {
//             sfClock_restart(fight->clock_square);
//             int move = fight->square[count % 13];
//             if (move == 1) {
//                 fight->y[i] = -save_x;
//                 fight->x[i] = save_y;
//             }
//             count++;
//         }
//     }
// }

int *create_zigzag_pattern(void)
{
    int *zz = malloc(sizeof(int) * 8);
    zz[0] = 0;
    zz[1] = 1;
    zz[2] = 0;
    zz[3] = 2;
    zz[4] = 0;
    zz[5] = 2;
    zz[6] = 0;
    zz[7] = 1;
    return (zz);
}

// void pattern_zigzag(fight_t *fight, int start)
// {
//     // int zz[8] = {0, 1, 0, 2, 0, 2, 0, 1};
//     sfTime time_zigzag = sfClock_getElapsedTime(fight->clock_zigzag);
//     float seconds = time_zigzag.microseconds / 1000000.0;
//     static int count;
//     for (int i = start; i < 20; i++) {
//         int save_x = fight->x[i];
//         int save_y = fight->y[i];
//         if (seconds > 0.3) {
//             sfClock_restart(fight->clock_zigzag);
//             int move = fight->zz[count % 8];
//             if (move == 1) {
//                 fight->y[i] = -save_x;
//                 fight->x[i] = save_y;
//             }
//             if (move == 2) {
//                 fight->y[i] = save_x;
//                 fight->x[i] = -save_y;
//             }
//             count++;
//         }
//     }
// }
