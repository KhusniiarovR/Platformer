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

void update_gameplay() {
    game_frame++;
    if (game_frame % 60 == 0) {
        if (player_time > 0) {
            player_time--;
        }
        move_enemy();
    }
    if (player_lifes == 0) {
        GAMESTATE = GAME_OVER;
    }
    move_player();
    update_player();
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

    if (IsKeyPressed(KEY_V)) {
        show_game_overlay = !show_game_overlay;
    }

    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && is_player_on_ground) {
        player_y_velocity = -JUMP_STRENGTH;
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE)) {
        if (!IsSoundPlaying(sword_sound) && is_player_has_sword) {
            sword_attack = true;
            PlaySound(sword_sound);
        }
    }
}

void move_enemy() {
    for (int i = 0; i < enemy_pos.size(); i++) {
        if (enemy_pos[i].w == 1) {
            get_collider({enemy_pos[i].x, enemy_pos[i].y}, ENEMY) = AIR;
            if (!is_colliding({enemy_pos[i].x + enemy_pos[i].z, enemy_pos[i].y}, '#')) {
                enemy_pos[i].x += enemy_pos[i].z;
            }
            else {
                enemy_pos[i].z *= -1;
                enemy_pos[i].x += enemy_pos[i].z;
            }
            get_collider({enemy_pos[i].x, enemy_pos[i].y}, AIR) = ENEMY;
        }
        if (enemy_pos[i].w == 2) {
            get_collider({enemy_pos[i].x, enemy_pos[i].y}, ENEMY_UP) = AIR;
            if (!is_colliding({enemy_pos[i].x, enemy_pos[i].y + enemy_pos[i].z}, '#')
                && !is_colliding({enemy_pos[i].x, enemy_pos[i].y + enemy_pos[i].z}, 'F')) {
                enemy_pos[i].y += enemy_pos[i].z;
            }
            else {
                enemy_pos[i].z *= -1;
                enemy_pos[i].y += enemy_pos[i].z;
            }

            get_collider({enemy_pos[i].x, enemy_pos[i].y}, AIR) = ENEMY_UP;
        }
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
                    player_time += 10;
                    PlaySound(coin_sound);
                }
            } break;
            case SPIKE: case SPIKE_UP: {
                if (is_colliding_sizeable(player_pos, SPIKE, 0.1f)
                    || is_colliding_sizeable(player_pos, SPIKE_UP, 0.1f)) {
                    player_die = true;
                    PlaySound(death_sound);
                    load_level();
                    player_lifes--;
                }
            } break;
            case ENEMY: case ENEMY_UP: {
                if (is_colliding(player_pos, ENEMY)
                    || is_colliding(player_pos, ENEMY_UP)) {
                    player_die = true;
                    PlaySound(death_sound);
                    load_level();
                    player_lifes--;
                }
                if (sword_attack) {
                    if (is_colliding({player_pos.x + 1, player_pos.y}, ENEMY) && player_facing_right) {
                        for (int i = 0; i < enemy_pos.size(); i++) {
                            if (abs(enemy_pos[i].x - player_pos.x) < 2 && abs(enemy_pos[i].y - player_pos.y) < 1.5) {
                                get_collider({player_pos.x + 1, player_pos.y}, ENEMY) = '*';
                                PlaySound(enemy_death_sound);
                                enemy_pos.erase(enemy_pos.begin() + i);
                            }
                        }
                    }
                    else if (is_colliding({player_pos.x - 1, player_pos.y}, ENEMY) && !player_facing_right) {
                        for (int i = 0; i < enemy_pos.size(); i++) {
                            if (abs(player_pos.x - enemy_pos[i].x) < 2 && abs(enemy_pos[i].y - player_pos.y) < 1.5) {
                                get_collider({player_pos.x - 1, player_pos.y}, ENEMY) = '*';
                                PlaySound(enemy_death_sound);
                                enemy_pos.erase(enemy_pos.begin() + i);
                            }
                        }
                    }
                    if (is_colliding({player_pos.x + 1, player_pos.y}, ENEMY_UP) && player_facing_right) {
                        for (int i = 0; i < enemy_pos.size(); i++) {
                            if (abs(enemy_pos[i].x - player_pos.x) < 2 && abs(enemy_pos[i].y - player_pos.y) < 1.5) {
                                get_collider({player_pos.x + 1, player_pos.y}, ENEMY_UP) = '*';
                                PlaySound(enemy_death_sound);
                                enemy_pos.erase(enemy_pos.begin() + i);
                            }
                        }
                    }
                    else if (is_colliding({player_pos.x - 1, player_pos.y}, ENEMY_UP) && !player_facing_right) {
                        for (int i = 0; i < enemy_pos.size(); i++) {
                            if (abs(enemy_pos[i].x - player_pos.x) < 2 && abs(enemy_pos[i].y - player_pos.y) < 1.5) {
                                get_collider({player_pos.x - 1, player_pos.y}, ENEMY_UP) = '*';
                                PlaySound(enemy_death_sound);
                                enemy_pos.erase(enemy_pos.begin() + i);
                            }
                        }
                    }
                }
            } break;
            case CONVEYOR: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, CONVEYOR)) {
                    move_player_horizontally(MOVEMENT_SPEED * 0.3f);
                }
            } break;
            case SWORD: {
                if (is_colliding({player_pos.x, player_pos.y}, SWORD)) {
                    get_collider(player_pos, SWORD) = ' ';
                    is_player_has_sword = true;
                    PlaySound(sword_pick_up_sound);
                }
            }
            case SLIME_JUMP: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_JUMP)) {
                    MOVEMENT_SPEED = 0.03f; }
                else { MOVEMENT_SPEED = 0.1f; }
            } break;
            case SLIME_STICKY: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, SLIME_STICKY)) {
                    JUMP_STRENGTH = 0.19f; }
                else { JUMP_STRENGTH = 0.27f; }
                if (is_colliding({player_pos.x + 0.1f, player_pos.y}, SLIME_STICKY)
                    || is_colliding({player_pos.x - 0.1f, player_pos.y}, SLIME_STICKY)) {
                    player_y_velocity = 0.03f; }
            } break;
            case FALL_WALL: {
                if (is_colliding({player_pos.x, player_pos.y + 0.1f}, FALL_WALL)) {
                    destroy_fall_wall({player_pos.x, player_pos.y + 0.1f}); }
            } break;
            case BREAK_WALL: {
                if (sword_attack) {
                    if (is_colliding({player_pos.x + 1, player_pos.y}, BREAK_WALL) && player_facing_right) {
                        get_collider({player_pos.x + 1, player_pos.y}, BREAK_WALL) = '*'; }
                    else if (is_colliding({player_pos.x - 1, player_pos.y}, BREAK_WALL) && !player_facing_right) {
                        get_collider({player_pos.x - 1, player_pos.y}, BREAK_WALL) = '*'; }
                }
            } break;
            case SPRING: {
                if (is_colliding(player_pos, SPRING)) {
                    player_y_velocity = -JUMP_STRENGTH * 1.6;
                    spring_sprite.loop = true;
                    PlaySound(spring_sound);
                }
                else { spring_sprite.loop = false; }
            } break;
            default: break;
        }
    }
    if (is_colliding(player_pos, EXIT) || IsKeyPressed(KEY_EQUAL)) {
        if (player_time > 1) {
            PlaySound(exit_sound);
            completed_levels[offset] = true;
        }
        else {
            PlaySound(lose_sound);
        }
        load_level();
    }
}

#endif // PLAYER_H
