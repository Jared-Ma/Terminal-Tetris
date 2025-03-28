#ifndef STATS_H
#define STATS_H
#include "game_state.h"

#include <stdint.h>


struct Stats {
    float game_time_s;
    float real_time_s;
    float score_per_s;
    float piece_per_s;
    uint32_t num_pieces;
    uint32_t num_single;
    uint32_t num_double;
    uint32_t num_triple;
    uint32_t num_tetris;
    uint64_t frame_count;
    float fps;
};

typedef struct Stats Stats;

Stats stats_get(void);

Stats *stats_init(void);

void stats_destroy(Stats* stats);

void stats_debug_print(const Stats* stats);

void stats_reset(Stats* stats);

void stats_update(Stats* stats, const GameState* game_state);

#endif
