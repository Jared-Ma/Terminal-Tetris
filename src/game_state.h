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

#define MAX_GRAVITY_LEVEL 15
#define LEVEL_LINE_REQ 10
#define LOCK_DELAY 30
#define MAX_MOVE_RESET 15
#define SOFT_DROP_GRAVITY_MULT 20

#define SINGLE_MULT 100
#define DOUBLE_MULT 300
#define TRIPLE_MULT 500
#define TETRIS_MULT 800
#define T_SPIN_ZERO_MULT 400
#define T_SPIN_SINGLE_MULT 800
#define T_SPIN_DOUBLE_MULT 1200
#define T_SPIN_TRIPLE_MULT 1600
#define T_SPIN_MINI_ZERO_MULT 100
#define T_SPIN_MINI_SINGLE_MULT 200
#define T_SPIN_MINI_DOUBLE_MULT 400
#define SINGLE_PERFECT_CLEAR_MULT 800
#define DOUBLE_PERFECT_CLEAR_MULT 1200
#define TRIPLE_PERFECT_CLEAR_MULT 1800
#define TETRIS_PERFECT_CLEAR_MULT 2000
#define B2B_TETRIS_PERFECT_CLEAR_MULT 3200
#define B2B_DIFFICULT_CLEAR_MULT 1.5
#define COMBO_MULT 50
#define SOFT_DROP_MULT 1
#define HARD_DROP_MULT 2


struct GameState {
    Piece curr_piece;
    Piece hold_piece;
    Piece next_piece;
    Piece ghost_piece;
    Shape board[BOARD_H][BOARD_W];

    bool holding_piece;
    bool hold_blocked;
    uint8_t next_index;
    Shape next_queue[NUM_SHAPES];

    bool soft_drop;
    float gravity_value;
    uint8_t lock_delay_timer;
    uint8_t move_reset_count;

    size_t level;
    size_t lines;
    size_t score;
    int combo;
    uint8_t t_rotation_test_num;
    bool curr_clear_difficult;
    bool prev_clear_difficult;
    bool prev_clear_perfect_tetris;
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

void game_state_apply_stack_gravity(GameState* game_state, size_t row);

void game_state_clear_line(GameState* game_state, size_t row);

void game_state_clear_lines(GameState* game_state);

void game_state_hard_drop_curr_piece(GameState* game_state);

void game_state_move_ghost_piece(GameState* game_state, int y, int x);

void game_state_update_ghost_piece(GameState* game_state);

bool game_state_check_top_out(GameState* game_state);

void game_state_reset_lock_delay_timer(GameState* game_state);

void game_state_decrement_lock_delay_timer(GameState* game_state);

void game_state_reset_move_reset_count(GameState* game_state);

void game_state_increment_move_reset_count(GameState* game_state);

bool game_state_check_curr_piece_grounded(GameState* game_state);

size_t game_state_calc_t_spin_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_line_clear_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_perfect_clear_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_combo_points(GameState* game_state, size_t num_lines);

float game_state_calc_difficult_clear_mult(GameState* game_state, size_t num_lines);

void game_state_increase_score(GameState* game_state, size_t points);

void game_state_increment_level(GameState* game_state);

void game_state_increase_lines(GameState* game_state, size_t num_lines);

void game_state_reset_combo(GameState* game_state);

void game_state_increment_combo(GameState* game_state);

void game_state_set_prev_clear_difficult(GameState* game_state, bool value);

void game_state_set_curr_clear_difficult(GameState* game_state, bool value);

void game_state_set_prev_clear_perfect_tetris(GameState* game_state, bool value);

void game_state_reset_gravity_value(GameState* game_state);

void game_state_increase_gravity_value(GameState* game_state, float value);

void game_state_set_soft_drop(GameState* game_state, bool value);

void game_state_apply_gravity(GameState* game_state);

void game_state_soft_drop_curr_piece(GameState* game_state);

void game_state_apply_soft_drop_gravity(GameState* game_state);

void game_state_set_t_rotation_test_num(GameState* game_state, uint8_t value);

bool game_state_check_t_spin(GameState* game_state);

bool game_state_check_t_spin_mini(GameState* game_state);

bool game_state_check_empty_board(GameState* game_state);

#endif
