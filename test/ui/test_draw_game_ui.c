#include "test_draw_game_ui.h"
#include "draw.h"

#include <stdint.h>


void test_draw_hold_window(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);
    game_window_refresh(&hold_window);
}

void test_draw_board_window(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);
    game_window_refresh(&board_window);
}

void test_draw_next_window(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);
    game_window_refresh(&next_window);
}

void test_draw_stats_window(int8_t y_offset, int8_t x_offset) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(&stats_window);
    game_window_refresh(&stats_window);
}

void test_draw_controls_window(int8_t y_offset, int8_t x_offset) {
    GameWindow controls_window = game_window_get(
        CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, 
        CONTROLS_WINDOW_Y + y_offset, CONTROLS_WINDOW_X + x_offset
    );
    draw_controls_window(&controls_window);
    game_window_refresh(&controls_window);
}

void test_draw_main_menu_window(int8_t y_offset, int8_t x_offset) {
    GameWindow main_menu_window = game_window_get(
        MAIN_MENU_WINDOW_H, MAIN_MENU_WINDOW_W, 
        MAIN_MENU_WINDOW_Y + y_offset, MAIN_MENU_WINDOW_X + x_offset
    );
    draw_main_menu_window(&main_menu_window, 1);
    game_window_refresh(&main_menu_window);
}

void test_draw_pause_window(int8_t y_offset, int8_t x_offset) {
    GameWindow pause_window = game_window_get(
        PAUSE_WINDOW_H, PAUSE_WINDOW_W, 
        PAUSE_WINDOW_Y + y_offset, PAUSE_WINDOW_X + x_offset
    );
    draw_pause_window(&pause_window);
    game_window_refresh(&pause_window);
}

void test_draw_game_over_window(int8_t y_offset, int8_t x_offset) {
    GameWindow game_over_window = game_window_get(
        GAME_OVER_WINDOW_H, GAME_OVER_WINDOW_W, 
        GAME_OVER_WINDOW_Y + y_offset, GAME_OVER_WINDOW_X + x_offset
    );
    draw_game_over_window(&game_over_window);
    game_window_refresh(&game_over_window);
}

void test_draw_board_stack(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);
    
    GameState game_state = game_state_get();
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (i % 2 == 0) {
                game_state.board[i][j] = (j % 2 == 0) ? (i % NUM_SHAPES) + 1 : 0;
            } else {
                game_state.board[i][j] = (j % 2 == 0) ? 0 : (i % NUM_SHAPES) + 1;
            }
        }
    }

    draw_board_stack(&board_window, &game_state);
    game_window_refresh(&board_window);
}

void test_draw_buffer_zone_line(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);
    draw_buffer_zone_line(&board_window);
    game_window_refresh(&board_window);
}

void test_draw_curr_piece_i_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(I, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_j_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(J, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_l_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(L, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_o_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(O, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_s_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(S, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_t_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(T, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_z_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(Z, SPAWN_Y, SPAWN_X);
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_lock_delay_dim(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(I, SPAWN_Y, SPAWN_X);
    game_state.lock_delay_timer = 20;
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_curr_piece_lock_delay_standout(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(I, SPAWN_Y, SPAWN_X);
    game_state.lock_delay_timer = LOCK_DELAY_STANDOUT_MAX;
    draw_curr_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_i_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(I, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_j_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(J, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_l_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(L, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_o_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(O, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_s_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(S, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_t_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(T, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_ghost_piece_z_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    game_state.curr_piece = piece_get(Z, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    draw_ghost_piece(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_score(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state.score = 12345678;
    draw_score(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_board_state(int8_t y_offset, int8_t x_offset) {
    GameWindow board_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(&board_window);

    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);
    for (size_t i = BOARD_H - NUM_SHAPES; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state.board[i][j] = (i % NUM_SHAPES) + 1;
        }
    }
    game_state.curr_piece = piece_get(I, SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(&game_state);
    game_state.score = 12345678;
    draw_board_state(&board_window, &game_state);

    game_window_refresh(&board_window);
}

void test_draw_hold_piece_i_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(I, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_j_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(J, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_l_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(L, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_o_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(O, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_s_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(S, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_t_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(T, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_z_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(Z, 0, 0);
    game_state.holding_piece = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_i_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(I, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_j_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(J, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_l_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(L, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_o_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(O, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_s_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(S, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_t_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(T, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_hold_piece_z_piece_blocked(int8_t y_offset, int8_t x_offset) {
    GameWindow hold_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(&hold_window);

    GameState game_state = game_state_get();
    game_state.hold_piece = piece_get(Z, 0, 0);
    game_state.holding_piece = true;
    game_state.hold_blocked = true;
    draw_hold_piece(&hold_window, &game_state);

    game_window_refresh(&hold_window);
}

void test_draw_next_piece_i_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(I, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_next_piece_j_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(J, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_next_piece_l_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(L, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_next_piece_o_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(O, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_next_piece_s_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(S, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_next_piece_t_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(T, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_next_piece_z_piece(int8_t y_offset, int8_t x_offset) {
    GameWindow next_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(&next_window);

    GameState game_state = game_state_get();
    game_state.next_piece = piece_get(Z, 0, 0);
    draw_next_piece(&next_window, &game_state);

    game_window_refresh(&next_window);
}

void test_draw_stats(int8_t y_offset, int8_t x_offset) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(&stats_window);

    GameState game_state = game_state_get();
    game_state.lines = 1234;
    game_state.level = 1234;

    Stats stats = stats_get();
    stats.seconds = 754;
    stats.score_per_sec = 1.2345;
    stats.piece_per_sec = 6.7890;

    draw_stats(&stats_window, &game_state, &stats);

    game_window_refresh(&stats_window);
}

void test_draw_pause_stats(int8_t y_offset, int8_t x_offset) {
    GameWindow stats_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(&stats_window);

    Stats stats = stats_get();
    stats.num_single = 12;
    stats.num_double = 34;
    stats.num_triple = 56;
    stats.num_tetris = 78;

    draw_pause_stats(&stats_window, &stats);

    game_window_refresh(&stats_window);
}
