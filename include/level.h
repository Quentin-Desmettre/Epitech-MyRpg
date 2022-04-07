/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** level
*/

#ifndef LEVEL_H_
    #define LEVEL_H_

/// level default texture
    #define DEFAULT_TEXT "assets/texture.png"

/// level complexity
    #define COMPLEXITY 3

/// level sizes
static const sfVector2f BIG = {28, 38};
static const sfVector2f SMALL = {13, 18};

/// level structure
typedef struct level {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f size;
    int depth;
    char *name;
    char **room;
} level_t;

////////////////////////////////////////////////////////////
/// \brief Create an level according to parameters
///
/// \param params The format string. The available parameters are:
/// \param d      depth of the level.
/// \param n      name of the level.
/// \param t      path to the texture to load (LOBBY_TEXT by default).
/// \param s      room size (BIG by default).
///
/// \return A new level_t object, or NULL if it failed.
///
////////////////////////////////////////////////////////////
level_t *level_create(char *params, ...);

/// level setters
void set_level_depth(level_t *level, va_list va);
void set_level_name(level_t *level, va_list va);
void set_level_txt(level_t *level, va_list va);
void set_level_size(level_t *level, va_list va);

/// room builders
void create_room(level_t *level);

/// string of all the parameters
    #define LEVEL_PARAMS "dnts"

#endif
