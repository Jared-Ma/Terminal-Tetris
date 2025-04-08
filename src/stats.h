#ifndef STATS_H
#define STATS_H
#include "game_state.h"

#include <stdint.h>

/** @file
 ** @brief Collection of functions to interface with the Stats object.
 **/


/** 
 ** @brief Stats consists of auxillary game statistics.
 **/
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

/** 
 ** @brief Initialize the Stats object.
 **
 ** @return The initialized Stats object.
 **/
Stats stats_get(void);

/** 
 ** @brief Allocate memory and initialize a Stats object.
 **
 ** @return A pointer to the allocated Stats object.
 **/
Stats* stats_init(void);

/** 
 ** @brief Deallocate the Stats object @stats.
 **
 ** @param stats The Stats object to be deallocated.
 **/
void stats_destroy(Stats* stats);

/** 
 ** @brief Print values of each member in @stats.
 **
 ** @param stats The Stats object to be read.
 **/
void stats_debug_print(const Stats* stats);

/** 
 ** @brief Reset values of @stats to what they were on initialization.
 **
 ** @param stats The Stats object to be reset.
 **/
void stats_reset(Stats* stats);

/** 
 ** @brief Update values of @stats according to @game_state.
 **
 ** @param stats The Stats object to be modified.
 ** @param game_state The GameState object to be read.
 **/
void stats_update(Stats* stats, const GameState* game_state);

#endif
