#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "piece.h"

#define BUFFER_ZONE_H 2
#define BOARD_H 22
#define BOARD_W 10

#define SRS_NUM_ROTATIONS 8
#define SRS_NUM_TESTS 5
#define SRS_NUM_COORDS 2
#define MAX_GRAVITY_LEVEL 15


extern const int8_t SPAWN_Y;
extern const int8_t SPAWN_X;

extern const uint8_t LEVEL_LINE_REQ;
extern const uint8_t LOCK_DELAY;
extern const uint8_t MAX_MOVE_RESET;
extern const uint8_t SOFT_DROP_GRAVITY_MULT;

extern const uint16_t SINGLE_POINTS;
extern const uint16_t DOUBLE_POINTS;
extern const uint16_t TRIPLE_POINTS;
extern const uint16_t TETRIS_POINTS;

extern const uint16_t T_SPIN_ZERO_POINTS;
extern const uint16_t T_SPIN_SINGLE_POINTS;
extern const uint16_t T_SPIN_DOUBLE_POINTS;
extern const uint16_t T_SPIN_TRIPLE_POINTS;

extern const uint16_t T_SPIN_MINI_ZERO_POINTS;
extern const uint16_t T_SPIN_MINI_SINGLE_POINTS;
extern const uint16_t T_SPIN_MINI_DOUBLE_POINTS;

extern const uint16_t SINGLE_PERFECT_CLEAR_POINTS;
extern const uint16_t DOUBLE_PERFECT_CLEAR_POINTS;
extern const uint16_t TRIPLE_PERFECT_CLEAR_POINTS;
extern const uint16_t TETRIS_PERFECT_CLEAR_POINTS;
extern const uint16_t B2B_TETRIS_PERFECT_CLEAR_POINTS;

extern const uint16_t COMBO_POINTS;
extern const uint16_t SOFT_DROP_POINTS;
extern const uint16_t HARD_DROP_POINTS;
extern const float B2B_DIFFICULT_CLEAR_MULT;

extern const int SRS_TABLE[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];
extern const int SRS_TABLE_I[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];
extern const int SRS_TABLE_O[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];
extern const float GRAVITY_TABLE[MAX_GRAVITY_LEVEL];

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

    uint64_t level;
    uint64_t lines;
    uint64_t score;
    int64_t combo;
    int64_t difficult_clear_combo;
    int64_t tetris_perfect_clear_combo;
    uint8_t t_rotation_test_num;
    uint64_t last_action_points;
    char last_action_string[64];
};

typedef struct GameState GameState;

GameState game_state_get(void);

GameState* game_state_init(void);

void game_state_destroy(GameState* game_state);

void game_state_start(GameState* game_state);

void game_state_reset(GameState* game_state);

void game_state_debug_print(GameState* game_state);

void game_state_generate_next_queue(GameState* game_state);

void game_state_load_next_piece(GameState* game_state);

void game_state_spawn_curr_piece(GameState* game_state);

void game_state_hold_piece(GameState* game_state);

bool game_state_check_collision(GameState* game_state, Piece piece);

bool game_state_check_curr_piece_grounded(GameState* game_state);

void game_state_move_curr_piece(GameState* game_state, int y, int x);

void game_state_rotate_curr_piece(GameState* game_state, Rotation rotation);

void game_state_rotate_curr_piece_srs(GameState* game_state, Rotation rotation);

void game_state_hard_drop_curr_piece(GameState* game_state);

void game_state_lock_curr_piece(GameState* game_state);

void game_state_apply_stack_gravity(GameState* game_state, size_t row);

void game_state_clear_line(GameState* game_state, size_t row);

void game_state_clear_lines(GameState* game_state);

void game_state_apply_gravity(GameState* game_state);

void game_state_apply_soft_drop_gravity(GameState* game_state);

void game_state_soft_drop_curr_piece(GameState* game_state);

void game_state_move_ghost_piece(GameState* game_state, int y, int x);

void game_state_update_ghost_piece(GameState* game_state);

bool game_state_check_t_spin(GameState* game_state);

bool game_state_check_t_spin_mini(GameState* game_state);

bool game_state_check_empty_board(GameState* game_state);

size_t game_state_calc_t_spin_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_line_clear_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_t_spin_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_perfect_clear_points(GameState* game_state, size_t num_lines);

size_t game_state_calc_combo_points(GameState* game_state, size_t num_lines);

float game_state_calc_difficult_clear_mult(GameState* game_state, size_t num_lines);

#endif
