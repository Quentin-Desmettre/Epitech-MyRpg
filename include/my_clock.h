/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** my_clock.h
*/

#ifndef MY_CLOCK_H
    #define MY_CLOCK_H
    #include <SFML/System.h>

typedef struct {
    sfClock *clock;
    sfInt64 elapsed;
    sfBool is_paused;
} p_clock_t;

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a pausable clock.
/// \return Returns the constructed clock.
///////////////////////////////////////////////////////////////////////////////
p_clock_t *p_clock_create(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Get the value of the clock, int microseconds.
///////////////////////////////////////////////////////////////////////////////
sfInt64 get_elapsed_time(p_clock_t *clock);

///////////////////////////////////////////////////////////////////////////////
/// \brief Get if the clock is paused.
///////////////////////////////////////////////////////////////////////////////
sfBool clock_is_paused(p_clock_t *clock);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy a clock.
///////////////////////////////////////////////////////////////////////////////
void clock_destroy(p_clock_t *clock);

///////////////////////////////////////////////////////////////////////////////
/// \brief Pause a clock. If it is already paused, does nothing.
///////////////////////////////////////////////////////////////////////////////
void pause_clock(p_clock_t *clock);

///////////////////////////////////////////////////////////////////////////////
/// \brief Resume a clock. If it is not paused, does nothing.
///////////////////////////////////////////////////////////////////////////////
void resume_clock(p_clock_t *clock);

///////////////////////////////////////////////////////////////////////////////
/// \brief Restart a clock. If it is paused, it still start clock.
///////////////////////////////////////////////////////////////////////////////
void restart_clock(p_clock_t *clock);

void resume_clocks(void);
void pause_clocks(void);
p_clock_t *create_clock(void);
void destroy_clock(p_clock_t *p);

#endif
