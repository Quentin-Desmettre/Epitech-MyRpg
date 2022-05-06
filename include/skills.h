/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** skills
*/

#ifndef SKILLS_H_
    #define SKILLS_H_

    #include "rpg.h"
    #include "my_clock.h"

// list of differents skills paths
    #define SKILLS_PATH "assets/skills/skills.png"
    #define S_BUTTON_PATH "assets/skills/skills_button.png"

// skills infos
    #define NB_SKILLS 3
    #define LOCKED 0
    #define LEVEL_1 1
    #define LEVEL_2 2

// list of differents skills
    #define SPRINT 0
    #define CRY 1
    #define FIND_EXIT 2

// macro for skills
    #define S_POS_X(size, i) ((size).x / 2 - (452 / 1080.0 * (size).y)) + (i)
    #define S_TIME(game) get_elapsed_time((game)->skills->clocks[SPRINT])
    #define C_TIME(game) get_elapsed_time((game)->skills->clocks[CRY])
    #define F_TIME(game) get_elapsed_time((game)->skills->clocks[FIND_EXIT])
    #define F_WAIT(level) ((level) == 2 ? 60 : 90)
    #define SEC * 1000000

// descriptions of the diffetents skills
    #define SKILLS_DESC "You are able to sprint for 5 seconds.\n\
Use this skill with the L-Shift key."
    #define CRY_DESC "You can create a puddle by crying \n\
to afraid monsters. Be carefull you lose\n\
hydratation while crying. Use with the C key"
    #define FIND_EXIT_DESC "You can know if the exit is in this room\n\
Use this skill with the F key"

// skills_data structure
typedef struct skills_data {
    int tab[NB_SKILLS];
    int pc;
    int xp;
} skills_data_t;

// skills structure
typedef struct skills {
    skills_data_t *data;
    sfSprite *sk_sprites[NB_SKILLS][2];
    sfRectangleShape *rect;
    sfTexture *texture;
    sfSprite *sprite;
    sfSprite *button;
    sfVector2f pos;
    p_clock_t *clocks[NB_SKILLS];
    int skill_selected;
    int sprint;
    int draw;
} skills_t;

// skills prototypes
skills_t *skills_create(void);

// getters of the skills descriptions
static inline char const *skills_title(int skills)
{
    if (skills == SPRINT)
        return "Sprint";
    else if (skills == CRY)
        return "Cry";
    return "Find Exit";
}

static inline char const *skills_txt(int skills)
{
    if (skills == SPRINT)
        return SKILLS_DESC;
    else if (skills == CRY)
        return CRY_DESC;
    return FIND_EXIT_DESC;
}

#endif
