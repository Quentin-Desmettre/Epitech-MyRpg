/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create_inventory
*/

#include "rpg.h"
#include "inventory.h"
#include "inventory_static.h"

void sort_inventory(inventory_t *inventory)
{
    for (int i = 1; i < 12; i++) {
        if (inventory->data->items[i] > -1 &&
        inventory->data->items[i - 1] < 0) {
            inventory->data->items[i - 1] = inventory->data->items[i];
            inventory->data->nb_items[i - 1] = inventory->data->nb_items[i];
            inventory->data->items[i] = -1;
            inventory->data->nb_items[i] = 0;
            i = 0;
        }
    }
}

void remove_item(inventory_t *inventory, int item, int nb)
{
    for (int i = 11; i >= 0; i--) {
        if (inventory->data->items[i] == item) {
            inventory->data->nb_items[i] -= nb;
            inventory->data->nb_items[i] < 0 ?
            inventory->data->nb_items[i] = 0 : 0;
            !inventory->data->nb_items[i] ? inventory->data->items[i] = -1 : 0;
            if (!inventory->data->nb_items[i]) {
                sort_inventory(inventory);
                inventory->item_selected = -1;
            }
            return;
        }
    }
}

void add_item(inventory_t *inventory, int item, int nb)
{
    for (int i = 0; i < 12; i++) {
        if (inventory->data->items[i] == item &&
        inventory->data->nb_items[i] < STACK_SIZE) {
            inventory->data->nb_items[i] += nb;
            return;
        }
    }
    for (int i = 0; i < 12; i++) {
        if (inventory->data->items[i] == -1) {
            inventory->data->items[i] = item;
            inventory->data->nb_items[i] = nb;
            return;
        }
    }
}

void items_create(inventory_t *inventory)
{
    sfTexture *texture;

    for (int i = 0; i < NB_ITEMS; i++) {
        inventory->items_sprite[i] = sfSprite_create();
        texture = sfTexture_createFromFile(items_paths[i], NULL);
        sfSprite_setTexture(inventory->items_sprite[i], texture, sfTrue);
    }
    inventory->rtex = sfRenderTexture_create(1920, 1080, 0);
    texture = sfTexture_createFromFile(I_BUTTON_PATH, NULL);
    inventory->buttons[0] = sfSprite_create();
    inventory->buttons[1] = sfSprite_create();
    sfSprite_setTexture(inventory->buttons[0], texture, sfTrue);
    sfSprite_setTexture(inventory->buttons[1], texture, sfTrue);
}

inventory_t *inventory_create(void)
{
    sfVector2u size;
    inventory_t *inventory = malloc(sizeof(inventory_t));

    memset(inventory, 0, sizeof(inventory_t));
    inventory->data = malloc(sizeof(inventory_data_t));
    memset(inventory->data, 0, sizeof(inventory_data_t));
    memset(inventory->data->items, -1, sizeof(int) * INVENTORY_SIZE);
    memset(inventory->data->nb_items, 0, sizeof(int) * INVENTORY_SIZE);
    inventory->sprite = sfSprite_create();
    inventory->texture = sfTexture_createFromFile(INVENTORY_PATH, NULL);
    sfSprite_setTexture(inventory->sprite, inventory->texture, sfTrue);
    size = sfTexture_getSize(inventory->texture);
    inventory->rect.left = inventory->pos.x;
    inventory->rect.top = inventory->pos.y;
    inventory->rect.width = size.x;
    inventory->rect.height = size.y;
    inventory->item_selected = -1;
    items_create(inventory);
    return inventory;
}
