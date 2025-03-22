#include "test_draw_game_vfx.h"
#include "vfx.h"
#include "draw.h"

#include <stdint.h>


void test_vfx_lock_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_i_piece);
}

void test_vfx_lock_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_j_piece);
}

void test_vfx_lock_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_l_piece);
}

void test_vfx_lock_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_o_piece);
}

void test_vfx_lock_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_s_piece);
}

void test_vfx_lock_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_t_piece);
}

void test_vfx_lock_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_lock_piece_reset, LOCK_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_lock_z_piece);
}

void test_vfx_line_clear_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_line_clear_reset, LINE_CLEAR_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_line_clear_single);
}

void test_vfx_line_clear_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_line_clear_reset, LINE_CLEAR_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_line_clear_double);
}

void test_vfx_line_clear_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_line_clear_reset, LINE_CLEAR_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_line_clear_triple);
}

void test_vfx_line_clear_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_line_clear_reset, LINE_CLEAR_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_line_clear_tetris);
}

void test_vfx_line_clear_t_spin(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_line_clear_reset, LINE_CLEAR_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_line_clear_t_spin);
}

void test_vfx_line_clear_all_clear(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_line_clear_reset, LINE_CLEAR_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_line_clear_all_clear);
}

void test_vfx_hold_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_i_piece);
}

void test_vfx_hold_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_j_piece);
}

void test_vfx_hold_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_l_piece);
}

void test_vfx_hold_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_o_piece);
}

void test_vfx_hold_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_s_piece);
}

void test_vfx_hold_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_t_piece);
}

void test_vfx_hold_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        HOLD_WINDOW_H, HOLD_WINDOW_W,
        HOLD_WINDOW_Y + y_offset, HOLD_WINDOW_X + x_offset
    );
    draw_hold_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_hold_piece_reset, HOLD_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_hold_z_piece);
}

void test_vfx_next_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_i_piece);
}

void test_vfx_next_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_j_piece);
}

void test_vfx_next_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_l_piece);
}

void test_vfx_next_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_o_piece);
}

void test_vfx_next_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_s_piece);
}

void test_vfx_next_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);
    
    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_t_piece);
}

void test_vfx_next_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        NEXT_WINDOW_H, NEXT_WINDOW_W,
        NEXT_WINDOW_Y + y_offset, NEXT_WINDOW_X + x_offset
    );
    draw_next_window(game_window);

    *vfx = vfx_get(game_window, draw_vfx_next_piece_reset, NEXT_PIECE_VFX_FRAMES);
    vfx_enable(vfx, draw_vfx_next_z_piece);
}

void test_vfx_action_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 2;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 3;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 4;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_t_spin = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    game_state.last_action_t_spin = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 2;
    game_state.last_action_t_spin = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 3;
    game_state.last_action_t_spin = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin_mini(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_t_spin_mini = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin_mini_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    game_state.last_action_t_spin_mini = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_t_spin_mini_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 2;
    game_state.last_action_t_spin_mini = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_all_clear_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    game_state.last_action_all_clear = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_all_clear_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 2;
    game_state.last_action_all_clear = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_all_clear_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 3;
    game_state.last_action_all_clear = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_action_all_clear_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 4;
    game_state.last_action_all_clear = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_action_reset, ACTION_VFX_FRAMES);
    vfx_enable_action(vfx, &game_state);
}

void test_vfx_combo(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    game_state.combo = 123;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_combo_reset, COMBO_VFX_FRAMES);
    vfx_enable_combo(vfx, &game_state);
}

void test_vfx_b2b_combo(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    game_state.difficult_clear_combo = 123;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_b2b_combo_reset, B2B_COMBO_VFX_FRAMES);
    vfx_enable_b2b_combo(vfx, &game_state);
}

void test_vfx_points(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.last_action_num_lines = 1;
    game_state.last_action_points = 12345678;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_points_reset, POINTS_VFX_FRAMES);
    vfx_enable_points(vfx, &game_state);
}

void test_vfx_level_up(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        BOARD_WINDOW_H, BOARD_WINDOW_W,
        BOARD_WINDOW_Y + y_offset, BOARD_WINDOW_X + x_offset
    );
    draw_board_window(game_window);

    GameState game_state = game_state_get();
    game_state.level = 1;
    game_state.level_up_event_flag = true;

    *vfx = vfx_get(game_window, draw_vfx_level_up_reset, LEVEL_UP_VFX_FRAMES);
    vfx_enable_level_up(vfx, &game_state);
}

void test_vfx_stats_lines(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.lines = 1;
    game_state.last_action_num_lines = 1;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_stats_lines_reset, STATS_LINES_VFX_FRAMES);
    vfx_enable_stats_lines(vfx, &game_state);
}

void test_vfx_stats_level(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset) {
    *game_window = game_window_get(
        STATS_WINDOW_H, STATS_WINDOW_W,
        STATS_WINDOW_Y + y_offset, STATS_WINDOW_X + x_offset
    );
    draw_stats_window(game_window);

    GameState game_state = game_state_get();
    Stats stats = stats_get();
    game_state.level = 1;
    game_state.level_up_event_flag = true;
    draw_stats(game_window, &game_state, &stats);

    *vfx = vfx_get(game_window, draw_vfx_stats_level_reset, STATS_LEVEL_VFX_FRAMES);
    vfx_enable_stats_level(vfx, &game_state);
}
