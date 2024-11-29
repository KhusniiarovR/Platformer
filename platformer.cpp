#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    game_frame++;

    // TODO
    if (is_player_moving && is_player_on_ground) is_player_moving = false;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        move_player_horizontally(MOVEMENT_SPEED);
        is_player_moving = true;
        player_facing_right = true;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        move_player_horizontally(-MOVEMENT_SPEED);
        is_player_moving = true;
        player_facing_right = false;
    }
    // Calculating collisions to decide whether the player is allowed to jump: don't want them to suction cup to the ceiling or jump midair
    is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && is_player_on_ground) {
        player_y_velocity = -JUMP_STRENGTH;
    }

    update_player();
}

void draw_game() {
    // TODO health

    ClearBackground(BLACK);
    draw_level();
    draw_game_overlay();
    draw_game_overlay_hearts();
}

int main() {
    InitWindow(1024, 480, "Platformer");
    SetTargetFPS(60);

    load_fonts();
    load_images();
    load_sounds();
    load_level();

    while (!WindowShouldClose()) {
        BeginDrawing();
        switch (GAMESTATE) {
            case GAME_MENU: {
                draw_menu();
                break;
            }
            case GAME_PLAY: {
                if (IsKeyDown(KEY_Q)) { GAMESTATE = GAME_PAUSED;}
                update_game();
                draw_game();
                break;
            }
            case GAME_END: {
                draw_victory_menu();
                break;
            }
            case GAME_PAUSED: {
                draw_game();
                draw_pause_menu();
                if (IsKeyDown(KEY_E)) { GAMESTATE = GAME_PLAY;}
                break;
            }
        }
        EndDrawing();
    }

    unload_level();
    unload_sounds();
    unload_images();
    unload_fonts();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
