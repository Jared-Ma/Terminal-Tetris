#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
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

const float GRAVITY_TABLE[MAX_GRAVITY_LEVEL] = {
    0.016667, 
    0.021017, 
    0.026977, 
    0.035256, 
    0.046922,
    0.063612, 
    0.087869, 
    0.123700, 
    0.177527, 
    0.259801, 
    0.387811, 
    0.590646, 
    0.918105, 
    1.456960, 
    2.361181
};

GameState game_state_get(void) {
    GameState game_state = {
        .curr_piece = { 0 },
        .hold_piece = { 0 },
        .next_piece = { 0 },
        .ghost_piece = { 0 },
        .holding_piece = false,
        .hold_allowed = true,
        .next_index = 0,
        .next_queue = { 0 },
        .board = {{ 0 }},
        .score = 0,
        .level = 1,
        .lines = 0,
        .combo = -1,
        .prev_clear_difficult = false,
        .curr_clear_difficult = false,
        .prev_clear_perfect_tetris = false,
        .t_rotation_test_num = 0,
        .lock_delay_timer = LOCK_DELAY,
        .move_reset_count = 0,
        .gravity_value = 0.0,
        .soft_drop = false
    };
    return game_state;
}

GameState* game_state_init(void) {
    GameState* game_state = malloc(sizeof(GameState));
    *game_state = game_state_get();
    game_state_gen_next_queue(game_state);
    game_state->next_piece = piece_get(game_state->next_queue[game_state->next_index], SPAWN_Y, SPAWN_X);
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
    game_state_gen_next_queue(game_state);
    game_state->next_piece = piece_get(game_state->next_queue[game_state->next_index], SPAWN_Y, SPAWN_X);
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
            "\tnext_index = %u\n"
            "\tnext_shapes = ",
            game_state->holding_piece,
            game_state->next_index
        );
        fprintf(debug_log, "[ ");
        for (size_t i = 0; i < NUM_SHAPES; ++i) {
            fprintf(debug_log, "%c ", shape_to_char(game_state->next_queue[i]));
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
        fprintf(
            debug_log,
            "\tscore = %lu\n"
            "\tlevel = %u\n"
            "\tlines = %lu\n"
            "\tcombo = %i\n"
            "\tprev_clear_difficult = %i\n"
            "\tcurr_clear_difficult = %i\n"
            "\tprev_clear_perfect_tetris = %i\n"
            "\tt_rotation_test_num = %i\n"
            "\tlock_delay_timer = %u\n"
            "\tmove_reset_count = %u\n"
            "\tgravity_value = %f\n"
            "\tsoft_drop = %i\n",
            game_state->score,
            game_state->level,
            game_state->lines,
            game_state->combo,
            game_state->prev_clear_difficult,
            game_state->curr_clear_difficult,
            game_state->prev_clear_perfect_tetris,
            game_state->t_rotation_test_num,
            game_state->lock_delay_timer,
            game_state->move_reset_count,
            game_state->gravity_value,
            game_state->soft_drop
        );
        fprintf(debug_log, "}\n");
    }
}

void game_state_gen_next_queue(GameState* game_state) {
    srand(time(0));
    Shape random_shapes[NUM_SHAPES] = {I, J, L, O, S, T, Z};
    for (size_t i = NUM_SHAPES-1; i > 0; --i) {
        size_t j = rand() % (i+1);
        Shape temp = random_shapes[i];
        random_shapes[i] = random_shapes[j];
        random_shapes[j] = temp;
    }
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        game_state->next_queue[i] = random_shapes[i];
    }
}

