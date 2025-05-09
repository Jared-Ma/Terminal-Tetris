#include "test_stats.h"
#include "stats.h"
#include "game_state.h"

#include "assert_trace.h"

#include <stdbool.h>
#include <stdio.h>


bool test_stats_get(void) {
    Stats stats = stats_get();
    ASSERT(stats.game_time_s == 0.0);
    ASSERT(stats.real_time_s == 0.0);
    ASSERT(stats.score_per_s == 0.0);
    ASSERT(stats.piece_per_s == 0.0);
    ASSERT(stats.num_pieces == 0);
    ASSERT(stats.num_single == 0);
    ASSERT(stats.num_double == 0);
    ASSERT(stats.num_triple == 0);
    ASSERT(stats.num_tetris == 0);
    ASSERT(stats.frame_count == 0);
    ASSERT(stats.fps == 0.0);
    return true;
}

bool test_stats_init(void) {
    Stats* stats = stats_init();
    ASSERT(stats->game_time_s == 0.0);
    ASSERT(stats->real_time_s == 0.0);
    ASSERT(stats->score_per_s == 0.0);
    ASSERT(stats->piece_per_s == 0.0);
    ASSERT(stats->num_pieces == 0);
    ASSERT(stats->num_single == 0);
    ASSERT(stats->num_double == 0);
    ASSERT(stats->num_triple == 0);
    ASSERT(stats->num_tetris == 0);
    ASSERT(stats->frame_count == 0);
    ASSERT(stats->fps == 0.0);
    stats_destroy(stats);
    return true;
}

bool test_stats_reset(void) {
    Stats stats = stats_get();
    stats.game_time_s = 1.0;
    stats.real_time_s = 1.0;
    stats.score_per_s = 2.0;
    stats.piece_per_s = 3.0;
    stats.num_pieces = 4;
    stats.num_single = 5;
    stats.num_double = 6;
    stats.num_triple = 7;
    stats.num_tetris = 8;
    stats.frame_count = 9;
    stats.fps = 10.0;
    stats_reset(&stats);
    ASSERT(stats.game_time_s == 0.0);
    ASSERT(stats.real_time_s == 0.0);
    ASSERT(stats.score_per_s == 0.0);
    ASSERT(stats.piece_per_s == 0.0);
    ASSERT(stats.num_pieces == 0);
    ASSERT(stats.num_single == 0);
    ASSERT(stats.num_double == 0);
    ASSERT(stats.num_triple == 0);
    ASSERT(stats.num_tetris == 0);
    ASSERT(stats.frame_count == 0);
    ASSERT(stats.fps == 0.0);
    return true;
}

bool test_stats_update(void) {
    Stats stats = stats_get();
    GameState game_state = game_state_get();

    stats.game_time_s = 2.0;
    game_state.score = 100;
    stats.num_pieces = 6;
    game_state.last_locked_piece_shape = I;
    game_state.last_action_num_lines = 1;

    stats_update(&stats, &game_state);

    ASSERT(stats.score_per_s == 50.0);
    ASSERT(stats.piece_per_s == 3.5);
    ASSERT(stats.num_pieces == 7);
    ASSERT(stats.num_single == 1);
    return true;
}
