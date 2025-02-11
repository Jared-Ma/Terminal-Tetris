#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game_state.h"
#include "piece.h"
#include "logger.h"


const int SRS_TABLE[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS] = {
    {{0, 0}, {-1, 0}, {-1, +1}, {0, -2}, {-1, -2}},
    {{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
    {{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
    {{0, 0}, {-1 ,0}, {-1, +1}, {0, -2}, {-1, -2}},
    {{0, 0}, {+1, 0}, {+1, +1}, {0, -2}, {+1, -2}},
    {{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
    {{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
    {{0, 0}, {+1, 0}, {+1, +1}, {0, -2}, {+1, -2}}
};

const int SRS_TABLE_I[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS] = {
    {{0, 0}, {-2, 0}, {+1, 0}, {-2, -1}, {+1, +2}},
    {{0, 0}, {+2, 0}, {-1, 0}, {+2, +1}, {-1, -2}},
    {{0, 0}, {-1, 0}, {+2, 0}, {-1, +2}, {+2, -1}},
    {{0, 0}, {+1 ,0}, {-2, 0}, {+1, -2}, {-2, +1}},
    {{0, 0}, {+2, 0}, {-1, 0}, {+2, +1}, {-1, -2}},
    {{0, 0}, {-2, 0}, {+1, 0}, {-2, -1}, {+1, +2}},
    {{0, 0}, {+1, 0}, {-2, 0}, {+1, -2}, {-2, +1}},
    {{0, 0}, {-1, 0}, {+2, 0}, {-1, +2}, {+2, -1}}
};

const int SRS_TABLE_O[SRS_NUM_ROTATIONS][SRS_NUM_TESTS][SRS_NUM_COORDS] = {
    {{0, +1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{+1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{-1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, +1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{-1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{+1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
};

const int SPAWN_Y = 1;
const int SPAWN_X = (BOARD_W - 1) / 2;

GameState game_state_get() {
    GameState game_state = {
        .curr_piece = { 0 },
        .hold_piece = { 0 },
        .next_piece = { 0 },
        .ghost_piece = { 0 },
        .holding_piece = false,
        .hold_allowed = true,
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
    game_state->next_piece = piece_get(game_state->next_shapes[game_state->next_index], SPAWN_Y, SPAWN_X);
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

void game_state_restart(GameState* game_state) {
    *game_state = game_state_get();
    game_state_gen_next_shapes(game_state);
    game_state->next_piece = piece_get(game_state->next_shapes[game_state->next_index], SPAWN_Y, SPAWN_X);
    game_state_load_next_piece(game_state);
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
            "\tholding_piece = %i\n"
            "\tnext_index = %lu\n"
            "\tnext_shapes = ",
            game_state->holding_piece,
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
    game_state->next_piece = piece_get(game_state->next_shapes[game_state->next_index], SPAWN_Y, SPAWN_X);
    game_state_update_ghost_piece(game_state);
}

void game_state_hold_piece(GameState* game_state) {
    if (game_state->hold_allowed) {
        if (game_state->holding_piece) {
            Piece tmp;
            tmp = game_state->curr_piece;
            game_state->curr_piece = game_state->hold_piece;
            game_state->hold_piece = tmp;
            game_state_update_ghost_piece(game_state);
        } else {
            game_state->hold_piece = game_state->curr_piece;
            game_state->holding_piece = true;
            game_state_load_next_piece(game_state);
        }
        game_state->hold_piece.r = 0;
        game_state->hold_piece.y = SPAWN_Y;
        game_state->hold_piece.x = SPAWN_X;
        game_state->hold_allowed = false;
    }
}

bool game_state_check_collision(GameState* game_state, Piece piece) {
    int top_left_y = piece.y - piece.n / 2; 
    int top_left_x = piece.x - piece.n / 2;

    for (size_t i = 0; i < piece.n; ++i) {
        for (size_t j = 0; j < piece.n; ++j) {
            if (piece.M[piece.r][i][j] == 1) {
                if (
                    top_left_y + i < 0 || top_left_y + i > BOARD_H - 1 || 
                    top_left_x + j < 0 || top_left_x + j > BOARD_W - 1 ||
                    game_state->board[top_left_y + i][top_left_x + j] > 0
                ) {
                    return true;
                }
            }
        }
    }
    return false;
}

void game_state_move_curr_piece(GameState* game_state, int y, int x) {
    Piece test_piece = game_state->curr_piece;
    test_piece.y = y;
    test_piece.x = x;
    if (!game_state_check_collision(game_state, test_piece)) {
        piece_move(&game_state->curr_piece, y, x);
        game_state_update_ghost_piece(game_state);
    } 
}

void game_state_rotate_curr_piece_srs(GameState* game_state, Rotation rotation) {
    Piece curr_piece_copy = game_state->curr_piece;

    size_t r_index;
    if (rotation == RIGHT) {
        r_index = 2 * game_state->curr_piece.r;
    } else {
        r_index = SRS_NUM_ROTATIONS - 1;
        r_index -= (game_state->curr_piece.r > 0) ? 2*(R_MAX - game_state->curr_piece.r) : 0;
    }

    for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {
        if (game_state->curr_piece.shape == I) {
            piece_move(
                &game_state->curr_piece, 
                game_state->curr_piece.y - SRS_TABLE_I[r_index][i][1], 
                game_state->curr_piece.x + SRS_TABLE_I[r_index][i][0]
            );
        } else if (game_state->curr_piece.shape == O) {
            piece_move(
                &game_state->curr_piece, 
                game_state->curr_piece.y - SRS_TABLE_O[r_index][i][1], 
                game_state->curr_piece.x + SRS_TABLE_O[r_index][i][0]
            );
        } else {
            piece_move(
                &game_state->curr_piece, 
                game_state->curr_piece.y - SRS_TABLE[r_index][i][1], 
                game_state->curr_piece.x + SRS_TABLE[r_index][i][0]
            );
        }
        game_state_rotate_curr_piece(game_state, rotation);
        if (game_state->curr_piece.r != curr_piece_copy.r) {
            game_state_update_ghost_piece(game_state);
            return;
        }
        game_state->curr_piece = curr_piece_copy;
    }
}

void game_state_rotate_curr_piece(GameState* game_state, Rotation rotation) {
    Piece test_piece = game_state->curr_piece;
    test_piece.r = compute_r_index(game_state->curr_piece.r, rotation);
    if (!game_state_check_collision(game_state, test_piece)) {
        piece_rotate(&game_state->curr_piece, rotation);
    } 
}

void game_state_place_curr_piece(GameState* game_state) {
    int top_left_y = game_state->curr_piece.y - game_state->curr_piece.n / 2; 
    int top_left_x = game_state->curr_piece.x - game_state->curr_piece.n / 2;

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1) {
                game_state->board[top_left_y + i][top_left_x + j] = game_state->curr_piece.shape;
            }
        }
    }
    
    game_state->hold_allowed = true;
}

void game_state_apply_gravity(GameState* game_state, size_t row, size_t num_lines) {
    for (size_t i = row; i >= num_lines; --i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state->board[i][j] = game_state->board[i - num_lines][j];
            game_state->board[i - num_lines][j] = 0;
        }
    }
}

void game_state_clear_line(GameState* game_state, size_t row) {
    for (size_t i = 0; i < BOARD_W; ++i) {
        game_state->board[row][i] = 0;
    }
}

void game_state_clear_lines(GameState* game_state) {
    size_t num_lines = 0;
    for (size_t i = 0; i < BOARD_H; ++i) {
        bool line = true;
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (game_state->board[i][j] == 0) {
                line = false;
                break;
            }
        }
        if (line) {
            game_state_clear_line(game_state, i);
            num_lines++;
        } else if (num_lines > 0) {
            game_state_apply_gravity(game_state, i-1, num_lines);
            num_lines = 0;
        }
    }

    if (num_lines > 0) {
        game_state_apply_gravity(game_state, BOARD_H - 1, num_lines);
    }
}

void game_state_drop_curr_piece(GameState* game_state) {
    for (size_t y = game_state->curr_piece.y + 1; y < BOARD_H; ++y) {
        Piece prev_piece = game_state->curr_piece;
        game_state_move_curr_piece(game_state, y, game_state->curr_piece.x);
        if (game_state->curr_piece.y == prev_piece.y) {
            break;
        }
    }
    game_state_place_curr_piece(game_state);
}

void game_state_move_ghost_piece(GameState* game_state, int y, int x) {
    Piece test_piece = game_state->ghost_piece;
    test_piece.y = y;
    test_piece.x = x;
    if (!game_state_check_collision(game_state, test_piece)) {
        piece_move(&game_state->ghost_piece, y, x);
    } 
}

void game_state_update_ghost_piece(GameState* game_state) {
    game_state->ghost_piece = game_state->curr_piece;
    for (size_t y = game_state->ghost_piece.y + 1; y < BOARD_H; ++y) {
        Piece prev_piece = game_state->ghost_piece;
        game_state_move_ghost_piece(game_state, y, game_state->ghost_piece.x);
        if (game_state->ghost_piece.y == prev_piece.y) {
            return;
        }
    }
}

bool game_state_check_top_out(GameState* game_state) {
    int top_left_y = game_state->curr_piece.y - game_state->curr_piece.n / 2; 
    int top_left_x = game_state->curr_piece.x - game_state->curr_piece.n / 2;

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (
                game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1 &&
                game_state->board[top_left_y + i][top_left_x + j] > 0
            ) {
                return true;
            }
        }
    }

    return false;
}
