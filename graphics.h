#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "assets.h"
#include "globals.h"

void draw_text(Text &text) {
    Vector2 dimensions = MeasureTextEx(*text.font, text.str.c_str(), text.size * screen_scale, text.spacing);
    Vector2 pos = {
        (screen_size.x * text.position.x) - (0.5f * dimensions.x),
        (screen_size.y * text.position.y) - (0.5f * dimensions.y)
    };

    DrawTextEx(*text.font, text.str.c_str(), pos, dimensions.y, text.spacing, text.color);
}

void derive_graphics_metrics_from_loaded_level() {
    screen_size.x  = static_cast<float>(GetScreenWidth());
    screen_size.y = static_cast<float>(GetScreenHeight());

    cell_size = std::min(
        screen_size.x / static_cast<float>(current_level.columns),
        screen_size.y / static_cast<float>(current_level.rows)
    ) * CELL_SCALE;
    screen_scale = std::min(
        screen_size.x,
        screen_size.y
    ) / SCREEN_SCALE_DIVISOR;
    float level_width  = static_cast<float>(current_level.columns) * cell_size;
    float level_height = static_cast<float>(current_level.rows)    * cell_size;
    shift_to_center.x = (screen_size.x - level_width) * 0.5f;
    shift_to_center.y = (screen_size.y - level_height) * 0.5f;
}

void draw_menu_buttons() {
    Vector2 mouse_pos = GetMousePosition();
    Rectangle play_button = {screen_size.x * 0.3f, screen_size.y * 0.75f, screen_size.x * 0.4f, screen_size.y * 0.1f};
    DrawRectangleRoundedLines(play_button, 0.5f, 10, 2, WHITE);
    draw_text(::play_button);
    Rectangle exit_button = {screen_size.x * 0.3f, screen_size.y * 0.87f, screen_size.x * 0.4f, screen_size.y * 0.1f};
    DrawRectangleRoundedLines(exit_button, 0.5f, 10, 2, WHITE);
    draw_text(::exit_button);
    {
        if (CheckCollisionPointRec(mouse_pos, play_button)) {
            is_mouse_inside_play_button = true;
        }
        else { is_mouse_inside_play_button = false;}
    }
    {
        if (CheckCollisionPointRec(mouse_pos, exit_button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exit_condition = true;
        }
    }
}

void draw_menu() {
    ClearBackground(BLACK);
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(main_menu_image.width), static_cast<float>(main_menu_image.height) };
    Rectangle destination = { 0, 0, screen_size.x, screen_size.y };
    DrawTexturePro(main_menu_image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
    draw_menu_buttons();

    if (IsKeyPressed(KEY_ENTER) || (is_mouse_inside_play_button && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) )) {
        GAMESTATE = GAME_LEVEL_SELECTION;
    }
}

void draw_selection_menu() {
    ClearBackground(BLACK);
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(main_menu_image.width), static_cast<float>(main_menu_image.height) };
    Rectangle destination = { 0, 0, screen_size.x, screen_size.y };
    DrawTexturePro(main_menu_image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
    Vector2 mouse_pos = GetMousePosition();
    Rectangle back_button_rec = {0.005f * screen_size.x, 0.01f * screen_size.y,
                             screen_size.x * 0.2f, screen_size.y * 0.13f};
    DrawRectangleRounded(back_button_rec, 1, 4, {0,0,0,70});
    draw_text(back_button);
    if (IsKeyPressed(KEY_ENTER)) {
        GAMESTATE = GAME_PLAY;
        offset = -1;
        player_score = 0;
        player_lifes = 3;
        level_index = 0;
        load_level();
    }
    if (IsKeyPressed(KEY_ESCAPE) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, back_button_rec))) {
        GAMESTATE = GAME_MENU;
    }
    for (int j = 1; j <= LEVEL_COUNT / 5 + 1; j++) {
        for (int i = 1; i <= 5; i++) {
            int number = (j-1) * 5 + i;
            if (number > LEVEL_COUNT) {
                return;
            }
            float unit = screen_size.x/6;
            Rectangle rect = {unit * i - screen_size.x/24, 0.2f * j * screen_size.y, screen_size.x/12, screen_size.y/10};
            DrawRectangleRounded(rect, 1, 6, {0,0,0,50});
            Text level_number = {std::to_string(number), {(unit * i) / screen_size.x,
            (screen_size.y * 0.2f * j + screen_size.y * 0.05f) / screen_size.y}, 32, GREEN};
            draw_text(level_number);
            if (CheckCollisionPointRec(mouse_pos, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                GAMESTATE = GAME_PLAY;
                offset = number - 2;
                player_score = 0;
                player_lifes = 3;
                level_index = 0;
                load_level();
            }
        }
    }
}

void draw_game_overlay() {
    Text score = {
        "Score " + std::to_string(player_score),
        { 0.50f, 0.05f },
        48.0f
    };
    Text score_shadow = {
        "Score " + std::to_string(player_score),
        { 0.503f, 0.055f },
        48.0f,
        GRAY
    };

    draw_text(score_shadow);
    draw_text(score);
}

