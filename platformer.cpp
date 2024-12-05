#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    game_frame++;

    if (player_lifes == 0) {
        GAMESTATE = GAME_OVER;
    }
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

    is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && is_player_on_ground) {
        player_y_velocity = -JUMP_STRENGTH;
    }

    update_player();
}

void draw_game() {
    ClearBackground(BLACK);
    draw_level();
    draw_game_overlay();
    draw_game_overlay_hearts();
}

int main() {
    InitWindow(1024, 480, "Platformer");
    //InitWindow(1920, 1020, "Platformer");
    //ToggleBorderlessWindowed();
    SetExitKey(0);
    SetTargetFPS(60);

    load_fonts();
    load_images();
    load_sounds();
    load_level();

    while (!WindowShouldClose()) {
        if (!IsSoundPlaying(main_menu_music)) {
            PlaySound(main_menu_music);
        }
        BeginDrawing();
        if (exit_condition || IsKeyPressed(KEY_I)) {
            break;
        }
        switch (GAMESTATE) {
            case GAME_MENU: {
                draw_menu();
                break;
            }
            case GAME_PLAY: {
                if (IsKeyPressed(KEY_ESCAPE)) { GAMESTATE = GAME_PAUSED;}
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
                if (IsKeyPressed(KEY_ESCAPE)) { GAMESTATE = GAME_PLAY;}
                break;
            }
            case GAME_OVER: {
                ClearBackground(BLACK);
                draw_game_over();
                if (IsKeyPressed(KEY_ENTER)) { GAMESTATE = GAME_MENU;}
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