void game_state_load_next_piece(GameState* game_state) {
    game_state->curr_piece = game_state->next_piece;
    game_state->next_index++;
    if (game_state->next_index == NUM_SHAPES) {
        game_state->next_index = game_state->next_index % NUM_SHAPES;
        game_state_gen_next_queue(game_state);
    }
    game_state->next_piece = piece_get(game_state->next_queue[game_state->next_index], SPAWN_Y, SPAWN_X);
    
    // Reset curr piece properties
    game_state_update_ghost_piece(game_state);
    game_state_reset_move_reset_count(game_state);
    game_state_reset_gravity_value(game_state);
    game_state_set_t_rotation_test_num(game_state, 0);
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
        if (game_state->lock_delay_timer < LOCK_DELAY && game_state->move_reset_count < MAX_MOVE_RESET) {
            game_state_reset_lock_delay_timer(game_state);
            game_state_increment_move_reset_count(game_state);
        }
        if (game_state->curr_piece.shape == T) {
            game_state_set_t_rotation_test_num(game_state, 0);
        }
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
            if (game_state->lock_delay_timer < LOCK_DELAY && game_state->move_reset_count < MAX_MOVE_RESET) {
                game_state_reset_lock_delay_timer(game_state);
                game_state_increment_move_reset_count(game_state);
            }
            if (game_state->curr_piece.shape == T) {
                game_state_set_t_rotation_test_num(game_state, i+1);
            }
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

void game_state_lock_curr_piece(GameState* game_state) {
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

void game_state_apply_stack_gravity(GameState* game_state, size_t row) {
    for (size_t i = row; i >= 1; --i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state->board[i][j] = game_state->board[i-1][j];
            game_state->board[i-1][j] = 0;
        }
    }
}

void game_state_clear_line(GameState* game_state, size_t row) {
    for (size_t i = 0; i < BOARD_W; ++i) {
        game_state->board[row][i] = 0;
    }
}

void game_state_clear_lines(GameState* game_state) {
    size_t rows[4];
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
            rows[num_lines++] = i;
        }
    }

    size_t points = 0;
    points += game_state_calc_t_spin_points(game_state, num_lines);
    points += game_state_calc_line_clear_points(game_state, num_lines);

    // clear lines from board and apply stack gravity
    for (size_t i = 0; i < num_lines; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state->board[rows[i]][j] = 0;
        }
        game_state_apply_stack_gravity(game_state, rows[i]);
    }

    points += game_state_calc_perfect_clear_points(game_state, num_lines);
    points += game_state_calc_combo_points(game_state, num_lines);
    points *= game_state_calc_difficult_clear_mult(game_state, num_lines);

    game_state_increase_score(game_state, points);
    game_state_increase_lines(game_state, num_lines);
    game_state_set_prev_clear_difficult(game_state, game_state->curr_clear_difficult);
}

void game_state_hard_drop_curr_piece(GameState* game_state) {
    int prev_y = game_state->curr_piece.y;

    for (size_t y = game_state->curr_piece.y + 1; y < BOARD_H; ++y) {
        Piece prev_piece = game_state->curr_piece;
        game_state_move_curr_piece(game_state, y, game_state->curr_piece.x);
        if (game_state->curr_piece.y == prev_piece.y) {
            break;
        }
    }

    game_state_increase_score(game_state, HARD_DROP_MULT*(game_state->curr_piece.y - prev_y));
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

bool game_state_check_curr_piece_grounded(GameState* game_state) {
    int top_left_y = game_state->curr_piece.y - game_state->curr_piece.n / 2; 
    int top_left_x = game_state->curr_piece.x - game_state->curr_piece.n / 2;

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1) {
                if (
                    top_left_y + i + 1 > BOARD_H - 1 ||
                    game_state->board[top_left_y + i + 1][top_left_x + j] > 0
                ) {
                    return true;
                }
            }
        }
    }

    return false;
}

size_t game_state_calc_t_spin_points(GameState* game_state, size_t num_lines) {
    size_t points = 0;

    if (game_state_check_t_spin(game_state)) {
        if (num_lines == 0) {
            points += T_SPIN_ZERO_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, game_state->prev_clear_difficult);
        } else if (num_lines == 1) {
            points += T_SPIN_SINGLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        } else if (num_lines == 2) {
            points += T_SPIN_DOUBLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        } else if (num_lines == 3) {
            points += T_SPIN_TRIPLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        }
    } else if (game_state_check_t_spin_mini(game_state)) {
        if (num_lines == 0) {
            points += T_SPIN_MINI_ZERO_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        } else if (num_lines == 1) {
            points += T_SPIN_MINI_SINGLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        } else if (num_lines == 2) {
            points += T_SPIN_MINI_DOUBLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        }
    }

    return points;
}

