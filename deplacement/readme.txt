je t'ai tout envoyer comme ça si jamais tu veux tester

structure pour le player que j'ai utilisé:

typedef struct player_s {
    int sprint;
    int normal_walk;
    int slow_walk;
    sfClock *clock_n_walk;
    sfTime time_n_walk;
    float seconds_n_walk;
    int speed;
    int moral;
    int in_game;
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfVector2f pos;
} player_t;