#include "raylib.h"
#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    switch (GAMESTATE) {
        case GAME_MENU: {
            if (IsKeyPressed(KEY_ENTER) || (is_mouse_inside_play_button && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )) {
                GAMESTATE = GAME_LEVEL_SELECTION; }
            break;
        }
        case GAME_LEVEL_SELECTION: {
            if (IsKeyPressed(KEY_ENTER)) {
                GAMESTATE = GAME_PLAY;
                offset--;
                level_index = 0;
                load_level();
            }
            break;
        }
        case GAME_PLAY: {
            update_gameplay();
            break;
        }
        case GAME_END: {
            if (IsKeyPressed(KEY_ENTER)) {
                for (int i = 0; i < LEVEL_COUNT; i++) {
                    completed_levels[i] = false;
                }
                GAMESTATE = GAME_MENU;
            }
            break;
        }
        case GAME_PAUSED: case GAME_OVER: {
            break;
        }
    }
}

void draw_game() {
    ClearBackground(BLACK);
    switch (GAMESTATE) {
        case GAME_MENU: {
            draw_menu();
        break;
        }
        case GAME_LEVEL_SELECTION: {
            draw_selection_menu();
        break;
        }
        case GAME_PLAY: {
            draw_gameplay();
        break;
        }
        case GAME_END: {
            draw_victory_menu();
        break;
        }
        case GAME_PAUSED: {
            draw_gameplay();
            draw_pause_menu();
        break;
        }
        case GAME_OVER: {
            draw_game_over();
        break;
        }
    }
}

int main() {
    //InitWindow(1024, 480, "Platformer");
    InitWindow(1920, 1020, "Platformer");
    ToggleBorderlessWindowed();
    SetExitKey(0);
    SetTargetFPS(60);

    load_fonts();
    load_images();
    load_sounds();
    load_level();

    while (!WindowShouldClose()) {
        if (!IsSoundPlaying(main_music)) {
            PlaySound(main_music);
        }
        if (exit_condition) { break; }
        update_game();
        BeginDrawing();
        draw_game();
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
