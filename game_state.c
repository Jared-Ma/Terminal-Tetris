#include <stdlib.h>
#include <time.h>
#include "game_state.h"
#include "piece.h"
#include "logger.h"


GameState game_state_get() {
    GameState game_state = {
        .curr_piece = { 0 },
        .hold_piece = { 0 },
        .next_piece = { 0 },
        .next_index = 0,
        .next_shapes = { 0 },
        .board = {{ 0 }}
    };
    return game_state;
}

GameState* game_state_init() {
    GameState* game_state = malloc(sizeof(GameState));
    *game_state = game_state_get();
    game_state_gen_next_shapes(game_state);
    game_state->next_piece = piece_get(game_state->next_shapes[game_state->next_index], 3, 3);
    game_state_load_next_piece(game_state);
    return game_state;
}

void game_state_destroy(GameState* game_state) {
    if (game_state) {
        *game_state = (GameState){ 0 };
        free(game_state);
        game_state = NULL;
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
        piece_debug_print(&game_state->curr_piece);
        fprintf(
            debug_log,
            "\thold_piece = "
        );
        piece_debug_print(&game_state->hold_piece);
        fprintf(
            debug_log,
            "\tnext_piece = "
        );
        piece_debug_print(&game_state->next_piece);
        fprintf(
            debug_log,
            "\tnext_index = %u\n"
            "\tnext_shapes = ",
            game_state->next_index
        );
        fprintf(debug_log, "[ ");
        for (size_t i = 0; i < NUM_SHAPES; ++i) {
            fprintf(debug_log, "%c ", shape_to_char(game_state->next_shapes[i]));
        }
        fprintf(debug_log, "]\n");
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

void game_state_gen_next_shapes(GameState* game_state) {
    srand(time(0));
    Shape random_shapes[NUM_SHAPES] = {I, J, L, O, S, T, Z};
    for (size_t i = NUM_SHAPES-1; i > 0; --i) {
        size_t j = rand() % (i+1);
        Shape temp = random_shapes[i];
        random_shapes[i] = random_shapes[j];
        random_shapes[j] = temp;
    }
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        game_state->next_shapes[i] = random_shapes[i];
    }
}

void game_state_load_next_piece(GameState* game_state) {
    game_state->curr_piece = game_state->next_piece;
    game_state->next_index++;
    if (game_state->next_index == NUM_SHAPES) {
        game_state->next_index = game_state->next_index % NUM_SHAPES;
        game_state_gen_next_shapes(game_state);
    }
    game_state->next_piece = piece_get(game_state->next_shapes[game_state->next_index], 3, 3);
}
