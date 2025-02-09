#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <stdbool.h>
#include "piece.h"

#define BOARD_H 20 
#define BOARD_W 10

#define SRS_NUM_ROTATIONS 8
#define SRS_NUM_TESTS 5
#define SRS_NUM_COORDS 2

// const int SRS_TABLE[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];
// const int SRS_TABLE_I[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS];

struct GameState {
    Piece curr_piece;
    Piece hold_piece;
    Piece next_piece;
    Piece ghost_piece;
    bool holding_piece;
    size_t next_index;
    Shape next_shapes[NUM_SHAPES];
    bool board[BOARD_H][BOARD_W];
};

typedef struct GameState GameState;

GameState game_state_get();

GameState* game_state_init();

void game_state_destroy(GameState* game_state);

void debug_print_table();

void game_state_debug_print(GameState* game_state);

void game_state_gen_next_shapes(GameState* game_state);

void game_state_load_next_piece(GameState* game_state);

void game_state_hold_piece(GameState* game_state);

void game_state_move_curr_piece(GameState* game_state, int y, int x);

void game_state_rotate_curr_piece_srs(GameState *game_state, Rotation rotation);

void game_state_rotate_curr_piece(GameState* game_state, Rotation rotation);

void game_state_place_curr_piece(GameState* game_state);

void game_state_apply_gravity(GameState* game_state, size_t row, size_t num_lines);

void game_state_clear_line(GameState* game_state, size_t row);

void game_state_clear_lines(GameState* game_state);

void game_state_drop_curr_piece(GameState* game_state);

void game_state_move_ghost_piece(GameState* game_state, int y, int x);

void game_state_update_ghost_piece(GameState* game_state);

#endif

