/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** create.c
*/

#include "rpg.h"
#include "main_menu.h"

void main_menu_ev(window_t *win, sfEvent ev)
{
    main_menu_t *m = win->menus[HOME];
    sfVector2f p = (sfVector2f){ev.mouseButton.x, ev.mouseButton.y};

    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(m->buttons, 4, p.x, p.y);
    if (ev.type == sfEvtMouseMoved)
        check_button_move(m->buttons, 4, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_button_release(m->buttons, 4, p, win);
}

void destroy_main_menu(main_menu_t *m)
{
    sfText_destroy(m->main_txt);
    sfSprite_destroy(m->background);
    sfRenderTexture_destroy(m->rtex);
    for (int i = 0; i < 4; i++)
        destroy_button(m->buttons[i]);
    free(m);
}

void rescale_main_menu(main_menu_t *m, sfVector2f win_size)
{
    sfRenderTexture_destroy(m->rtex);
    m->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    for (int i = 0; i < 4; i++) {
        m->buttons[i]->container_size = win_size;
        update_button(m->buttons[i]);
        if (i == 3)
            button_set_pos(m->buttons[i], (sfVector2f){win_size.x * mm_pf[i].x,
            win_size.x * mm_pf[i].x});
        if (i == 2)
            button_set_pos(m->buttons[i], (sfVector2f){win_size.x * mm_pf[i].x,
            win_size.x * mm_pf[i].y});
    }
    set_sprite_size(m->background, win_size);
    sfText_setCharacterSize(m->main_txt, win_size.y / 6);
    sfText_setPosition(m->main_txt,
    (sfVector2f){win_size.x / 2, win_size.y / 4});
    center_text(m->main_txt);
}

main_menu_t *create_main_menu(sfVector2f win_size)
{
    main_menu_t *m = malloc(sizeof(main_menu_t));
    void (*actions[])(void *) = {go_to_local_save, go_to_settings,
    go_to_htp, quit_main_menu};

    m->main_txt = init_text("Backrooms", win_size.y / 6);
    center_text(m->main_txt);
    sfText_setPosition(m->main_txt,
    (sfVector2f){win_size.x / 2, win_size.y / 4});
    m->background = init_sprite(global_texture(), back_rect, win_size);
    for (int i = 0; i < 4; i++)
        m->buttons[i] = build_button("pf,sf,rect,"
        "text,texture,base_size,ff,release,p_sf,r_sf",
        mm_pf[i], mm_sf[i], mm_rects[i], mm_texts[i], global_texture(),
        win_size, mm_ff_factors[i], actions[i], BUTTON_PRESS, BUTTON_RELEASE);
    m->rtex = sfRenderTexture_create(win_size.x, win_size.y, 0);
    return m;
}

const sfTexture *draw_main_menu(window_t *w)
{
    main_menu_t *m = w->menus[HOME];
    game_t *game = w->menus[GAME];
    sfSprite *s;

    anim_npc(game->player);
    sfRenderTexture_clear(m->rtex, sfBlack);
    sfRenderTexture_clear(game->rtex, sfBlack);
    sfRenderTexture_drawSprite(m->rtex, m->background, NULL);
    draw_room(w->menus[LIGHT], w->menus[GAME], w);
    draw_enemies(game, w->menus[LIGHT], w);
    draw_map(w->menus[LIGHT], w->menus[GAME], w);
    sfRenderTexture_display(game->rtex);
    s = init_sprite_from_texture(sfRenderTexture_getTexture(game->rtex));
    sfRenderTexture_drawSprite(m->rtex, s, NULL);
    for (int i = 0; i < 4; i++)
        draw_button_to_rtex(m->buttons[i], m->rtex);
    sfRenderTexture_drawText(m->rtex, m->main_txt, NULL);
    sfRenderTexture_display(m->rtex);
    sfSprite_destroy(s);
    return sfRenderTexture_getTexture(m->rtex);
}
