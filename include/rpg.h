/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rpg.h
*/

#ifndef RPG_H
    #define RPG_H
    #include <string.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include "my_clock.h"
    #include "settings.h"
    #include "sprite.h"
    #include "level.h"
    #include "room.h"
    #include "game.h"
    #include "light.h"
    #include "fight.h"
    #include "npc.h"
    #include "quest.h"
    #include "particles.h"
    #include "inter_npc.h"

    #ifdef DEBUG

        #define sfMusic_createFromFile music_func
        #define sfSound_create sound_func

    sfSound *sound_func(void);
    sfMusic *music_func(char *s);

    #endif
    #define get_music_vol() music_vol(0, 0)
    #define set_music_vol(x) music_vol(1, x)
    #define get_sound_vol() sound_vol(0, 0)
    #define set_sound_vol(x) sound_vol(1, x)

list_t **sound_list(void);
list_t **music_list(void);
float music_vol(int change, float new);
float sound_vol(int change, float new);

    #include "audio_builder.h"

    #define ABS(x) ((x) < 0 ? -(x) : (x))
    #define REPEAT_DELAY 500000
    #define SPACING 0.06
    #define BUTTON_PRESS "./assets/audio/button_press.ogg"
    #define BUTTON_RELEASE "./assets/audio/button_release.ogg"
    #define LOBBY_MUSIC "./assets/audio/lobby.ogg"
    #define WIN_CLOSE "./assets/audio/win_close.ogg"
    #define ITM_TYPE(x) ((item_t *)((x)->data))->type

    #define VISION_ANGLE 90.0
    #define NB_RAY 90
    #define SPEED_ACC 18
    #define ABS(x) ((x) < 0 ? -(x) : (x))
    #define GET_GAME(win) ((game_t *)(win)->menus[GAME])

    #define MAX_DISTANCE 15
    #define SQRT_2 1.41421356237

typedef struct {
    button_t *buttons[5];
    sfSprite *background;
    sfRenderTexture *rtex;
} main_menu_t;

typedef struct win {
    sfVideoMode mode;
    sfRenderWindow *win;
    int state;
    void *menus[12];
    p_clock_t *lum_clock;

    int is_transition;
    int next_state;
    int framerate;

    const sfTexture* (*draw[12])(struct win *);
    void (*event[12])(struct win *, sfEvent ev);
    void (*update[12])(void *);

    sfMusic *music;
    sfSound *close_sfx;
} window_t;

typedef enum {
    SETTINGS, HOME, EXIT, GAME, LIGHT, SELECT_SAVE, CREATE_SAVE, FIGHT
} state_t;

static const sfIntRect back_rect = {
    0, 0, 1, 1
};

static const sfColor grey = {
    128, 128, 128, 255
};

static const sfIntRect stats_rects[] = {
    {648, 671, 125, 124}, // strength
    {775, 671, 128, 117}, // speed
    {648, 799, 128, 128}, // stamina
    {776, 799, 128, 128} // mental health
};

static const sfIntRect bars_frames[] = {
    {131, 0, 380, 100},
    {131, 101, 380, 100},
    {131, 202, 380, 100},
    {131, 404, 380, 100},
    {0, 0, 130, 120},
    {0, 142, 126, 120},
    {0, 284, 126, 120},
    {131, 303, 380, 100}
};

static const sfIntRect icon_rect = {
    0, 671, 648, 648
};

typedef struct {
    char player_name[13];
    float health_percent;
    float m_health_percent;
    unsigned strength;
    unsigned stamina;
    unsigned speed;
    unsigned mental_stability;
    sfColor skin_comb;
} player_info_t;

static const sfIntRect hider_rect = {
    82, 241, 128, 128
};
static const sfIntRect button_rect = {0, 81, 315, 80};

typedef struct {
    player_info_t infos;

    sfSprite *skin;

    sfSprite *border;
    sfRenderTexture *rtex;

    sfSprite *stats_img;

    sfText *stats;
    sfText *name;
} gui_player_t;

