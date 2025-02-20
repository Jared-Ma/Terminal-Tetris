#include <stdio.h>
#include <stdbool.h>
#include "utils/assert_trace.h"
#include "stats.h"


bool test_stats_get(void) {
    Stats stats = stats_get();
    ASSERT(stats.time == 0);
    ASSERT(stats.frame_count == 0);
    ASSERT(stats.fps == 0.0);
    return true;
}

bool test_stats_init(void) {
    Stats* stats = stats_init();
    ASSERT(stats->time == 0);
    ASSERT(stats->frame_count == 0);
    ASSERT(stats->fps == 0.0);
    stats_destroy(stats);
    return true;
}

bool test_stats_reset(void) {
    Stats stats = stats_get();
    stats.time = 1;
    stats.frame_count = 1;
    ASSERT(stats.time == 1);
    ASSERT(stats.time == 1);
    stats_reset(&stats);
    ASSERT(stats.time == 0);
    ASSERT(stats.frame_count == 0);
    return true;
}
