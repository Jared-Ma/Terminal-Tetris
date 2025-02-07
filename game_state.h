#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <stdbool.h>
#include "piece.h"

#define BOARD_H 20 
#define BOARD_W 10


struct GameState {
    Piece curr_piece;
    Piece hold_piece;
    Piece next_piece;
    bool holding_piece;
    size_t next_index;
    Shape next_shapes[NUM_SHAPES];
    bool board[BOARD_H][BOARD_W];
};

typedef struct GameState GameState;

GameState game_state_get();

GameState* game_state_init();

void game_state_destroy(GameState* game_state);

void game_state_debug_print(GameState* game_state);

void game_state_gen_next_shapes(GameState* game_state);

void game_state_load_next_piece(GameState* game_state);

void game_state_hold_piece(GameState* game_state);

void game_state_move_piece(GameState* game_state, int y, int x);

void game_state_rotate_piece(GameState* game_state, Rotation rotation);

void game_state_place_piece(GameState* game_state);

#endif

