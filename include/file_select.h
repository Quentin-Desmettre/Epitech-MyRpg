/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** file_select.h
*/

#ifndef FILE_SELECT_H
    #define FILE_SELECT_H

void delete_selected(void *win);
void launch_create_file(void *win);
void launch_file(void *win);

static inline void go_back_to_main(void *win)
{
    set_next_win_state(win, HOME);
}

char const *texts[] = {
    "Cancel", "Delete", "Create", "Play"
};

void (*functions[4])(void *) = {
    go_back_to_main,
    delete_selected,
    launch_create_file,
    launch_file
};

char *files[3] = {
    "saves/save1",
    "saves/save2",
    "saves/save3"
};

#endif
