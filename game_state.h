#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "piece.h"

#define TARGET_FPS 60

#define BOARD_H 22
#define BOARD_W 10
#define BUFFER_ZONE_H 2
#define SPAWN_Y 1
#define SPAWN_X (BOARD_W - 1) / 2

#define SRS_NUM_ROTATIONS 8
#define SRS_NUM_TESTS 5
#define SRS_NUM_COORDS 2

#define NUM_LEVELS 15
#define LEVEL_LINE_REQ 10
#define LOCK_DELAY 30
#define MAX_MOVE_RESET 15

#define SINGLE_MULT 100
#define DOUBLE_MULT 300
#define TRIPLE_MULT 500
#define TETRIS_MULT 800
#define COMBO_MULT 50


struct GameState {
    Piece curr_piece;
    Piece hold_piece;
    Piece next_piece;
    Piece ghost_piece;
    bool holding_piece;
    bool hold_allowed;
    uint8_t next_index;
    Shape next_queue[NUM_SHAPES];
    Shape board[BOARD_H][BOARD_W];

    size_t score;
    uint8_t level;
    size_t lines;
    int combo;
    bool prev_clear_difficult;
    
    uint8_t lock_delay_timer;
    uint8_t move_reset_count;
    size_t fall_count;
    size_t fall_frame_count;
};

typedef struct GameState GameState;

GameState game_state_get(void);

GameState* game_state_init(void);

void game_state_destroy(GameState* game_state);

void game_state_restart(GameState* game_state);

void game_state_debug_print(GameState* game_state);

void game_state_gen_next_queue(GameState* game_state);

void game_state_load_next_piece(GameState* game_state);

void game_state_hold_piece(GameState* game_state);

void game_state_move_curr_piece(GameState* game_state, int y, int x);

void game_state_rotate_curr_piece_srs(GameState* game_state, Rotation rotation);

void game_state_rotate_curr_piece(GameState* game_state, Rotation rotation);

void game_state_lock_curr_piece(GameState* game_state);

void game_state_apply_stack_gravity(GameState* game_state, size_t row, size_t num_lines);

void game_state_clear_line(GameState* game_state, size_t row);

void game_state_clear_lines(GameState* game_state);

void game_state_drop_curr_piece(GameState* game_state);

void game_state_move_ghost_piece(GameState* game_state, int y, int x);

void game_state_update_ghost_piece(GameState* game_state);

bool game_state_check_top_out(GameState* game_state);

void game_state_reset_lock_delay_timer(GameState* game_state);

void game_state_decrement_lock_delay_timer(GameState* game_state);

void game_state_reset_move_reset_count(GameState* game_state);

void game_state_increment_move_reset_count(GameState* game_state);

bool game_state_check_curr_piece_grounded(GameState* game_state);

size_t game_state_calc_line_clear_points(GameState* game_state, size_t lines_cleared);

void game_state_update_score(GameState* game_state, size_t points);

void game_state_increment_level(GameState* game_state);

void game_state_update_lines(GameState* game_state, size_t num_lines);

void game_state_reset_combo(GameState* game_state);

void game_state_increment_combo(GameState* game_state);

void game_state_set_prev_clear_difficult(GameState* game_state, bool value);

void game_state_reset_fall_count(GameState* game_state);

void game_state_increment_fall_count(GameState* game_state);

void game_state_reset_fall_frame_count(GameState* game_state);

void game_state_increment_fall_frame_count(GameState* game_state);

void game_state_apply_fall_speed(GameState* game_state);

#endif
