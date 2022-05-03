/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pnj.c
*/

#include "inter_npc.h"

void destroy_texture(void *tex)
{
    texture_t *t = tex;

    free(t->name);
    sfTexture_destroy(t->tex);
    free(t);
}

texture_t *find_texture(char const *name, list_t *list)
{
    list_t *begin = list;
    texture_t *tmp;

    if (!begin)
        return NULL;
    do {
        tmp = list->data;
        if (!my_strcmp(tmp->name, name))
            return tmp;
        list = list->next;
    } while (list != begin);
    return NULL;
}

texture_t *init_texture(char const *name)
{
    sfTexture *tex = sfTexture_createFromFile(name, NULL);
    texture_t *t;

    if (!tex)
        return NULL;
    t = malloc(sizeof(texture_t));
    t->tex = tex;
    t->name = my_strdup(name);
    return t;
}

list_t **textures_list(void)
{
    static list_t *l = NULL;

    return &l;
}

sfTexture *get_texture_by_name(char const *name)
{
    list_t **textures = textures_list();
    texture_t *tmp;

    tmp = find_texture(name, *textures);
    if (tmp)
        return tmp->tex;
    tmp = init_texture(name);
    if (!tmp)
        return NULL;
    append_node(textures, tmp);
    return tmp->tex;
}
