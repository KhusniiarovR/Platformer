#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"

#include <string>
#include <cstddef>
#include <cmath>

/* Game Elements */

const char WALL   = '#';
const char AIR    = ' ';
const char PLAYER = '@';
const char COIN   = '*';
const char EXIT   = 'E';
const char SPIKE  = 'S';
const char SPIKE_UP = 's';
const char SPRING = 'J'; //jump
const char BREAK_WALL = 'B';
const char FALL_WALL = 'F';
const char SLIME_JUMP = 'j';
const char SLIME_STICKY = 'T';

/* Levels */

struct level {
    size_t rows = 0, columns = 0;
    char *data = nullptr;
};

char LEVEL_1_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '@', ' ', ' ', ' ', 'S', ' ', ' ', 'E', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
};

char LEVEL_2_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', '@', ' ', ' ', '#', '*', ' ', ' ', ' ', ' ', 'E',
    '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', 'S', 'S', ' ', '#', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};

char LEVEL_3_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', 'E', ' ', ' ', ' ', '*', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', '#',
    '#', '#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', 'S', ' ', ' ', 'S', ' ', ' ', ' ', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '@', ' ', ' ', 'S', 'S', ' ', ' ', 'J', 'S', 'S', 'S', ' ', ' ', ' ', 'J', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};

char LEVEL_4_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 's', 's', ' ', ' ', ' ', ' ', '*', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'T', ' ', ' ', '#',
    '#', '@', ' ', ' ', ' ', 'S', ' ', 'S', ' ', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'E', ' ', ' ', ' ', '#',
    '#', '#', '#', 'T', 'T', '#', 'T', '#', 'T', '#', '#', '#', '#', '#', 'T', '#', '#', '#', '#', '#', 'T', 'T', '#',
};

char LEVEL_5_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#',
    '#', 'B', ' ', ' ', ' ', ' ', '#',
    '#', '#', ' ', ' ', ' ', ' ', 'T',
    '#', ' ', ' ', 'j', 'j', ' ', 'T',
    '#', ' ', ' ', '#', ' ', ' ', 'T',
    'j', ' ', '#', '#', ' ', ' ', 'T',
    'j', ' ', 'j', 'T', ' ', ' ', '#',
    'j', ' ', 'j', 'T', ' ', 'S', '#',
    'j', ' ', 'j', 'T', ' ', '#', '#',
    '#', ' ', '#', 'T', ' ', ' ', '#',
    '#', ' ', '#', '#', ' ', ' ', '#',
    '#', ' ', ' ', '#', ' ', ' ', '#',
    '#', '#', ' ', '#', ' ', ' ', '#',
    '#', '@', ' ', '#', 'S', 'E', '#',
    '#', '#', '#', '#', '#', '#', '#',
};

char LEVEL_6_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', 'S', ' ', ' ', ' ', ' ', 'S', 'S', ' ', ' ', 'S', ' ', ' ', ' ', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'J', '#',
    '#', '@', ' ', ' ', 'S', ' ', ' ', ' ', ' ', ' ', 'S', ' ', ' ', ' ', ' ', '#', '#',
    '#', '#', 'F', 'F', '#', 'F', 'F', 'F', 'F', 'F', '#', 'F', 'F', 'F', 'F', '#', '#',
    '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#',
    '#', '#', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', '#', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};

char LEVEL_7_DATA[] = {
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 's', 's', '#',
    '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', ' ', ' ', ' ', 'S', ' ', ' ', 'S', ' ', ' ', 'S', ' ', ' ', 'S', ' ', ' ', '#',
    '#', ' ', ' ', ' ', 'j', ' ', ' ', 'j', ' ', ' ', 'j', ' ', ' ', 'j', ' ', ' ', '#',
    '#', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
    '#', '#', 'S', 'J', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', ' ', '#',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'E', '#',
};

level LEVEL_1 = {
    7, 11,
    LEVEL_1_DATA
};

level LEVEL_2 = {
    8, 11,
    LEVEL_2_DATA
};

level LEVEL_3 = {
    14, 17,
    LEVEL_3_DATA
};

level LEVEL_4 = {
    6, 23,
    LEVEL_4_DATA
};

level LEVEL_5 = {
    15, 7,
    LEVEL_5_DATA
};

level LEVEL_6 = {
    14, 17,
    LEVEL_6_DATA
};

level LEVEL_7 = {
    10, 17,
    LEVEL_7_DATA
};

int level_index = 0;
const int LEVEL_COUNT = 7;

level LEVELS[LEVEL_COUNT] = {
    LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, LEVEL_6, LEVEL_7
};

/* Loaded Level Data */

level current_level;
char *current_level_data;
int offset = -1;

/* Player data */

float GRAVITY_FORCE = 0.01f;
float JUMP_STRENGTH = 0.27f;
float MOVEMENT_SPEED = 0.1f;

Vector2 player_pos;
float player_y_velocity = 0;

bool is_player_on_ground;
bool is_player_moving;
bool player_facing_right = true;
bool sword_attack = false;
bool player_die = false;

int player_score = 0;
int player_lifes = 3;

/* Graphic Metrics */

