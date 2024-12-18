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
    if (!is_colliding({next_x, player_pos.y}, WALL)
        && !is_colliding({next_x, player_pos.y}, BREAK_WALL)
        && !is_colliding({next_x, player_pos.y}, SLIME_STICKY)
        && !is_colliding({next_x, player_pos.y}, SLIME_JUMP)) {
        player_pos.x = next_x;
    } else {
        player_pos.x = roundf(player_pos.x);
    }
}

void update_player() {
    player_pos.y += player_y_velocity;
    player_y_velocity += GRAVITY_FORCE;

    is_player_on_ground = is_colliding({ player_pos.x, player_pos.y + 0.1f }, WALL)
                        || is_colliding({ player_pos.x, player_pos.y + 0.1f }, FALL_WALL)
                        || is_colliding({ player_pos.x, player_pos.y + 0.1f }, SLIME_STICKY)
                        || is_colliding({ player_pos.x, player_pos.y +0.1f }, SLIME_JUMP)
                        || is_colliding({ player_pos.x, player_pos.y + 0.1f }, ICE);
    if (is_player_on_ground) {
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    if (is_colliding(player_pos, COIN)) {
        get_collider(player_pos, COIN) = ' ';
        player_score+=10;
        PlaySound(coin_sound);
    }
    if (is_colliding(player_pos, EXIT)) {
        PlaySound(exit_sound);
        load_level();
    }
    if (is_colliding_sizeable(player_pos, SPIKE, 0.1f) || is_colliding_sizeable(player_pos, SPIKE_UP, 0.1f)) {
        player_die = true;
        load_level();
        player_lifes--;
    }
    if (is_colliding(player_pos, ICE)) {
        if (is_player_moving) {
            if (player_facing_right) {
                player_pos.x += 100.0f;
            }
            else {
                player_pos.x -= 100.0f;
            }
        }
        // TODO ice_logic
    }
    if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_JUMP)) {
        JUMP_STRENGTH = 0.10f;
        MOVEMENT_SPEED = 0.03f;}
    else {
        JUMP_STRENGTH = 0.27f;
        MOVEMENT_SPEED = 0.1f;}
    if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_STICKY)) {
        JUMP_STRENGTH = 0.19f;}
    else { JUMP_STRENGTH = 0.27f;}
    if (is_colliding({player_pos.x + 0.1f, player_pos.y}, SLIME_STICKY)
        || is_colliding({player_pos.x - 0.1f, player_pos.y}, SLIME_STICKY)) {
        GRAVITY_FORCE = 0.0001f;}
    else { GRAVITY_FORCE = 0.01f;}
    if (is_colliding({player_pos.x, player_pos.y + 0.1f}, FALL_WALL)) {
        destroy_fall_wall({player_pos.x, player_pos.y + 0.1f});
    }
    if (sword_attack) {
        if (is_colliding({player_pos.x + 1, player_pos.y}, BREAK_WALL) && player_facing_right) {
            get_collider({player_pos.x + 1, player_pos.y}, BREAK_WALL) = '*';
        }
        if (is_colliding({player_pos.x - 1, player_pos.y}, BREAK_WALL) && !player_facing_right) {
            get_collider({player_pos.x - 1, player_pos.y}, BREAK_WALL) = '*';
        }
    }
    if (is_colliding(player_pos, SPRING)) {
        player_y_velocity = -JUMP_STRENGTH * 1.6;
        spring_sprite.loop = true;
    }
    else { spring_sprite.loop = false; }
}

#endif // PLAYER_H
