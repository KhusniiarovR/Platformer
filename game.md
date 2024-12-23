title:Gray Castle

KEYS:

menu: 

    enter/lmb(play) to open level selection menu

    escape/lmb(exit) to close game

level_selection_menu:

    enter to start previous played level(first by default)

    escape/lmb(back) to open menu

    lmb(level_icons) to choose level

game:

    awsd or key_arrows to move player

    space/lmb to attack with sword

    escape to pause

    'V' to hide/show game_overlay

    '=' to instantly complete level

pause:

    enter to resume

    escape/lmb(back) to open menu

game_win:

    enter to open menu

game_over:

    escape/lmb(menu) to open menu

    enter/lmb(again) to restart level

ADDED FEATURES:

menu:

    add menu gamestate

    add menu_image

    add menu buttons(play_exit) (alternative enter/escape)

level_selection_menu:

    add level_selection_menu gamestate

    add menu_image

    add back_button

    add rounded_rectangles(buttons) // using for loop

    numbers inside rectangles show if level is completed(green) or not(red)


level loading system:

    struct level add vector<char> blocks && vector<char> wall_blocks to check collisions with blocks that are in current level (level.h/load_level)
        example: for (int i = 0; i < blocks.size(); i++) {switch(blocks[i])} (player.h/update_player)
    
    change score to time(if time == 0 player didnt complete level) (player.h/update_player/237L)
    
    collision with walls horizontal check with for loop (player.h/move_player_horizontally)
    
    collision with walls vertical (player.h/move_player/49L)


obstacles: (player.h/update_player)

    WALL   = '#'; standart gray_bricks

    AIR    = ' '; standart clear space

    PLAYER = '@'; player_start position

    COIN   = '*'; pickupable give + 10 seconds time / animated / has sound

    EXIT   = 'E'; main goal to touch this / animated

    SPIKE  = 'S'; can kill player, bool player_die(level.h/load_level) / has small collision (level.h/is_colliding_sizeable) (makes game more balanced)

    SPIKE_UP = 's'; the same as above but upside_down

    SPRING = 'J'; boost player to the sky / animated / has sound

    BREAK_WALL = 'B'; looks similarly to WALL, can be cleared with sword and drop coin

    FALL_WALL = 'F'; if player touch will start timer (utilities.h/destroy_fall_wall) and then will change to AIR

    SLIME_JUMP = 'j'; green slime slow_down and desreace jump_strength but can slow_down falling

    SLIME_STICKY = 'T'; blue slime give ability to bounce from sides, but turn off jumping as usual

    CONVEYOR = 'C'; constantly move player
    enemy logic:
        <Vector4> enemy_pos (filled in level.h/load_level);x,y for position in level grid, z to remember destionation, w to check type of enemy
        move (player.h/move_enemy) every second
        ENEMY = 'Z'; purple enemy, can kill player, move by grid left-right every second, has wall collision detection and can be destroyed with sword and drop coin/has death_sound
        ENEMY_UP = 'z'; blue, similar as above but move up-down

    SWORD = 'A'; pickupable give player sword / has sound


NEW GAME CHANGES:

in game:

        add idle_animation(use bool is_player_moving) (assets.h/draw_player_anim)

        bool player_facing_right to rotate player_sprite (left/right) (assets.h/draw_image_player)

        to check do you have sword look at sword_icon(left_down corner), press space/lbm to attack(bool sword_attack) (assets.h/draw_image_sword) move with cosine function, can destroy break_walls and enemies

        globally playing_music (platformer.cpp/main/44L)

game_overlay:

        hearts system(graphics/draw_game_overlay)

        is player have sword icon, (black if not)

        time to complete level 

        level_number(left_top corner) to check your level_number(red if is not completed, green if it is)
    