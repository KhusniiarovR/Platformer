#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"

bool is_colliding(Vector2 pos, char look_for, level &level) {
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};
    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t column = 0; column < level.columns; ++column) {
            if (level.data[row * level.columns + column] == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_colliding_sizeable(Vector2 pos, char look_for, float size_x, level &level) {
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};
    float offset_x = (1.0f - size_x)/2;
    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t column = 0; column < level.columns; ++column) {
            if (level.data[row * level.columns + column] == look_for) {
                Rectangle block_hitbox = {(float) column + offset_x, (float) row, size_x/10, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

char& get_collider(Vector2 pos, char look_for, level &level) {
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t column = 0; column < level.columns; ++column) {
            if (level.data[row * level.columns + column] == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return level.data[row * level.columns + column];
                }
            }
        }
    }

    return level.data[static_cast<int>(roundf(pos.y) * level.columns + roundf(pos.x))];
}

void load_level() {
    if (!player_die) {
        offset++;
        level_index = offset;

        if (level_index >= LEVEL_COUNT) {
            create_victory_menu_background();
            GAMESTATE = GAME_END;
            return;
        }
    }
    size_t rows = LEVELS[level_index].rows;
    size_t columns = LEVELS[level_index].columns;
    current_level_data = new char[rows*columns];

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            current_level_data[row*columns + column] = LEVELS[level_index].data[row*columns + column];
        }
    }

    current_level = {rows, columns, current_level_data};
    player_die = false;
    spawn_player();
    derive_graphics_metrics_from_loaded_level();
}

void unload_level() {
    delete[] current_level_data;
}

#endif // LEVEL_H