typedef struct {
    sfRenderTexture *rtex;
    sfRectangleShape *background;
    p_clock_t *underscore;
    sfText *text;
    int has_underscore;
    int max_char;
} line_edit_t;

typedef struct {
    button_t *color_buttons[6];
    sfText *col_vals[3];

    button_t *stats_buttons[8];
    sfText *stats_val[4];
    sfSprite *stats;
    sfText *stats_prompt;
    sfText *pts_left;

    sfSprite *skin;
    sfRectangleShape *skin_back;

    button_t *actions[2];

    line_edit_t *name;
    sfRenderTexture *rtex;
    sfSprite *background;
    sfText *prompt;

    p_clock_t *repeat;
    int f_no;
} create_save_t;

typedef struct {
    gui_player_t *saves[3];
    button_t *buttons[4]; // exit - delete - create - launch
    sfSprite *hider;
    sfRenderTexture *rtex;
    create_save_t *create_save;
    int primary;
    int secondary;
} choose_save_t;

typedef struct {
    npc_t *enemy;
    p_clock_t *decide_clock;
    sfInt64 rnd_mve;
    sfInt64 rnd_wait;
    sfVector2f mov_vector;
    int is_in_rush;
    splash_particles_t *splash;
} enemy_t;

__attribute__((unused)) static const char *name_qst[4] = {
    "Backrooms",
    "Beat em up",
    "Drink",
    "Pills !!!"
};

__attribute__((unused)) static const char *desc_qst[6] = {
    "Hey welcome in the backrooms.\n"
    "The backrooms are safe, but be quiet.\n"
    "Try to exit level 0.\n"
    "Good luck !\n\n"
    " Have fun =)",

    "Kill 10 entity !\n It's fun and healthy !\n   =)",

    "Do you like almond water?\n I could drink dozens"
    "\n Try to drink 10 bottles !",

    "Apparently overdoses are bad.\n Anyway, try it and take 10 pills !\n\n"
    "                  =)",

    "Congratulations !\n"
    "You successfully exited level 0.\n"
    "Now, try to exit level 1.\n"
    "Or, you can stay here with me\n"
    "and my friends =)",

    "Oh no, you're already in the last level :(\n"
    "Or are you ?\n"
    "Anyway, try to exit =)\n"
    "Good luck ;)"
};


window_t *window(window_t *ptr);
void destroy_path(path_t *p);
void update_path(path_t *p, level_t *l, ray_c *data, sfVector2f graphic_goal);
sfVector2f vector_to_objective(enemy_t *e,
game_t *game, ray_c *data, sfVector2f win_s);
void switch_clocks(void);
void destroy_enemy(void *enemy);
void quest_destroy(quest_data_t *q);
int check_pause(sfEvent ev, game_t *game);
sfFloatRect get_npc_hitbox(npc_t *player);
void draw_enemies(game_t *game, ray_c *data, window_t *win);
void create_enemy(game_t *game, ray_c *data);
void anim_npc(npc_t *npc);
int is_pnj_colliding(ray_c *data, npc_t *player, level_t *level);
void change_room(game_t *game, ray_c *data, sfVector2f pos);
void destroy_skills(skills_t *s);
void move_pl(window_t *win);
void free_save(gui_player_t *g);
void destroy_create_save(void **cr);
void free_choose_save(choose_save_t *c);
void init_from_file(gui_player_t *g,
char const *file, sfVector2f size);
void change_color(create_save_t *c, int button);
const sfTexture *draw_create_save(window_t *c);
create_save_t *create_create_save(sfVector2f size, int f_no);
void file_select_events(window_t *win, sfEvent ev);
gui_player_t *create_gui_player(char const *file, sfVector2f win_size);
void go_back_to_main(void *win);
void delete_selected(void *win);
void launch_create_file(void *win);
void launch_file(void *win);
choose_save_t *create_choose_save(sfVector2f win_size);
sfSprite *get_gui_player(gui_player_t *p, sfRenderTexture *rtex, int index);
void rescale_choose_save(choose_save_t *c, sfVector2f size);
const sfTexture *draw_choose_save(window_t *win);
void update_buttons_colors(choose_save_t *c);
void rescale_gui_player(gui_player_t *g, sfVector2f win_size);

