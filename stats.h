#ifndef STATS_H
#define STATS_H
#include <stdlib.h>
#include <stdbool.h>

#define SINGLE_MULT 100
#define DOUBLE_MULT 300
#define TRIPLE_MULT 500
#define TETRIS_MULT 800
#define COMBO_MULT 50


struct Stats {
    size_t time;
    size_t score;
    size_t lines;
    size_t level;
    int combo;
    bool prev_clear_difficult;
    size_t frame_count;
    double fps;
};

typedef struct Stats Stats;

Stats stats_get(void);

Stats *stats_init(void);

void stats_destroy(Stats* stats);

void stats_debug_print(Stats* stats);

void stats_restart(Stats* stats);

void stats_update_time(Stats* stats, double seconds);

size_t stats_calc_points(Stats* stats, size_t lines_cleared);

void stats_update_score(Stats* stats, size_t points);

void stats_increment_lines(Stats* stats);

void stats_increment_level(Stats* stats);

void stats_reset_combo(Stats* stats);

void stats_increment_combo(Stats* stats);

void stats_set_prev_clear_difficult(Stats* stats, bool value);

void stats_increment_frame_count(Stats* stats);

#endif