size_t game_state_calc_line_clear_points(GameState* game_state, size_t num_lines) {
    size_t points = 0;

    if (!game_state_check_t_spin(game_state) && !game_state_check_t_spin_mini(game_state)) {
        if (num_lines == 1) {
            points += SINGLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, false);
        } else if (num_lines == 2) {
            points += DOUBLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, false);
        } else if (num_lines == 3) {
            points += TRIPLE_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, false);
        } else if (num_lines == 4) {
            points += TETRIS_MULT * game_state->level;
            game_state_set_curr_clear_difficult(game_state, true);
        }
    }

    return points;
}

size_t game_state_calc_perfect_clear_points(GameState* game_state, size_t num_lines) {
    size_t points = 0;

    if (game_state_check_empty_board(game_state)) {
        if (num_lines == 1) {
            points += SINGLE_PERFECT_CLEAR_MULT * game_state->level;
        } else if (num_lines == 2) {
            points += DOUBLE_PERFECT_CLEAR_MULT * game_state->level;
        } else if (num_lines == 3) {
            points += TRIPLE_PERFECT_CLEAR_MULT * game_state->level;
        } else if (num_lines == 4) {
            if (game_state->prev_clear_perfect_tetris) {
                points += B2B_TETRIS_PERFECT_CLEAR_MULT * game_state->level;
            } else {
                points += TETRIS_PERFECT_CLEAR_MULT * game_state->level;
            }
        }
    } 

    if (game_state_check_empty_board(game_state) && num_lines == 4) {
        game_state_set_prev_clear_perfect_tetris(game_state, true);
    } else if (num_lines > 0) {
        game_state_set_prev_clear_perfect_tetris(game_state, false);
    }

    return points;
}

size_t game_state_calc_combo_points(GameState* game_state, size_t num_lines) {
    size_t points = 0;

    if (num_lines > 0) {
        game_state_increment_combo(game_state);
        points += COMBO_MULT * game_state->combo * game_state->level;
    } else {
        game_state_reset_combo(game_state);
    }

    return points;
}

float game_state_calc_difficult_clear_mult(GameState* game_state, size_t num_lines) {
    if (num_lines > 0 && game_state->prev_clear_difficult && game_state->curr_clear_difficult) {
        return B2B_DIFFICULT_CLEAR_MULT;
    }
    return 1.0;
}

void game_state_increase_score(GameState* game_state, size_t points) {
    if (game_state) {
        game_state->score += points;
    }
}

void game_state_increment_level(GameState* game_state) {
    if (game_state) {
        // game_state->level += (game_state->level < NUM_LEVELS) ? 1 : 0;
        game_state->level++;
    }
}

void game_state_increase_lines(GameState* game_state, size_t num_lines) {
    if (game_state) {
        game_state->lines += num_lines;
        if (game_state->lines >= game_state->level * LEVEL_LINE_REQ) {
            game_state_increment_level(game_state);
        }
    }
}

void game_state_reset_combo(GameState* game_state) {
    if (game_state) {
        game_state->combo = -1;
    }
}

void game_state_increment_combo(GameState* game_state) {
    if (game_state) {
        game_state->combo++;
    }
}

void game_state_set_prev_clear_difficult(GameState* game_state, bool value) {
    if (game_state) {
        game_state->prev_clear_difficult = value;
    }
}

void game_state_set_curr_clear_difficult(GameState* game_state, bool value) {
    if (game_state) {
        game_state->curr_clear_difficult = value;
    }
}