void load_saves(choose_save_t *c);
void create_file(create_save_t *c, window_t *win);
void update_player_color(create_save_t *c);
void change_color(create_save_t *c, int button);

void create_save_events(window_t *win, sfEvent ev);

sfTexture *player_texture(void);
float size_of_char(char what, sfFont *font);

void destroy_line_edit(line_edit_t *le);
void update_underscore(line_edit_t *le);
sfSprite *draw_line_edit(line_edit_t *le, sfVector2f pos);
void scale_line_edit(line_edit_t *le, sfVector2f size);
line_edit_t *create_line_edit(sfVector2f size, char const *def, int max_char);
const char *get_text(line_edit_t *le);
void append_to_text(sfText *t, char c);
void remove_last_text(sfText *t);
void append_ev(sfEvent ev, sfText *base);
void line_edit_event(line_edit_t *le, sfEvent ev);

sfRectangleShape *create_rectangle(sfVector2f size,
sfColor fcol, float thick, sfColor ocol);

const sfTexture *draw_choose_save(window_t *win);
choose_save_t *create_choose_save(sfVector2f win_size);
void rescale_choose_save(choose_save_t *c, sfVector2f size);

// settings
void rescale_all(window_t *win);
void move_settings(settings_t *se, window_t *win);
void go_back(settings_t *se, window_t *win);
void update_full_screen(settings_t *se, window_t *win);
void update_vsync(settings_t *se, window_t *win);
void update_res(settings_t *se, window_t *win);
void update_framerate(settings_t *se, window_t *win);
void save_settings(settings_t *se);
void rescale_settings(settings_t *se, window_t *win);
void settings_ev(window_t *win, sfEvent ev);
void draw_set_button(sfRenderTexture *r, button_t *b);
const sfTexture *draw_settings(window_t *win);
void check_sound_repeat(window_t *win, sfEvent *ev);
int get_set_button_at(settings_t *se, sfEvent *ev);
void manage_settings_hover(sfEvent *ev, window_t *win);
void manage_settings_press(sfEvent *ev, window_t *win);
void manage_settings_release(sfEvent *ev, window_t *win);
sfVector2f conv(sfVector2f c, window_t *win);
settings_t *init_settings(window_t *win);
void apply_settings(settings_t *se, window_t *win);

// window
window_t *window_create(void);
void rescale_all(window_t *win);
void update_transition(window_t *win, sfSprite *s);
void set_next_win_state(window_t *win, int state);

// main menu
const sfTexture *draw_main_menu(window_t *m);
main_menu_t *create_main_menu(sfVector2f win_size);
void rescale_main_menu(main_menu_t *m, sfVector2f win_size);
void destroy_main_menu(main_menu_t *m);
void main_menu_ev(window_t *win, sfEvent ev);

// mainmenu events
void quit_main_menu(void *win);
void go_to_settings(void *win);
void go_to_local_save(void *win);
void go_to_map_editor(void *win);
void go_to_online_level(void *win);
void lazy_room(window_t *win);

// game
game_t *game_create(void);
void game_ev(window_t *win, sfEvent ev);
const sfTexture *draw_game(window_t *win);
void destroy_game(game_t *game);
void new_room(game_t *game, ray_c *light);
void draw_room(ray_c *data, game_t *game, window_t *win);
void change_form(game_t *game, sfVector2u size_win, sfVector2i tmp
, ray_c *data);
void draw_inventory(game_t *game, window_t *win);
void draw_stats_pts(game_t *game, window_t *win);
void center_inventory(game_t *game, window_t *win);
void inventory_events(game_t *game, sfEvent ev, window_t *win);
void draw_item(game_t *game, int item, int box, sfVector2f size);
void draw_item_info(game_t *game, int item, sfVector2u size);
void take_item(window_t *win, game_t *game, ray_c *data);
void my_srand(void);
void draw_bar(sfRenderTexture *rtex, sfVector2f pos,
sfVector2f size, sfVector2f types);
void draw_xp(game_t *game, window_t *win);
float get_xp_percent(npc_t *player);
void remove_xp(game_t *game, int xp);
void add_xp(game_t *game, int xp);