const float CELL_SCALE = 1.0f; // An aesthetic parameter to add some negative space around level
const float SCREEN_SCALE_DIVISOR = 700.0f; // The divisor was found through experimentation
                                           // to scale things accordingly to look pleasant.

Vector2 screen_size;
float screen_scale; // Used to scale str/UI components size and displacements based on the screen_size size
float cell_size;
Vector2 shift_to_center;

/* Fonts */

Font menu_font;

/* Display Text Parameters */

struct Text {
    std::string str;
    Vector2 position = { 0.50f, 0.50f };
    float size = 32.0f;
    Color color = WHITE;
    float spacing = 4.0f;
    Font* font = &menu_font;
};

Text game_paused = {
    "Press Escape to Resume"
};

Text victory_title = {
    "You Won!",
    { 0.50f, 0.50f },
    100.0f,
    RED
};

Text victory_subtitle = {
    "Press Enter to go back to menu",
    { 0.50f, 0.65f }
};

Text game_over = {
"You Lose, Press Enter to continue",
    {0.50, 0.50}, 20, RED
};

Text play_button = {
    "PLAY", {0.50, 0.80}, 50, WHITE
};

Text exit_button = {
    "EXIT", {0.50, 0.92}, 50, RED
};

/* Images and Sprites */

Texture2D wall_image;
Texture2D air_image;
Texture2D spike_image;
Texture2D spike_up_image;
Texture2D spring_image;
Texture2D heart_image;
Texture2D main_menu_image;
Texture2D game_over_image;
Texture2D fire_ball_image;
Texture2D sword_image;
Texture2D break_wall_image;
Texture2D falling_wall_image;
Texture2D slime_jump_image;
Texture2D slime_sticky_image;

struct sprite {
    size_t frame_count    = 0;
    size_t frames_to_skip = 3;
    size_t frames_skipped = 0;
    size_t frame_index    = 0;
    bool loop = true;
    size_t prev_game_frame = 0;
    Texture2D *frames = nullptr;
};

sprite coin_sprite;
sprite player_sprite;
sprite player_idle_sprite;
sprite spring_sprite;
sprite exit_sprite;

/* Sounds */

Sound coin_sound;
Sound exit_sound;
Sound main_menu_music;

/* Victory Menu Background */

struct victory_ball {
    float x, y;
    float dx, dy;
    float radius;
};

const size_t VICTORY_BALL_COUNT     = 2000;
const float VICTORY_BALL_MAX_SPEED  = 2.0f;
const float VICTORY_BALL_MIN_RADIUS = 2.0f;
const float VICTORY_BALL_MAX_RADIUS = 3.0f;
const Color VICTORY_BALL_COLOR      = { 180, 180, 180, 255 };
const unsigned char VICTORY_BALL_TRAIL_TRANSPARENCY = 10;
victory_ball victory_balls[VICTORY_BALL_COUNT];

/* Frame Counter */

size_t game_frame = 0;
size_t sword_counter = 0;

/* Game States */

enum game_state {
    GAME_MENU,
    GAME_LEVEL_SELECTION,
    GAME_PLAY,
    GAME_END,
    GAME_PAUSED,
    GAME_OVER
};
game_state GAMESTATE = GAME_MENU;

/* Forward Declarations */

// GRAPHICS_H

void draw_text(Text &text);
void derive_graphics_metrics_from_loaded_level();
void draw_menu();
void draw_menu_buttons();
void draw_selection_menu();
void draw_game_overlay();
void draw_level();
void draw_player();
void draw_pause_menu();
void create_victory_menu_background();
void animate_victory_menu_background();
void draw_victory_menu_background();
void draw_victory_menu();

bool is_mouse_inside_play_button = false;
bool exit_condition = false;
// LEVEL_H

bool is_colliding(Vector2 pos, char look_for = '#', level &level = current_level);
bool is_colliding_sizeable(Vector2 pos, char look_for = '#', float size_x = 1.0f, level &level = current_level);
char& get_collider(Vector2 pos, char look_for, level &level = current_level);

void load_level();
void unload_level();

// PLAYER_H

void spawn_player();
void move_player_horizontally(float delta);
void update_player();

// ASSETS_H

void load_fonts();
void unload_fonts();

void load_images();
void unload_images();

void draw_image(Texture2D image, Vector2 pos, float width, float height);
void draw_image_player(Texture2D image, Vector2 pos, float width, float height);
void draw_image_sword(Texture2D image, Vector2 pos, float width, float height);
void draw_image(Texture2D image, Vector2 pos, float size);
void draw_game_overlay_hearts();

sprite load_sprite(
    const std::string &file_name_prefix,
    const std::string &file_name_suffix,
    size_t frame_count = 1,
    bool loop = true,
    size_t frames_to_skip = 3
);
void unload_sprite(sprite &sprite);
void draw_sprite(sprite &sprite, Vector2 pos, float width, float height);
void draw_sprite(sprite &sprite, Vector2 pos, float size);
void draw_player_anim(Vector2 pos, float width, float height);
void anim_calc(sprite &sprite_frame_count);

void load_sounds();
void unload_sounds();

// UTILITIES_H

float rand_from_to(float from, float to);
float rand_up_to(float to);
void destroy_fall_wall(Vector2 pos);

#endif // GLOBALS_H