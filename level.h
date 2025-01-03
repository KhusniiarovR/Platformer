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
        bool complete = true;
        for (int i = 0; i < LEVEL_COUNT; i++) {
            if (completed_levels[i] == false) {
                complete = false;
                break;
            }
        }
        if (level_index >= LEVEL_COUNT && !complete) {
            GAMESTATE = GAME_LEVEL_SELECTION;
            return;
        }
        if (complete) {
            create_victory_menu_background();
            PlaySound(win_sound);
            GAMESTATE = GAME_END;
            return;
        }
        player_lifes = 2;
        current_block.clear();
        current_walls.clear();
        for (int i = 0; i < LEVELS[level_index].blocks.size(); i++) {
            current_block.push_back(LEVELS[level_index].blocks[i]);
        }
        for (size_t i = 0; i < LEVELS[level_index].wall_blocks.size(); i++) {
            current_walls.push_back(LEVELS[level_index].wall_blocks[i]);
        }
    }
    unload_level();
    player_time = 30;
    is_player_has_sword = false;

    size_t rows = LEVELS[level_index].rows;
    size_t columns = LEVELS[level_index].columns;
    current_level_data = new char[rows*columns];

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            current_level_data[row*columns + column] = LEVELS[level_index].data[row*columns + column];
            if (current_level_data[row*columns + column] == ENEMY) {
                enemy_pos.push_back({(float) column, (float) row, 1.0f, 1});
            }
            if (current_level_data[row*columns + column] == ENEMY_UP) {
                enemy_pos.push_back({(float) column, (float) row, 1.0f, 2});
            }
        }
    }
    current_level = {rows, columns, current_level_data};
    player_die = false;
    spawn_player();
    derive_graphics_metrics_from_loaded_level();
}

void unload_level() {
    delete[] current_level_data;
    enemy_pos.clear();
}

#endif // LEVEL_H