sfVector2f win_size(window_t *win);
int dir_from_v2f(sfVector2f vf);
sfVector2f rand_dir(void);
sfInt32 my_rand(sfInt32 min, sfInt32 max);
void rush_to_player(enemy_t *e, level_t *l, window_t *win, sfSprite *);

void update_vector(sfVector2f *vector, npc_t *npc, sfVector2f win_size);

static inline sfVector2u get_graphic_size(level_t *l, ray_c *data)
{
    return (sfVector2u){(l->size.y + 1) * data->cell,
    (l->size.x + 1) * data->cell + data->cell / 2};
}
static inline sfVector2u graphic_pos_to_map(sfVector2f graphic_pos,
sfVector2u graphic_size, sfVector2u logic_size, float cell)
{
    return (sfVector2u){
        graphic_pos.y * logic_size.y / graphic_size.y,
        (graphic_pos.x - cell / 2.0) * logic_size.x / graphic_size.x
    };
}
static inline float deg_to_rad(float degree)
{
    return degree * PI / 180.0;
}
static inline sfVector2f *alloc_v2f(float x, float y)
{
    sfVector2f *v = malloc(sizeof(sfVector2f));

    v->x = x;
    v->y = y;
    return v;
}
static inline void sftext_set_string_malloc(sfText *t, char *str)
{
    sfText_setString(t, str);
    free(str);
}
static inline interactive_npc_t *create_pnj(game_t *game, ray_c *light)
{
    return !(rand() % 3) ? create_quest_npc(rnd_quest(game->quest), game,
    light) : create_talk_npc(game, light);
}

int can_rush(enemy_t *e, ray_c *data, npc_t *player, window_t *win);
float dist_between(sfSprite *a, sfSprite *b);
void launch_combat(window_t *win);
int check_rush(enemy_t *en, ray_c *data, game_t *g, window_t *win);

void draw_quest(game_t *game, sfRenderWindow *win);
void quest_init(game_t *game);
void ev_quest(game_t *game, sfEvent ev, sfRenderWindow *win);
void rotate_vector(sfVector2f *vec, float degree);

void draw_skills(game_t *game, window_t *win);
void skills_events(game_t *game, sfEvent ev, sfVector2f size);
void scale_draw(game_t *game, sfVector2f scale);
void next_level(ray_c *data);
void sprint_event(game_t *game);
void draw_sprint(game_t *game, sfVector2f size);
void draw_cry(game_t *game, sfVector2f size);
void cry_event(game_t *game);
void draw_find_exit(game_t *game, sfVector2f size);
void find_exit_event(game_t *game);

// fight
const sfTexture *draw_fight(window_t *win);
void fight_ev(window_t *win, sfEvent ev);
void move_pl_fight(fight_t *fight, window_t *win);
void move_blocs(fight_t *fight, window_t *win);
void change_to_prop(sfRenderTexture *tex , sfRectangleShape *rec
, window_t *win);
void change_to_prop_c(sfRenderTexture *tex , sfCircleShape *crl, window_t *win);
void change_to_prop_s(sfRenderTexture *tex , sfSprite *ply, window_t *win);

void destroy_npc(npc_t *n);
void destroy_pause(pause_t *p);
void destroy_level(level_t *l);
int other_are_rushing(list_t *enemies, enemy_t *exclude);
void give_quest(quest_data_t *q, int d);
path_t *create_path(char **map, sfVector2u map_size);
int rnd_quest(quest_data_t *current_quests);

void unblock_pl(ray_c *data, npc_t *player, level_t *level);

#endif
