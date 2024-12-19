#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include "level.h"

void spawn_player() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * current_level.columns + column];
            if (cell == PLAYER) {
                player_pos.x = static_cast<float>(column);
                player_pos.y = static_cast<float>(row);
                return;
            }
        }
    }
}

void move_player_horizontally(float delta) {
    float next_x = player_pos.x + delta;
    bool collision_wall = false;
    for (int i = 0; i < current_walls.size(); i++) {
        if (is_colliding({next_x, player_pos.y}, current_walls[i])) {
            collision_wall = true;
            break;
        }
    }
    if (collision_wall) { player_pos.x = roundf(player_pos.x); }
    else { player_pos.x = next_x; }
}

void move_player() {
    if (is_player_moving && is_player_on_ground) {
        is_player_moving = false;
    }
    is_player_on_ground = false;
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

    for (int i = 0; i < current_walls.size(); ++i) {
        if (is_colliding({player_pos.x, player_pos.y + 0.1f}, current_walls[i])) {
            is_player_on_ground = true;
            break;
        }
    }
    if ((is_colliding({player_pos.x + 0.1f, player_pos.y}, SLIME_JUMP) && player_facing_right) ||
        (is_colliding({player_pos.x - 0.1f, player_pos.y}, SLIME_JUMP) && !player_facing_right) && is_player_moving) {
        is_player_on_ground = true;
    }
    if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_JUMP)) {
        is_player_on_ground = false;
    }

    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && is_player_on_ground) {
        player_y_velocity = -JUMP_STRENGTH;
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE)) {
        sword_attack = true;
    }
}

void update_player() {
    player_pos.y += player_y_velocity;
    player_y_velocity += GRAVITY_FORCE;
    is_player_on_ground = false;
    for (int i = 0; i < current_walls.size(); i++) {
        if (is_colliding({ player_pos.x, player_pos.y + 0.1f }, current_walls[i])) {
            is_player_on_ground = true;
            break;
        }
    }

    if (is_player_on_ground) {
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    for (int i = 0; i < current_block.size(); i++) {
        switch (current_block[i]) {
            case COIN: {
                if (is_colliding(player_pos, COIN)) {
                    get_collider(player_pos, COIN) = ' ';
                    player_score+=10;
                    PlaySound(coin_sound);
                }
            } break;
            case SPIKE: case SPIKE_UP: {
                if (is_colliding_sizeable(player_pos, SPIKE, 0.1f) || is_colliding_sizeable(player_pos, SPIKE_UP, 0.1f)) {
                    player_die = true;
                    load_level();
                    player_lifes--;
                }
            } break;
            case CONVEYOR: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, CONVEYOR)) {
                    move_player_horizontally(-MOVEMENT_SPEED * 0.1f);
                }
            } break;
            case SLIME_JUMP: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_JUMP)) {
                    MOVEMENT_SPEED = 0.03f;
                }
                else {
                    MOVEMENT_SPEED = 0.1f;
                }
            } break;
            case SLIME_STICKY: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_STICKY)) {
                    JUMP_STRENGTH = 0.19f;}
                else { JUMP_STRENGTH = 0.27f;}
                if (is_colliding({player_pos.x + 0.1f, player_pos.y}, SLIME_STICKY)
                    || is_colliding({player_pos.x - 0.1f, player_pos.y}, SLIME_STICKY)) {
                    GRAVITY_FORCE = 0.0001f;}
                else { GRAVITY_FORCE = 0.01f;}
            } break;
            case FALL_WALL: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, FALL_WALL)) {
                    destroy_fall_wall({player_pos.x, player_pos.y + 0.1f});
                }
            } break;
            case BREAK_WALL: {
                if (sword_attack) {
                    if (is_colliding({player_pos.x + 1, player_pos.y}, BREAK_WALL) && player_facing_right) {
                        get_collider({player_pos.x + 1, player_pos.y}, BREAK_WALL) = '*';
                    }
                    if (is_colliding({player_pos.x - 1, player_pos.y}, BREAK_WALL) && !player_facing_right) {
                        get_collider({player_pos.x - 1, player_pos.y}, BREAK_WALL) = '*';
                    }
                }
            } break;
            case SPRING: {
                if (is_colliding(player_pos, SPRING)) {
                    player_y_velocity = -JUMP_STRENGTH * 1.6;
                    spring_sprite.loop = true;
                }
                else { spring_sprite.loop = false; }
            } break;
            default: break;
        }
    }
    if (is_colliding(player_pos, EXIT)) {
        current_block.clear();
        current_walls.clear();
        PlaySound(exit_sound);
        load_level();
    }
}

#endif // PLAYER_H
