#ifndef IMAGES_H
#define IMAGES_H

#include "raylib.h"
#include "globals.h"

#include <string>
#include <cassert>

void load_fonts() {
    menu_font = LoadFontEx("data/fonts/ARCADE_N.ttf", 256, nullptr, 128);
}

void unload_fonts() {
    UnloadFont(menu_font);
}

void load_images() {
    wall_image    = LoadTexture("data/images/wall.png");
    air_image     = LoadTexture("data/images/air.png");
    spike_image   = LoadTexture("data/images/spike.png");
    spike_up_image = LoadTexture("data/images/spike_up.png");
    spring_image  = LoadTexture("data/images/spring_idle.png");
    heart_image   = LoadTexture("data/images/heart.png");
    main_menu_image = LoadTexture("data/images/main_menu.png");
    game_over_image = LoadTexture("data/images/game_over.png");
    sword_image = LoadTexture("data/images/sword.png");
    break_wall_image = LoadTexture("data/images/break_wall.png");
    falling_wall_image = LoadTexture("data/images/falling_wall.png");
    slime_jump_image = LoadTexture("data/images/slime_jump.png");
    slime_sticky_image = LoadTexture("data/images/slime_sticky.png");
    fire_ball_image = LoadTexture("data/images/fire_ball.png");
    coin_sprite   = load_sprite("data/images/coin/coin", ".png", 3, true, 18);
    player_sprite = load_sprite("data/images/player/player_move/player", ".png", 3, true, 10);
    player_idle_sprite = load_sprite("data/images/player/player_idle/player_idle", ".png", 2, true, 20);
    spring_sprite = load_sprite("data/images/spring/spring", ".png", 4, false, 1);
    exit_sprite = load_sprite("data/images/exit/exit", ".png", 3, true, 30);
    conveyor_sprite = load_sprite("data/images/conveyor/conveyor", ".png", 2, true, 30);
}

void unload_images() {
    UnloadTexture(wall_image);
    UnloadTexture(air_image);
    UnloadTexture(spike_image);
    UnloadTexture(spike_up_image);
    UnloadTexture(spring_image);
    UnloadTexture(heart_image);
    UnloadTexture(main_menu_image);
    UnloadTexture(game_over_image);
    UnloadTexture(sword_image);
    UnloadTexture(break_wall_image);
    UnloadTexture(falling_wall_image);
    UnloadTexture(slime_jump_image);
    UnloadTexture(slime_sticky_image);
    UnloadTexture(fire_ball_image);
    unload_sprite(player_sprite);
    unload_sprite(player_idle_sprite);
    unload_sprite(coin_sprite);
    unload_sprite(spring_sprite);
    unload_sprite(exit_sprite);
    unload_sprite(conveyor_sprite);
}

void draw_image(Texture2D image, Vector2 pos, float size) {
    draw_image(image, pos, size, size);
}

