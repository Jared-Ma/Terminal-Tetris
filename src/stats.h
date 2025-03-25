#ifndef STATS_H
#define STATS_H
#include "game_state.h"

#include <stdint.h>


struct Stats {
    double seconds;
    double score_per_sec;
    double piece_per_sec;
    uint64_t num_pieces;
    uint64_t num_single;
    uint64_t num_double;
    uint64_t num_triple;
    uint64_t num_tetris;
    uint64_t frame_count;
    double fps;
};

typedef struct Stats Stats;

Stats stats_get(void);

Stats *stats_init(void);

void stats_destroy(Stats* stats);

void stats_debug_print(const Stats* stats);

void stats_reset(Stats* stats);

void stats_update(Stats* stats, const GameState* game_state);

#endif
