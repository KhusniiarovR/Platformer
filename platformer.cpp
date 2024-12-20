#include "raylib.h"
#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    game_frame++;
    if (game_frame % 30 == 0) {
        if (player_score > 0) {
            player_score--;
        }
        if (game_frame % 60 == 0) {
            move_enemy();
        }
    }
    if (player_lifes == 0) {
        GAMESTATE = GAME_OVER;
    }
    move_player();
    update_player();
}

void draw_game() {
    ClearBackground(BLACK);
    draw_level();
    draw_game_overlay();
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
        if (!IsSoundPlaying(main_menu_music)) {
            PlaySound(main_menu_music);
        }
        if (exit_condition || IsKeyPressed(KEY_I)) {
            break;
        }
        BeginDrawing();
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
                break;
            }
            case GAME_OVER: {
                ClearBackground(BLACK);
                draw_game_over();
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
