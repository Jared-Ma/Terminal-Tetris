#include "test_game_perf.h"
#include "game_state.h"

#include <time.h>


void test_game_state_clear_lines_perf(struct timespec* start_time, struct timespec* end_time) {
    GameState game_state = game_state_get();
    
    for (size_t i = BOARD_H - 4; i < BOARD_H; ++i) {
        for (size_t j = BOARD_W - 4; j < BOARD_W; ++j) {
            game_state.board[i][j] = 1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, start_time);
    game_state_clear_lines(&game_state);
    clock_gettime(CLOCK_MONOTONIC, end_time);
}
