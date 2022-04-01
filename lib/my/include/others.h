/*
** EPITECH PROJECT, 2021
** others
** File description:
** header for others functions
*/

#ifndef INCLUDE_OTHERS_H
    #define INCLUDE_OTHERS_H

void my_sort_int_array(int *array, int size);
int my_sort_word_array(char **tab);
void my_int_swap(int *a, int *b);
void my_char_swap(char *a, char *b);
////////////////////////////////////////////////////////////
/// \brief Allows to frre multiple pointers at a time
///
/// \param to_free string to identify the type of pointer
///                ('p' for simple pointer and 'P' for double pointer).
///                For example:
///                "ppP" for two simple pointers and one double pointer.
///
/// \return void
///
////////////////////////////////////////////////////////////
void my_free(char *to_free, ...);

#endif
