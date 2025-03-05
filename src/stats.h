#ifndef STATS_H
#define STATS_H
#include <stdlib.h>
#include <stdbool.h>


struct Stats {
    double seconds;
    size_t frame_count;
    double fps;
};

typedef struct Stats Stats;

Stats stats_get(void);

Stats *stats_init(void);

void stats_destroy(Stats* stats);

void stats_debug_print(Stats* stats);

void stats_reset(Stats* stats);

#endif
