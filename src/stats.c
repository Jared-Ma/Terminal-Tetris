#include <stdbool.h>
#include <time.h>
#include "stats.h"
#include "logger.h"


Stats stats_get(void) {
    Stats stats = {
        .time = 0,
        .frame_count = 0,
        .fps = 0.0
    };
    return stats;
}

Stats* stats_init(void) {
    Stats* stats = malloc(sizeof(Stats));
    *stats = stats_get();
    return stats;
}

void stats_destroy(Stats* stats) {
    if (!stats) {
        return;
    }
    *stats = (Stats){ 0 };
    free(stats);
}

void stats_debug_print(Stats* stats) {
    if (stats) {
        fprintf(
            debug_log,
            "%p = {\n"
            "\ttime = %lu\n"
            "\tframe_count = %lu\n"
            "\tfps = %lf\n"
            "}\n",
            stats,
            stats->time,
            stats->frame_count,
            stats->fps
        );
    }
}

void stats_reset(Stats* stats) {
    if (!stats) {
        return;
    }
    *stats = stats_get();
}

void stats_increase_time(Stats* stats, double seconds) {
    if (!stats) {
        return;    
    }
    stats->time += seconds;
}

void stats_increment_frame_count(Stats* stats) {
    if (!stats) {
        return;
    }
    stats->frame_count++;
}
