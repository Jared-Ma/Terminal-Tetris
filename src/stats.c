#include "stats.h"
#include "game_state.h"
#include "logger.h"

#include <stdlib.h>
#include <stdio.h>


Stats stats_get(void) {
    Stats stats = {
        .seconds = 0.0,
        .score_per_sec = 0.0,
        .piece_per_sec = 0.0,
        .num_pieces = 0,
        .num_single = 0,
        .num_double = 0,
        .num_triple = 0,
        .num_tetris = 0,
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

void stats_debug_print(const Stats* stats) {
    if (!stats) {
        return;
    }
    fprintf(
        debug_log,
        "%p = {\n"
        "\tseconds = %lf\n"
        "\tscore_per_sec = %lf\n"
        "\tpiece_per_sec = %lf\n"
        "\tnum_pieces = %lu\n"
        "\tnum_single = %lu\n"
        "\tnum_double = %lu\n"
        "\tnum_triple = %lu\n"
        "\tnum_tetris = %lu\n"
        "\tframe_count = %lu\n"
        "\tfps = %lf\n"
        "}\n",
        stats,
        stats->seconds,
        stats->score_per_sec,
        stats->piece_per_sec,
        stats->num_pieces,
        stats->num_single,
        stats->num_double,
        stats->num_triple,
        stats->num_tetris,
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

void stats_update(Stats* stats, const GameState* game_state) {
    if (!stats) {
        return;
    }

    if (game_state->last_locked_piece_shape > 0) {
        stats->num_pieces++;
    }

    if (stats->seconds > 0) {
        stats->score_per_sec = game_state->score / stats->seconds;
        stats->piece_per_sec = stats->num_pieces / stats->seconds;
        stats->fps = stats->frame_count / stats->seconds;
    }

    if (game_state->last_action_num_lines == 1) {
        stats->num_single++;
    } else if (game_state->last_action_num_lines == 2) {
        stats->num_double++;
    } else if (game_state->last_action_num_lines == 3) {
        stats->num_triple++;
    } else if (game_state->last_action_num_lines == 4) {
        stats->num_tetris++;
    }
}
