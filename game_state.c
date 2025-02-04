#include <stdlib.h>
#include "game_state.h"
#include "piece.h"
#include "logger.h"


GameState game_state_get() {
    GameState game_state = {
        .curr_piece = NULL,
        .next_piece = NULL,
        .hold_piece = NULL,
        .board = {{ 0 }},
    };
    return game_state;
}

GameState* game_state_init() {
    GameState* game_state = malloc(sizeof(GameState));
    *game_state = game_state_get();
    return game_state;
}

void game_state_destroy(GameState* game_state) {
    if (game_state) {
        *game_state = (GameState){ 0 };
        free(game_state);
    }
}

void game_state_debug_print(GameState* game_state) {
    if (game_state) {
        fprintf(
            debug_log,
            "%p = {\n"
            "\tcurr_piece = ",
            game_state
        );
        piece_debug_print(game_state->curr_piece);
        fprintf(
            debug_log,
            "\tnext_piece = "
        );
        piece_debug_print(game_state->next_piece);
        fprintf(
            debug_log,
            "\thold_piece = "
        );
        piece_debug_print(game_state->hold_piece);
        fprintf(
            debug_log,
            "\tboard = \n"
        );
        for (size_t i = 0; i < BOARD_H; ++i) {
            fprintf(debug_log, "\t\t[ ");
            for (size_t j = 0; j < BOARD_W; ++j) {
                fprintf(debug_log, "%i ", game_state->board[i][j]);
            }
            fprintf(debug_log, "]\n");
        }
        fprintf(debug_log, "}\n");
    }
}