void game_state_set_prev_clear_perfect_tetris(GameState* game_state, bool value) {
    if (game_state) {
        game_state->prev_clear_perfect_tetris = value;
    }
}

void game_state_reset_lock_delay_timer(GameState* game_state) {
    if (game_state) {
        game_state->lock_delay_timer = LOCK_DELAY;
    }
}

void game_state_decrement_lock_delay_timer(GameState* game_state) {
    if (game_state) {
        game_state->lock_delay_timer -= (game_state->lock_delay_timer > 0) ? 1 : 0;
    }
}

void game_state_reset_move_reset_count(GameState* game_state) {
    if (game_state) {
        game_state->move_reset_count = 0;
    }
}

void game_state_increment_move_reset_count(GameState* game_state) {
    if (game_state) {
        game_state->move_reset_count += (game_state->move_reset_count < MAX_MOVE_RESET) ? 1 : 0;
    }
}

void game_state_reset_gravity_value(GameState* game_state) {
    if (game_state) {
        game_state->gravity_value = 0;
    }
}

void game_state_increase_gravity_value(GameState* game_state, float value) {
    if (game_state) {
        game_state->gravity_value += value;
    }
}

void game_state_set_soft_drop(GameState* game_state, bool value) {
    if (game_state) {
        game_state->soft_drop = value;
    }
}

void game_state_apply_gravity(GameState* game_state) {
    if (game_state->level > MAX_GRAVITY_LEVEL) {
        game_state_increase_gravity_value(game_state, GRAVITY_TABLE[MAX_GRAVITY_LEVEL - 1]);
    } else {
        game_state_increase_gravity_value(game_state, GRAVITY_TABLE[game_state->level - 1]);
    }
    while (game_state->gravity_value >= 1.0) {
        game_state->gravity_value -= 1.0;
        game_state_move_curr_piece(game_state, game_state->curr_piece.y + 1, game_state->curr_piece.x);
    }
}

void game_state_soft_drop_curr_piece(GameState* game_state) {
    int prev_y = game_state->curr_piece.y;
    game_state_move_curr_piece(game_state, game_state->curr_piece.y + 1, game_state->curr_piece.x);
    game_state_increase_score(game_state, SOFT_DROP_MULT * (game_state->curr_piece.y - prev_y));
    game_state_set_soft_drop(game_state, true);
}

void game_state_apply_soft_drop_gravity(GameState* game_state) {
    int prev_y = game_state->curr_piece.y;
    if (game_state->level > MAX_GRAVITY_LEVEL) {
        game_state_increase_gravity_value(game_state, SOFT_DROP_GRAVITY_MULT * GRAVITY_TABLE[MAX_GRAVITY_LEVEL - 1]);
    } else {
        game_state_increase_gravity_value(game_state, SOFT_DROP_GRAVITY_MULT * GRAVITY_TABLE[game_state->level - 1]);
    }
    game_state_apply_gravity(game_state);
    game_state_increase_score(game_state, SOFT_DROP_MULT * (game_state->curr_piece.y - prev_y));
    game_state_set_soft_drop(game_state, false);
}

void game_state_set_t_rotation_test_num(GameState* game_state, uint8_t value) {
    if (game_state) {
        game_state->t_rotation_test_num = value;
    }
}

