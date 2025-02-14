#include <stdbool.h>
#include <time.h>
#include "stats.h"
#include "logger.h"


Stats stats_get(void) {
    Stats stats = {
        .time = 0,
        .score = 0,
        .lines = 0,
        .level = 1,
        .combo = -1,
        .prev_clear_difficult = 0,
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
    if (stats) {
        *stats = (Stats){ 0 };
        free(stats);
        stats = NULL;
    }
}

void stats_debug_print(Stats* stats) {
    if (stats) {
        fprintf(
            debug_log,
            "%p = {\n"
            "\ttime = %lu\n"
            "\tscore = %lu\n"
            "\tlines = %lu\n"
            "\tlevel = %lu\n"
            "\tcombo = %i\n"
            "\tprev_clear_difficult = %i\n"
            "\tframe_count = %lu\n"
            "\tfps = %lf\n"
            "}\n",
            stats,
            stats->time,
            stats->score,
            stats->lines,
            stats->level,
            stats->combo,
            stats->prev_clear_difficult,
            stats->frame_count,
            stats->fps
        );
    }
}

void stats_restart(Stats* stats) {
    if (stats) {
        *stats = stats_get();
    }
}

void stats_update_time(Stats* stats, double seconds) {
    if (stats) {
        stats->time += seconds;
    }
}

size_t stats_calc_points(Stats* stats, size_t lines_cleared) {
    size_t points = 0;
    
    if (stats) {
        if (lines_cleared == 1) {
            points += SINGLE_MULT * stats->level;
            stats_set_prev_clear_difficult(stats, false);
        } else if (lines_cleared == 2) {
            points += DOUBLE_MULT * stats->level;
            stats_set_prev_clear_difficult(stats, false);
        } else if (lines_cleared == 3) {
            points += TRIPLE_MULT * stats->level;
            stats_set_prev_clear_difficult(stats, false);
        } else if (lines_cleared == 4) {
            points += TETRIS_MULT * stats->level;
            if (stats->prev_clear_difficult) {
                points *= 1.5;
            }
            stats_set_prev_clear_difficult(stats, true);
        }

        if (stats->combo > 0) {
            points += COMBO_MULT * stats->combo * stats->level;
        }
    }

    return points;
}

void stats_update_score(Stats* stats, size_t points) {
    if (stats) {
        stats->score += points;
        fprintf(debug_log, "points: %lu\n", points);
        fprintf(debug_log, "score: %lu\n", stats->score);
    }
}

void stats_increment_lines(Stats* stats) {
    if (stats) {
        stats->lines++;
    }
}

void stats_increment_level(Stats* stats) {
    if (stats) {
        stats->level++;
    }
}

void stats_reset_combo(Stats* stats) {
    if (stats) {
        stats->combo = -1;
    }
}

void stats_increment_combo(Stats* stats) {
    if (stats) {
        stats->combo++;
    }
}

void stats_set_prev_clear_difficult(Stats* stats, bool value) {
    if (stats) {
        stats->prev_clear_difficult = value;
    }
}

void stats_increment_frame_count(Stats* stats) {
    if (stats) {
        stats->frame_count++;
    }
}
