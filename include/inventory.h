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
    #define I_BUTTON_PATH "assets/inventory/button.png"

// number of items
    #define NB_ITEMS 2
// list of differents items
    #define WATER 0
    #define PILLS 1
// descriptions of the diffetents items
    #define WATER_DESC "Use this item to hydrate you.\n\
Each use will restore 40% of your thirst."
    #define PILLS_DESC "Use this item to heal yourself.\n\
Each use will restore 40% of your health."
// getters of the items descriptions
    #define ITEM_TITLE(item) (item) ? "Pills" : "Water"
    #define ITEM_TXT(item) (item) ? PILLS_DESC : WATER_DESC
    #define SCALE(size) (size).y / 1080.0
    #define POS_X(size, i, nb) ((size).x / 2 - (162 / 1080.0 * \
(size).y)) + i * (nb)
    #define POS_Y(size, i, nb) ((size).y / 2 - (246 / 1080.0 * \
(size).y)) + i * (nb)

// inventory_data structure
typedef struct inventory_data {
    int items[INVENTORY_SIZE];
    int nb_items[INVENTORY_SIZE];
    int size;
} inventory_data_t;

// inventory structure
typedef struct inventory {
    inventory_data_t *data;
    sfRenderTexture *rtex;
    sfTexture *texture;
    sfSprite *items_sprite[NB_ITEMS + 1];
    button_t *stat_btns[4];
    sfSprite *buttons[2];
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect rect;
    sfFloatRect items_pos[INVENTORY_SIZE];
    int item_selected;
    int draw;
} inventory_t;

// prototypes
inventory_t *inventory_create(void);
void add_item(inventory_t *inventory, int item, int nb);
void remove_item(inventory_t *inventory, int item, int nb);
void destroy_inventory(inventory_t *inventory);

#endif
