/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** inventory
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_

    #include "rpg.h"

// inventory infos
    #define INVENTORY_SIZE 12
    #define STACK_SIZE 5
    #define INVENTORY_PATH "assets/inventory/inventory.png"

// number of items
    #define NB_ITEMS 2
// list of differents items
    #define WATER 0
    #define PILLS 1

// invetory_data structure
typedef struct inventory_data {
    int items[INVENTORY_SIZE];
    int nb_items[INVENTORY_SIZE];
    int size;
} inventory_data_t;

// invetory structure
typedef struct inventory {
    inventory_data_t *data;
    sfTexture *texture;
    sfSprite *items_sprite[NB_ITEMS];
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect rect;
    int draw;
} inventory_t;

// prototypes
inventory_t *inventory_create(void);
void add_item(inventory_t *inventory, int item, int nb);
void remove_item(inventory_t *inventory, int item, int nb);

#endif
