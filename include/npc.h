/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** npc
*/

#ifndef NPC_H_
    #define NPC_H_

/// npc diretions
    #define LEFT 0
    #define UP 1
    #define RIGHT 2
    #define DOWN 3
    #define IDLE 4

/// npc structure
typedef struct npc {
    sfSprite *sprite;
    sfTexture *texture;
    int *nb_frames;
    sfIntRect **rects;
    int dir;
    int group;
    int frame;
    int thirst;
    int attack;
    int defense;
    int speed;
    int nb_rects;
    int level;
    int xp;
    int xp_limit;
    sfVector2f pos;
    sfVector2f scale;
    p_clock_t *move_clock;
    p_clock_t *anim_clock;
} npc_t;

////////////////////////////////////////////////////////////
/// \brief Create an npc according to parameters
///
/// \param params The format string. The available parameters are:
/// \param t      path to the texture to load.
/// \param n      array of ints for the frame number in each direction
///               (left, top, right, bottom, idle, ...).
///               Must be before the i argument!
/// \param i      array of sfIntRects for each direction
///               (left, top, right, bottom, idle, ...).
/// \param d      initial direction (optional, RIGHT by default).
/// \param g      group of the npc (optional, 0 by default).
/// \param s      starting frame (optional, 0 by default).
/// \param h      thirst of the npc (optional, 100 by default)
/// \param a      attack of the npc (optional, 10 by default)
/// \param f      defense of the npc (optional, 10 by default)
/// \param v      speed of the npc (optional, 10 by default)
/// \param p      position of the npc (optional, {0, 0} by default)
/// \param c      scale of the npc (optional, {1, 1} by default)
/// \param l      level of the npc (optional, 1 by default)
/// \param x      xp of the npc (optional, 0 by default)
///
/// \return A new npc_t object, or NULL if it failed.
///
////////////////////////////////////////////////////////////
npc_t *npc_create(char *params, ...);

/// npc setters
void set_npc_txt(npc_t *npc, va_list va);
void set_npc_frames(npc_t *npc, va_list va);
void set_npc_rects(npc_t *npc, va_list va);
void set_npc_dir(npc_t *npc, va_list va);
void set_npc_grp(npc_t *npc, va_list va);
void set_npc_initframe(npc_t *npc, va_list va);
void set_npc_atk(npc_t *npc, va_list va);
void set_npc_def(npc_t *npc, va_list va);
void set_npc_spd(npc_t *npc, va_list va);
void set_npc_health(npc_t *npc, va_list va);
void set_npc_pos(npc_t *npc, va_list va);
void set_npc_scale(npc_t *npc, va_list va);
void set_npc_level(npc_t *npc, va_list va);
void set_npc_xp(npc_t *npc, va_list va);

/// string of all the parameters
    #define NPC_PARAMS "tnidgshafvpc"

#endif