void draw_level() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {

            Vector2 pos = {
                    shift_to_center.x + static_cast<float>(column) * cell_size,
                    shift_to_center.y + static_cast<float>(row) * cell_size
            };

            char cell = current_level.data[row * current_level.columns + column];
            // The first image layer
            switch (cell) {
                case AIR:
                case PLAYER:
                case COIN:
                case EXIT:
                case SPIKE:
                    draw_image(air_image, pos, cell_size);
                    break;
                case SPIKE_UP:
                    draw_image(air_image, pos, cell_size);
                    break;
                case SPRING:
                    draw_image(air_image, pos, cell_size);
                    break;
                case BREAK_WALL:
                    draw_image(break_wall_image, pos, cell_size);
                    break;
                case FALL_WALL:
                    draw_image(falling_wall_image, pos, cell_size);
                    break;
                case SLIME_JUMP:
                    draw_image(slime_jump_image, pos, cell_size);
                    break;
                case SLIME_STICKY:
                    draw_image(slime_sticky_image, pos, cell_size);
                    break;
                case WALL:
                    draw_image(wall_image, pos, cell_size);
                    break;
                default:
                    break;
            }
            // The second image layer
            switch (cell) {
                case COIN:
                    draw_sprite(coin_sprite, pos, cell_size);
                    break;
                case EXIT:
                    draw_sprite(exit_sprite, pos, cell_size);
                    break;
                case SPIKE:
                    draw_image(spike_image, pos, cell_size);
                    break;
                case SPIKE_UP:
                    draw_image(spike_up_image, pos, cell_size);
                    break;
                case SPRING:
                    draw_sprite(spring_sprite, pos, cell_size);
                    break;
                default:
                    break;
            }
        }
    }
    draw_player();
}

void draw_player() {
    Vector2 pos = {
        shift_to_center.x + player_pos.x * cell_size,
        shift_to_center.y + player_pos.y * cell_size
    };
    draw_player_anim(pos, cell_size, cell_size);
    if (sword_attack) {
        draw_image_sword(sword_image, pos, cell_size, cell_size);
    }
}

void draw_pause_menu() {
    draw_text(game_paused);
    Vector2 mouse_pos = GetMousePosition();
    Rectangle back_button_rec = {0.005f * screen_size.x, 0.01f * screen_size.y,
                             screen_size.x * 0.2f, screen_size.y * 0.13f};
    DrawRectangleRounded(back_button_rec, 1, 4, {255,255,255,70});
    draw_text(back_button);
    if (IsKeyPressed(KEY_ESCAPE) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, back_button_rec))) {
        GAMESTATE = GAME_MENU;
    }
    if (IsKeyPressed(KEY_ENTER)) { GAMESTATE = GAME_PLAY;}
}

void create_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x  = rand_up_to(screen_size.x);
        ball.y  = rand_up_to(screen_size.y);
        ball.dx = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED);
        ball.dx *= screen_scale;
        if (abs(ball.dx) < 0E-1) ball.dx = 1.0f;
        ball.dy = rand_from_to(-VICTORY_BALL_MAX_SPEED, VICTORY_BALL_MAX_SPEED);
        ball.dy *= screen_scale;
        if (abs(ball.dy) < 0E-1) ball.dy = 1.0f;
        ball.radius = rand_from_to(VICTORY_BALL_MIN_RADIUS, VICTORY_BALL_MAX_RADIUS);
        ball.radius *= screen_scale;
    }

    /* Clear both the front buffer and the back buffer to avoid ghosting of the game graphics. */
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
    BeginDrawing();
}

void animate_victory_menu_background() {
    for (auto &ball : victory_balls) {
        ball.x += ball.dx;
        if (ball.x - ball.radius < 0 ||
            ball.x + ball.radius >= screen_size.x) {
            ball.dx = -ball.dx;
        }
        ball.y += ball.dy;
        if (ball.y - ball.radius < 0 ||
            ball.y + ball.radius >= screen_size.y) {
            ball.dy = -ball.dy;
        }
    }
}

void draw_victory_menu_background() {
    for (auto &ball : victory_balls) {
        DrawCircleV({ ball.x, ball.y }, ball.radius, VICTORY_BALL_COLOR);
    }
}

void draw_victory_menu() {
    DrawRectangle(
        0, 0,
        static_cast<int>(screen_size.x), static_cast<int>(screen_size.y),
        { 0, 0, 0, VICTORY_BALL_TRAIL_TRANSPARENCY }
    );

    animate_victory_menu_background();
    draw_victory_menu_background();
    draw_text(victory_title);
    draw_text(victory_subtitle);
    if (IsKeyPressed(KEY_ENTER)) {
        GAMESTATE = GAME_MENU;
    }
}

void draw_game_over() {
    ClearBackground({81, 86, 120, 255});
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(game_over_image.width), static_cast<float>(game_over_image.height) };
    Rectangle destination = { 0, 0, GetScreenWidth()/2.0f, GetScreenHeight()/1.0f };
    DrawTexturePro(game_over_image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
    Vector2 mouse_pos = GetMousePosition();
    Rectangle exit_button = {screen_size.x * 0.6f, screen_size.y * 0.65f, screen_size.x * 0.3f, screen_size.y * 0.1f};
    DrawRectangleRoundedLines(exit_button, 0.5f, 10, 2, WHITE);
    draw_text(exit_button_game_over);
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, exit_button)) {
        GAMESTATE = GAME_MENU;
    }
    if (IsKeyPressed(KEY_Z)) {
        GAMESTATE = GAME_PLAY;
        offset--;
        player_lifes = 3;
        player_score = 0;
        load_level();
    }
}

#endif // GRAPHICS_H