void draw_image(Texture2D image, Vector2 pos, float width, float height) {
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(image.width), static_cast<float>(image.height) };
    Rectangle destination = { pos.x, pos.y, width, height };
    DrawTexturePro(image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void draw_image_player(Texture2D image, Vector2 pos, float width, float height) {
    Rectangle source = { 0.0f, 0.0f, static_cast<float>(image.width), static_cast<float>(image.height)};
    Rectangle destination = { pos.x, pos.y, width, height };
    if (!player_facing_right) {
        source.width = static_cast<float>(-image.width);
    }
    DrawTexturePro(image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void draw_image_sword(Texture2D image, Vector2 pos, float width, float height) {
    sword_counter++;
    Rectangle source = { 0.0f, static_cast<float>(image.height), static_cast<float>(image.width), static_cast<float>(image.height)};
    Rectangle destination = {pos.x, pos.y, width, height};
    float cosine = abs(cos(sword_counter / 20 + 30)) * 0.8;
    if (!player_facing_right) {
        source.width = static_cast<float>(-image.width);
        destination.x -= width * cosine;
    }
    else { destination.x += width * cosine;}
    if (cosine - 0.02f < 0) {
        sword_counter = 0;
        sword_attack = false;
    }
    DrawTexturePro(image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void draw_game_overlay_hearts() {
    Rectangle source_rec = {0, 0, (float) heart_image.width, (float) heart_image.height};
    Rectangle destination_rec = {static_cast<float>(screen_size.x * 0.75), 0, 60 * screen_scale, 75 * screen_scale};
    for (int i = 0; i < player_lifes; i++) {
        destination_rec.x += 35 * screen_scale;
        DrawTexturePro(heart_image, source_rec, destination_rec, {0,0}, 0.0f, WHITE);
    }
}

sprite load_sprite(
    const std::string &file_name_prefix,
    const std::string &file_name_suffix,
    size_t frame_count,
    bool loop,
    size_t frames_to_skip
) {
    assert(frame_count < 100);

    sprite result = {
        frame_count, frames_to_skip, 0, 0, loop, 0, new Texture2D[frame_count]
    };
    for (size_t i = 0; i < frame_count; ++i) {
        std::string file_name;
        if (frame_count < 10) {
            file_name = file_name_prefix;
            file_name += std::to_string(i);
            file_name += file_name_suffix;
        } else {
            file_name = file_name_prefix;
            file_name += i < 10 ? ("0" + std::to_string(i)) : std::to_string(i);
            file_name += file_name_suffix;
        }
        result.frames[i] = LoadTexture(file_name.c_str());
    }

    return result;
}

void unload_sprite(sprite &sprite) {
    assert(sprite.frames != nullptr);

    for (size_t i = 0; i < sprite.frame_count; ++i) {
        UnloadTexture(sprite.frames[i]);
    }
    delete[] sprite.frames;
    sprite.frames = nullptr;
}

void draw_sprite(sprite &sprite, Vector2 pos, float size) {
    draw_sprite(sprite, pos, size, size);
}

void anim_calc(sprite &sprite_frame_count) {
    if (sprite_frame_count.prev_game_frame == game_frame) {
        return;
    }
    if (sprite_frame_count.frames_skipped < sprite_frame_count.frames_to_skip) {
        ++sprite_frame_count.frames_skipped;
    } else {
        sprite_frame_count.frames_skipped = 0;

        ++sprite_frame_count.frame_index;
        if (sprite_frame_count.frame_index >= sprite_frame_count.frame_count) {
            sprite_frame_count.frame_index = sprite_frame_count.loop ? 0 : sprite_frame_count.frame_count - 1;
        }
    }
    sprite_frame_count.prev_game_frame = game_frame;
}

void draw_player_anim(Vector2 pos, float width, float height) {
    if (!is_player_moving && is_player_on_ground) {
        draw_image_player(player_idle_sprite.frames[player_idle_sprite.frame_index], pos, width, height);
        anim_calc(player_idle_sprite);
    }
    else {
        draw_image_player(player_sprite.frames[player_sprite.frame_index], pos, width, height);
        anim_calc(player_sprite);
    }
}

void draw_sprite(sprite &sprite, Vector2 pos, float width, float height) {
    draw_image(sprite.frames[sprite.frame_index], pos, width, height);
    if (sprite.prev_game_frame == game_frame) {
        return;
    }
    if (sprite.frames_skipped < sprite.frames_to_skip) {
        ++sprite.frames_skipped;
    } else {
        sprite.frames_skipped = 0;

        ++sprite.frame_index;
        if (sprite.frame_index >= sprite.frame_count) {
            sprite.frame_index = sprite.loop ? 0 : sprite.frame_count - 1;
        }
    }
    sprite.prev_game_frame = game_frame;
}

void load_sounds() {
    InitAudioDevice();
    coin_sound = LoadSound("data/sounds/coin.wav");
    exit_sound = LoadSound("data/sounds/exit.wav");
    main_menu_music = LoadSound("data/sounds/music_main.mp3");
    win_sound = LoadSound("data/sounds/win.mp3");
}

void unload_sounds() {
    UnloadSound(coin_sound);
    UnloadSound(exit_sound);
    UnloadSound(main_menu_music);
    UnloadSound(win_sound);
}

#endif // IMAGES_H
