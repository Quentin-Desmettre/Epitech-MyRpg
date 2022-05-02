/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** pnj.c
*/

#include "inter_npc.h"

sfTexture *dialog_box(void)
{
    static sfTexture *tex = 0;

    if (!tex)
        tex = sfTexture_createFromFile(PNJ_TALK_BOX, NULL);
    return tex;
}

sfTexture *arrow_tex(void)
{
    static sfTexture *tex = 0;

    if (!tex)
        tex = sfTexture_createFromFile(ARROW_PNG, NULL);
    return tex;
}

sfTexture *opt_diag_box(void)
{
    static sfTexture *tex = 0;

    if (!tex)
        tex = sfTexture_createFromFile(OPT_DIALOG, NULL);
    return tex;
}