bool game_state_check_t_spin(GameState* game_state) {
    if (game_state->t_rotation_test_num > 0) {
        int top_left_y = game_state->curr_piece.y - game_state->curr_piece.n / 2; 
        int top_left_x = game_state->curr_piece.x - game_state->curr_piece.n / 2;

        bool top_left = false;
        bool top_right = false;
        bool bottom_left = false;
        bool bottom_right = false;

        if (
            top_left_y < 0 || top_left_y > BOARD_H - 1 || 
            top_left_x < 0 || top_left_x > BOARD_W - 1 ||
            game_state->board[top_left_y][top_left_x] > 0
        ) {
            top_left = true;
        }

        if (
            top_left_y < 0 || top_left_y > BOARD_H - 1 || 
            top_left_x + 2 < 0 || top_left_x + 2 > BOARD_W - 1 ||
            game_state->board[top_left_y][top_left_x + 2] > 0
        ) {
            top_right = true;
        }

        if (
            top_left_y + 2 < 0 || top_left_y + 2 > BOARD_H - 1 || 
            top_left_x < 0 || top_left_x > BOARD_W - 1 ||
            game_state->board[top_left_y + 2][top_left_x] > 0
        ) {
            bottom_left = true;
        }

        if (
            top_left_y + 2 < 0 || top_left_y + 2 > BOARD_H - 1 || 
            top_left_x + 2 < 0 || top_left_x + 2 > BOARD_W - 1 ||
            game_state->board[top_left_y + 2][top_left_x + 2] > 0
        ) {
            bottom_right = true;
        }

        if (game_state->curr_piece.r == 0) {
            if (top_left && top_right && (bottom_left || bottom_right)) {
                return true;
            }
        } else if (game_state->curr_piece.r == 1) {
            if (top_right && bottom_right && (top_left || bottom_left)) {
                return true;
            }
        } else if (game_state->curr_piece.r == 2) {
            if (bottom_left && bottom_right && (top_left || top_right)) {
                return true;
            }
        } else if (game_state->curr_piece.r == 3) {
            if (top_left && bottom_left && (top_right || bottom_right)) {
                return true;
            }
        }

        if (game_state->t_rotation_test_num == SRS_NUM_TESTS) {
            if (top_left + top_right + bottom_left + bottom_right >= 3) {
                return true;
            }
        } 
    }

    return false;
}

bool game_state_check_t_spin_mini(GameState* game_state) {
    if (game_state->t_rotation_test_num > 0 && game_state->t_rotation_test_num < SRS_NUM_TESTS) {
        int top_left_y = game_state->curr_piece.y - game_state->curr_piece.n / 2; 
        int top_left_x = game_state->curr_piece.x - game_state->curr_piece.n / 2;

        bool top_left = false;
        bool top_right = false;
        bool bottom_left = false;
        bool bottom_right = false;

        if (
            top_left_y < 0 || top_left_y > BOARD_H - 1 || 
            top_left_x < 0 || top_left_x > BOARD_W - 1 ||
            game_state->board[top_left_y][top_left_x] > 0
        ) {
            top_left = true;
        }

        if (
            top_left_y < 0 || top_left_y > BOARD_H - 1 || 
            top_left_x + 2 < 0 || top_left_x + 2 > BOARD_W - 1 ||
            game_state->board[top_left_y][top_left_x + 2] > 0
        ) {
            top_right = true;
        }

        if (
            top_left_y + 2 < 0 || top_left_y + 2 > BOARD_H - 1 || 
            top_left_x < 0 || top_left_x > BOARD_W - 1 ||
            game_state->board[top_left_y + 2][top_left_x] > 0
        ) {
            bottom_left = true;
        }

        if (
            top_left_y + 2 < 0 || top_left_y + 2 > BOARD_H - 1 || 
            top_left_x + 2 < 0 || top_left_x + 2 > BOARD_W - 1 ||
            game_state->board[top_left_y + 2][top_left_x + 2] > 0
        ) {
            bottom_right = true;
        }

        if (game_state->curr_piece.r == 0) {
            if (bottom_left && bottom_right && (top_left || top_right)) {
                return true;
            }
        } else if (game_state->curr_piece.r == 1) {
            if (top_left && bottom_left && (top_right || bottom_right)) {
                return true;
            }
        } else if (game_state->curr_piece.r == 2) {
            if (top_left && top_right && (bottom_left || bottom_right)) {
                return true;
            }
        } else if (game_state->curr_piece.r == 3) {
            if (top_right && bottom_right && (top_left || bottom_left)) {
                return true;
            }
        }
    }

    return false;
}

bool game_state_check_empty_board(GameState* game_state) {
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (game_state->board[i][j] > 0) {
                return false;
            } 
        }
    }
    return true;
}
