#include <stdbool.h>
#include <time.h>
#include "stats.h"
#include "logger.h"


Stats stats_get(void) {
    Stats stats = {
        .seconds = 0,
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
    if (!stats) {
        return;
    }
    fprintf(
        debug_log,
        "%p = {\n"
        "\tseconds = %lf\n"
        "\tframe_count = %lu\n"
        "\tfps = %lf\n"
        "}\n",
        stats,
        stats->seconds,
        stats->frame_count,
        stats->fps
    );
}

void stats_reset(Stats* stats) {
    if (!stats) {
        return;
    }
    *stats = stats_get();
}
