#include "test_stats.h"
#include "stats.h"

#include "assert_trace.h"

#include <stdbool.h>
#include <stdio.h>


bool test_stats_get(void) {
    Stats stats = stats_get();
    ASSERT(stats.seconds == 0.0);
    ASSERT(stats.frame_count == 0);
    ASSERT(stats.fps == 0.0);
    return true;
}

bool test_stats_init(void) {
    Stats* stats = stats_init();
    ASSERT(stats->seconds == 0.0);
    ASSERT(stats->frame_count == 0);
    ASSERT(stats->fps == 0.0);
    stats_destroy(stats);
    return true;
}

bool test_stats_reset(void) {
    Stats stats = stats_get();
    stats.seconds = 1;
    stats.frame_count = 1;
    stats_reset(&stats);
    ASSERT(stats.seconds == 0.0);
    ASSERT(stats.frame_count == 0);
    return true;
}
