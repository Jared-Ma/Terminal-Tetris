#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <stdbool.h>
#include "piece.h"

#define BOARD_H 24 
#define BOARD_W 10


struct GameState {
    Piece* curr_piece;
    Piece* next_piece;
    Piece* hold_piece;
    bool board[BOARD_H][BOARD_W];
};

typedef struct GameState GameState;

GameState game_state_get();

GameState* game_state_init();

void game_state_destroy(GameState* game_state);

void game_state_debug_print(GameState* game_state);

#endif

