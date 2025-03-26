#include "test_game_perf.h"
#include "game_state.h"

#include <time.h>


void test_game_state_clear_lines_perf(struct timespec* start_time, struct timespec* end_time) {
    GameState game_state = game_state_get();
    
    Shape test_board[BOARD_H][BOARD_W] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state.board[i][j] = test_board[i][j];
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, start_time);
    game_state_clear_lines(&game_state);
    clock_gettime(CLOCK_MONOTONIC, end_time);
}

void test_game_state_start_perf(struct timespec* start_time, struct timespec* end_time) {
    GameState game_state = game_state_get();

    clock_gettime(CLOCK_MONOTONIC, start_time);
    game_state_start(&game_state, 1);
    clock_gettime(CLOCK_MONOTONIC, end_time);
}

void test_game_state_spawn_curr_piece_perf(struct timespec* start_time, struct timespec* end_time) {
    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);

    clock_gettime(CLOCK_MONOTONIC, start_time);
    game_state_spawn_curr_piece(&game_state);
    clock_gettime(CLOCK_MONOTONIC, end_time);
}

void test_game_state_move_curr_piece_perf(struct timespec* start_time, struct timespec* end_time) {
    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);

    clock_gettime(CLOCK_MONOTONIC, start_time);
    game_state_move_curr_piece(&game_state, (BOARD_H-1)/2, (BOARD_W-1)/2);
    clock_gettime(CLOCK_MONOTONIC, end_time);
}

void test_game_state_rotate_curr_piece_srs(struct timespec* start_time, struct timespec* end_time) {
    GameState game_state = game_state_get();
    game_state_start(&game_state, 1);

    game_state.curr_piece = piece_get(I, (BOARD_H-1)/2, (BOARD_W-1)/2);

    Shape test_board[BOARD_H][BOARD_W] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state.board[i][j] = test_board[i][j];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, start_time);
    game_state_rotate_curr_piece_srs(&game_state, RIGHT);
    clock_gettime(CLOCK_MONOTONIC, end_time);
}
