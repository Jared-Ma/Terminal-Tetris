#include "test_game_state.h"
#include "game_state.h"
#include "piece.h"

#include "utils/assert_trace.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool check_piece_equals_zero(Piece piece) {
    ASSERT(piece.shape == 0);
    ASSERT(piece.y == 0);
    ASSERT(piece.x == 0);
    ASSERT(piece.n == 0);
    ASSERT(piece.l == 0);
    ASSERT(piece.r == 0);
    for (size_t i = 0; i < R_MAX; ++i) {
        for (size_t j = 0; j < N_MAX; ++j) {
            for (size_t k = 0; k < N_MAX; ++k) {
                ASSERT(piece.M[i][j][k] == 0);
            }
        }
    }
    return true;
}

bool test_game_state_get(void) {
    GameState game_state = game_state_get();
    ASSERT(check_piece_equals_zero(game_state.curr_piece));
    ASSERT(check_piece_equals_zero(game_state.hold_piece));
    ASSERT(check_piece_equals_zero(game_state.next_piece));
    ASSERT(check_piece_equals_zero(game_state.ghost_piece));
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            ASSERT(game_state.board[i][j] == 0);
        }
    }
    ASSERT(game_state.holding_piece == false);
    ASSERT(game_state.hold_blocked == false);
    ASSERT(game_state.next_index == 0);
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        ASSERT(game_state.next_queue[i] == 0);
    }
    ASSERT(game_state.soft_drop == false);
    ASSERT(game_state.gravity_value == 0.0);
    ASSERT(game_state.lock_delay_timer == 0);
    ASSERT(game_state.move_reset_count == 0);
    ASSERT(game_state.level == 0);
    ASSERT(game_state.lines == 0);
    ASSERT(game_state.score == 0);
    ASSERT(game_state.combo == 0);
    ASSERT(game_state.difficult_clear_combo == 0);
    ASSERT(game_state.tetris_all_clear_combo == 0);
    ASSERT(game_state.t_rotation_test_num == 0);
    ASSERT(game_state.last_action_points == 0);
    return true;
}

bool test_game_state_init(void) {
    GameState* game_state = game_state_init();
    ASSERT(check_piece_equals_zero(game_state->curr_piece));
    ASSERT(check_piece_equals_zero(game_state->hold_piece));
    ASSERT(check_piece_equals_zero(game_state->next_piece));
    ASSERT(check_piece_equals_zero(game_state->ghost_piece));
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            ASSERT(game_state->board[i][j] == 0);
        }
    }
    ASSERT(game_state->holding_piece == false);
    ASSERT(game_state->hold_blocked == false);
    ASSERT(game_state->next_index == 0);
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        ASSERT(game_state->next_queue[i] == 0);
    }
    ASSERT(game_state->soft_drop == false);
    ASSERT(game_state->gravity_value == 0.0);
    ASSERT(game_state->lock_delay_timer == 0);
    ASSERT(game_state->move_reset_count == 0);
    ASSERT(game_state->level == 0);
    ASSERT(game_state->lines == 0);
    ASSERT(game_state->score == 0);
    ASSERT(game_state->combo == 0);
    ASSERT(game_state->difficult_clear_combo == 0);
    ASSERT(game_state->tetris_all_clear_combo == 0);
    ASSERT(game_state->t_rotation_test_num == 0);
    ASSERT(game_state->last_action_points == 0);
    game_state_destroy(game_state);
    return true;
}

bool test_game_state_start(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    Shape next_shape = game_state.next_queue[game_state.next_index-1];
    ASSERT(game_state.level == 1);
    ASSERT(game_state.combo == -1);
    ASSERT(game_state.next_piece.shape = next_shape);
    
    return true;
}

bool test_game_state_restart(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    piece_move(&game_state.curr_piece, 5, 10);

    game_state_reset(&game_state);

    Shape next_shape = game_state.next_queue[game_state.next_index-1];
    ASSERT(game_state.level == 1);
    ASSERT(game_state.combo == -1);
    ASSERT(game_state.next_piece.shape == next_shape);
    return true;
}

bool test_game_state_generate_next_queue(void) {
    GameState game_state = game_state_get();
    game_state_generate_next_queue(&game_state);

    // test that next_queue has 1 of each shape
    size_t unique_shapes[NUM_SHAPES] = { 0 };
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        unique_shapes[game_state.next_queue[i] - 1]++;
    }
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        ASSERT(unique_shapes[i] == 1);
    }

    // copy the next_queue and generate the next one
    Shape prev_next_queue[NUM_SHAPES] = { 0 };
    for(size_t i = 0; i < NUM_SHAPES; ++i) {
        prev_next_queue[i] = game_state.next_queue[i];
    }
    game_state_generate_next_queue(&game_state);

    // check that the previous next_queue != current next_queue
    // this may fail by chance with probability 1/7! = 1/5040 
    bool equal_arrays = true;
    for (size_t i = 0; i < NUM_SHAPES; ++i) {
        if (prev_next_queue[i] != game_state.next_queue[i]) {
            equal_arrays = false;
        }
    }
    ASSERT(equal_arrays == false);

    return true;
}

bool test_game_state_load_next_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    
    // check that the next shape is equal to curr_piece.shape after loading the next piece 
    // and check that the function handles the case correctly when running out of next shapes
    for (size_t i = 0; i <= NUM_SHAPES; ++i) {
        Shape next_shape = game_state.next_piece.shape;
        game_state_load_next_piece(&game_state);
        ASSERT(game_state.curr_piece.shape == next_shape);
    }

    return true;
}

bool test_game_state_spawn_curr_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state_spawn_curr_piece(&game_state);
    ASSERT(game_state.curr_piece.y = SPAWN_Y);
    ASSERT(game_state.curr_piece.x = SPAWN_X);
    ASSERT(game_state.curr_piece.r == 0);
    ASSERT(game_state.gravity_value == 0.0);
    ASSERT(game_state.lock_delay_timer == LOCK_DELAY);
    ASSERT(game_state.move_reset_count == 0);
    ASSERT(game_state.t_rotation_test_num == 0);
    return true;
}

bool test_game_state_hold_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    // check initial hold
    Shape curr_shape = game_state.curr_piece.shape;
    game_state_hold_piece(&game_state);
    ASSERT(game_state.hold_piece.shape == curr_shape);
    ASSERT(game_state.holding_piece == true);
    ASSERT(game_state.hold_blocked == true);

    // check that holding piece is blocked afterwards
    Shape hold_shape = game_state.hold_piece.shape;
    game_state_hold_piece(&game_state);
    ASSERT(game_state.hold_piece.shape == hold_shape);

    // check that holding is no longer blocked after locking a piece
    game_state_lock_curr_piece(&game_state);
    ASSERT(game_state.hold_blocked == false);

    // check that holding swaps curr_piece and hold_piece
    curr_shape = game_state.curr_piece.shape;
    hold_shape = game_state.hold_piece.shape;
    game_state_hold_piece(&game_state);
    ASSERT(game_state.curr_piece.shape == hold_shape);
    ASSERT(game_state.hold_piece.shape == curr_shape);

    return true;
}

bool test_game_state_check_collision(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    ASSERT(!game_state_check_collision(&game_state, game_state.curr_piece));
    piece_move(&game_state.curr_piece, -1, 5);
    ASSERT(game_state_check_collision(&game_state, game_state.curr_piece));
    piece_move(&game_state.curr_piece, 5, -1);
    ASSERT(game_state_check_collision(&game_state, game_state.curr_piece));
    piece_move(&game_state.curr_piece, BOARD_H, 5);
    ASSERT(game_state_check_collision(&game_state, game_state.curr_piece));
    piece_move(&game_state.curr_piece, 5, BOARD_W);
    ASSERT(game_state_check_collision(&game_state, game_state.curr_piece));
    piece_move(&game_state.curr_piece, SPAWN_Y, SPAWN_X);
    game_state.board[SPAWN_Y][SPAWN_X] = 1;
    ASSERT(game_state_check_collision(&game_state, game_state.curr_piece));

    return true;
}

bool test_game_state_check_curr_piece_grounded(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    game_state.curr_piece = piece_get(T, BOARD_H - 1, 5);
    ASSERT(game_state_check_curr_piece_grounded(&game_state));

    game_state.board[BOARD_H - 1][5] = 1;
    piece_move(&game_state.curr_piece, BOARD_H - 2, 5);
    ASSERT(game_state_check_curr_piece_grounded(&game_state));

    piece_move(&game_state.curr_piece, BOARD_H - 3, 5);
    ASSERT(!game_state_check_curr_piece_grounded(&game_state));

    return true;
}

bool test_game_state_move_curr_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    // check that t_rotation_test_num resets when T pieces make a valid move
    game_state.curr_piece = piece_get(T, SPAWN_Y, SPAWN_X);
    game_state.t_rotation_test_num = 3;
    game_state_move_curr_piece(&game_state, 10, 5);
    ASSERT(game_state.curr_piece.y == 10);
    ASSERT(game_state.curr_piece.x == 5);
    ASSERT(game_state.t_rotation_test_num == 0);

    // check that y and x don't change when making an invalid move
    game_state_move_curr_piece(&game_state, -1, 10);
    ASSERT(game_state.curr_piece.y == 10);
    ASSERT(game_state.curr_piece.x == 5);

    // check that lock_delay_timer and move_reset_count don't change when making an invalid move
    game_state.lock_delay_timer = LOCK_DELAY - 1;
    game_state.move_reset_count = MAX_MOVE_RESET - 1;
    game_state_move_curr_piece(&game_state, -1, 5);
    ASSERT(game_state.lock_delay_timer == LOCK_DELAY - 1);
    ASSERT(game_state.move_reset_count == MAX_MOVE_RESET - 1);

    // check that they change when making a valid move
    game_state_move_curr_piece(&game_state, 10, 5);
    ASSERT(game_state.lock_delay_timer == LOCK_DELAY);
    ASSERT(game_state.move_reset_count == MAX_MOVE_RESET);

    // check that they only change when both 
    // lock_delay_timer < LOCK_DELAY and move_reset_count < MAX_MOVE_RESET
    game_state.lock_delay_timer = LOCK_DELAY;
    game_state.move_reset_count = MAX_MOVE_RESET - 1;
    game_state_move_curr_piece(&game_state, 11, 5);
    ASSERT(game_state.lock_delay_timer == LOCK_DELAY);
    ASSERT(game_state.move_reset_count == MAX_MOVE_RESET - 1);

    game_state.lock_delay_timer = LOCK_DELAY - 1;
    game_state.move_reset_count = MAX_MOVE_RESET;
    game_state_move_curr_piece(&game_state, 12, 5);
    ASSERT(game_state.lock_delay_timer == LOCK_DELAY - 1);
    ASSERT(game_state.move_reset_count == MAX_MOVE_RESET);
    
    return true;
}

bool test_game_state_rotate_curr_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    game_state_rotate_curr_piece(&game_state, RIGHT);
    ASSERT(game_state.curr_piece.r == 1);

    game_state_rotate_curr_piece(&game_state, LEFT);
    ASSERT(game_state.curr_piece.r == 0);

    game_state.curr_piece = piece_get(I, BOARD_H - 1, SPAWN_X);
    game_state_rotate_curr_piece(&game_state, RIGHT);
    ASSERT(game_state.curr_piece.r == 0);

    game_state_rotate_curr_piece(&game_state, LEFT);
    ASSERT(game_state.curr_piece.r == 0);

    return true;
}

bool test_game_state_rotate_curr_piece_srs_i_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    Piece test_spawn_piece = piece_get(I, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // iterate through each possible RIGHT and LEFT rotation and SRS test
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;
        test_spawn_piece.r = r % R_MAX;

        // calculate index into SRS_TABLE
        size_t r_index;
        if (rotation == RIGHT) {
            r_index = 2 * test_spawn_piece.r;
        } else {
            r_index = SRS_NUM_ROTATIONS - 1;
            r_index -= (test_spawn_piece.r > 0) ? 2*(R_MAX - test_spawn_piece.r) : 0;
        }
        
        // clear board of any obstructions
        for (size_t i = 0; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 0;
            }
        }

        for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {
            // reset curr_piece to test_spawn_piece
            game_state.curr_piece = test_spawn_piece;

            // resulting piece after kick and rotation
            Piece result_piece = game_state.curr_piece;
            result_piece.y = game_state.curr_piece.y - SRS_TABLE_I[r_index][i][1];
            result_piece.x = game_state.curr_piece.x + SRS_TABLE_I[r_index][i][0];
            result_piece.r = compute_r_index(game_state.curr_piece.r, rotation);

            // remove any obstruction in resulting placement of curr_piece after SRS rotation
            int result_top_left_y = result_piece.y - result_piece.n / 2; 
            int result_top_left_x = result_piece.x - result_piece.n / 2;
            for (size_t j = 0; j < result_piece.n; ++j) {
                for (size_t k = 0; k < result_piece.n; ++k) {
                    if (result_piece.M[result_piece.r][j][k] == 1) {
                        game_state.board[result_top_left_y + j][result_top_left_x + k] = 0;
                    }
                }
            }

            // perform SRS rotation on curr_piece
            game_state_rotate_curr_piece_srs(&game_state, rotation);

            // check that curr_piece matches result_piece
            ASSERT(game_state.curr_piece.y == result_piece.y);
            ASSERT(game_state.curr_piece.x == result_piece.x);
            ASSERT(game_state.curr_piece.r == result_piece.r);

            // add obstruction according to curr_piece placement, so that next SRS test is triggered
            int curr_top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
            int curr_top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                for (size_t k = 0; k < game_state.curr_piece.n; ++k) {
                    if (game_state.curr_piece.M[game_state.curr_piece.r][j][k] == 1) {
                        game_state.board[curr_top_left_y + j][curr_top_left_x + k] = 1;
                    }
                }
            }
            
            // remove any obstruction that blocks test_spawn_piece
            int test_top_left_y = test_spawn_piece.y - test_spawn_piece.n / 2; 
            int test_top_left_x = test_spawn_piece.x - test_spawn_piece.n / 2;
            for (size_t j = 0; j < test_spawn_piece.n; ++j) {
                for (size_t k = 0; k < test_spawn_piece.n; ++k) {
                    if (test_spawn_piece.M[test_spawn_piece.r][j][k] == 1) {
                        game_state.board[test_top_left_y + j][test_top_left_x + k] = 0;
                    }
                }
            }

            // check that curr_piece doesn't rotate after last test
            if (i == SRS_NUM_TESTS - 1) {
                game_state.curr_piece = test_spawn_piece;
                game_state_rotate_curr_piece_srs(&game_state, rotation);
                ASSERT(game_state.curr_piece.y == test_spawn_piece.y);
                ASSERT(game_state.curr_piece.x == test_spawn_piece.x);
                ASSERT(game_state.curr_piece.r == test_spawn_piece.r);
            }
        }
    }

    return true;
}

bool test_game_state_rotate_curr_piece_srs_j_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    Piece test_spawn_piece = piece_get(J, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // iterate through each possible RIGHT and LEFT rotation and SRS test
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;
        test_spawn_piece.r = r % R_MAX;

        // calculate index into SRS_TABLE
        size_t r_index;
        if (rotation == RIGHT) {
            r_index = 2 * test_spawn_piece.r;
        } else {
            r_index = SRS_NUM_ROTATIONS - 1;
            r_index -= (test_spawn_piece.r > 0) ? 2*(R_MAX - test_spawn_piece.r) : 0;
        }
        
        // clear board of any obstructions
        for (size_t i = 0; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 0;
            }
        }

        for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {
            // reset curr_piece to test_spawn_piece
            game_state.curr_piece = test_spawn_piece;

            // resulting piece after kick and rotation
            Piece result_piece = game_state.curr_piece;
            result_piece.y = game_state.curr_piece.y - SRS_TABLE[r_index][i][1];
            result_piece.x = game_state.curr_piece.x + SRS_TABLE[r_index][i][0];
            result_piece.r = compute_r_index(game_state.curr_piece.r, rotation);

            // remove any obstruction in resulting placement of curr_piece after SRS rotation
            int result_top_left_y = result_piece.y - result_piece.n / 2; 
            int result_top_left_x = result_piece.x - result_piece.n / 2;
            for (size_t j = 0; j < result_piece.n; ++j) {
                for (size_t k = 0; k < result_piece.n; ++k) {
                    if (result_piece.M[result_piece.r][j][k] == 1) {
                        game_state.board[result_top_left_y + j][result_top_left_x + k] = 0;
                    }
                }
            }

            // perform SRS rotation on curr_piece
            game_state_rotate_curr_piece_srs(&game_state, rotation);

            // check that curr_piece matches result_piece
            ASSERT(game_state.curr_piece.y == result_piece.y);
            ASSERT(game_state.curr_piece.x == result_piece.x);
            ASSERT(game_state.curr_piece.r == result_piece.r);

            // add obstruction according to curr_piece placement, so that next SRS test is triggered
            int curr_top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
            int curr_top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                for (size_t k = 0; k < game_state.curr_piece.n; ++k) {
                    if (game_state.curr_piece.M[game_state.curr_piece.r][j][k] == 1) {
                        game_state.board[curr_top_left_y + j][curr_top_left_x + k] = 1;
                    }
                }
            }
            
            // remove any obstruction that blocks test_spawn_piece
            int test_top_left_y = test_spawn_piece.y - test_spawn_piece.n / 2; 
            int test_top_left_x = test_spawn_piece.x - test_spawn_piece.n / 2;
            for (size_t j = 0; j < test_spawn_piece.n; ++j) {
                for (size_t k = 0; k < test_spawn_piece.n; ++k) {
                    if (test_spawn_piece.M[test_spawn_piece.r][j][k] == 1) {
                        game_state.board[test_top_left_y + j][test_top_left_x + k] = 0;
                    }
                }
            }
            
            // check that curr_piece doesn't rotate after last test
            if (i == SRS_NUM_TESTS - 1) {
                game_state.curr_piece = test_spawn_piece;
                game_state_rotate_curr_piece_srs(&game_state, rotation);
                ASSERT(game_state.curr_piece.y == test_spawn_piece.y);
                ASSERT(game_state.curr_piece.x == test_spawn_piece.x);
                ASSERT(game_state.curr_piece.r == test_spawn_piece.r);
            }
        }
    }

    return true;
}

bool test_game_state_rotate_curr_piece_srs_l_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    Piece test_spawn_piece = piece_get(L, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // iterate through each possible RIGHT and LEFT rotation and SRS test
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;
        test_spawn_piece.r = r % R_MAX;

        // calculate index into SRS_TABLE
        size_t r_index;
        if (rotation == RIGHT) {
            r_index = 2 * test_spawn_piece.r;
        } else {
            r_index = SRS_NUM_ROTATIONS - 1;
            r_index -= (test_spawn_piece.r > 0) ? 2*(R_MAX - test_spawn_piece.r) : 0;
        }
        
        // clear board of any obstructions
        for (size_t i = 0; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 0;
            }
        }

        for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {
            // reset curr_piece to test_spawn_piece
            game_state.curr_piece = test_spawn_piece;

            // resulting piece after kick and rotation
            Piece result_piece = game_state.curr_piece;
            result_piece.y = game_state.curr_piece.y - SRS_TABLE[r_index][i][1];
            result_piece.x = game_state.curr_piece.x + SRS_TABLE[r_index][i][0];
            result_piece.r = compute_r_index(game_state.curr_piece.r, rotation);

            // remove any obstruction in resulting placement of curr_piece after SRS rotation
            int result_top_left_y = result_piece.y - result_piece.n / 2; 
            int result_top_left_x = result_piece.x - result_piece.n / 2;
            for (size_t j = 0; j < result_piece.n; ++j) {
                for (size_t k = 0; k < result_piece.n; ++k) {
                    if (result_piece.M[result_piece.r][j][k] == 1) {
                        game_state.board[result_top_left_y + j][result_top_left_x + k] = 0;
                    }
                }
            }

            // perform SRS rotation on curr_piece
            game_state_rotate_curr_piece_srs(&game_state, rotation);

            // check that curr_piece matches result_piece
            ASSERT(game_state.curr_piece.y == result_piece.y);
            ASSERT(game_state.curr_piece.x == result_piece.x);
            ASSERT(game_state.curr_piece.r == result_piece.r);

            // add obstruction according to curr_piece placement, so that next SRS test is triggered
            int curr_top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
            int curr_top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                for (size_t k = 0; k < game_state.curr_piece.n; ++k) {
                    if (game_state.curr_piece.M[game_state.curr_piece.r][j][k] == 1) {
                        game_state.board[curr_top_left_y + j][curr_top_left_x + k] = 1;
                    }
                }
            }
            
            // remove any obstruction that blocks test_spawn_piece
            int test_top_left_y = test_spawn_piece.y - test_spawn_piece.n / 2; 
            int test_top_left_x = test_spawn_piece.x - test_spawn_piece.n / 2;
            for (size_t j = 0; j < test_spawn_piece.n; ++j) {
                for (size_t k = 0; k < test_spawn_piece.n; ++k) {
                    if (test_spawn_piece.M[test_spawn_piece.r][j][k] == 1) {
                        game_state.board[test_top_left_y + j][test_top_left_x + k] = 0;
                    }
                }
            }

            // check that curr_piece doesn't rotate after last test
            if (i == SRS_NUM_TESTS - 1) {
                game_state.curr_piece = test_spawn_piece;
                game_state_rotate_curr_piece_srs(&game_state, rotation);
                ASSERT(game_state.curr_piece.y == test_spawn_piece.y);
                ASSERT(game_state.curr_piece.x == test_spawn_piece.x);
                ASSERT(game_state.curr_piece.r == test_spawn_piece.r);
            }
        }
    }

    return true;
}

bool test_game_state_rotate_curr_piece_srs_o_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state.curr_piece = piece_get(O, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // check that the relative coordinates of O piece minos don't change after each rotation
    // i.e. the O piece doesn't appear to move on the board when rotated
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;

        // calculate coordinates of each O piece mino before the rotation
        int prev_mino_coordinates[4][2] = {{ 0 }};
        int prev_num_minos = 0;
        int top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
        int top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
        for (size_t i = 0; i < game_state.curr_piece.n; ++i) {
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                if (game_state.curr_piece.M[game_state.curr_piece.r][i][j] == 1) {
                    prev_mino_coordinates[prev_num_minos][0] = top_left_y + i;
                    prev_mino_coordinates[prev_num_minos][1] = top_left_x + j;
                    prev_num_minos++;
                }
            }
        }
    
        // perform rotation on O piece
        game_state_rotate_curr_piece_srs(&game_state, rotation);
        
        // calculate coordinates of each O piece mino after the rotation
        int curr_mino_coordinates[4][2] = {{ 0 }};
        int curr_num_minos = 0;
        top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
        top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
        for (size_t i = 0; i < game_state.curr_piece.n; ++i) {
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                if (game_state.curr_piece.M[game_state.curr_piece.r][i][j] == 1) {
                    curr_mino_coordinates[curr_num_minos][0] = top_left_y + i;
                    curr_mino_coordinates[curr_num_minos][1] = top_left_x + j;
                    curr_num_minos++;
                }
            }
        }
    
        // check that coordinates are the same before and after rotation
        for (size_t i = 0; i < curr_num_minos; ++i) {
            ASSERT(prev_mino_coordinates[i][0] == curr_mino_coordinates[i][0])
            ASSERT(prev_mino_coordinates[i][1] == curr_mino_coordinates[i][1])
        }
    }

    return true;
}

bool test_game_state_rotate_curr_piece_srs_s_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    Piece test_spawn_piece = piece_get(S, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // iterate through each possible RIGHT and LEFT rotation and SRS test
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;
        test_spawn_piece.r = r % R_MAX;

        // calculate index into SRS_TABLE
        size_t r_index;
        if (rotation == RIGHT) {
            r_index = 2 * test_spawn_piece.r;
        } else {
            r_index = SRS_NUM_ROTATIONS - 1;
            r_index -= (test_spawn_piece.r > 0) ? 2*(R_MAX - test_spawn_piece.r) : 0;
        }
        
        // clear board of any obstructions
        for (size_t i = 0; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 0;
            }
        }

        for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {
            // reset curr_piece to test_spawn_piece
            game_state.curr_piece = test_spawn_piece;

            // resulting piece after kick and rotation
            Piece result_piece = game_state.curr_piece;
            result_piece.y = game_state.curr_piece.y - SRS_TABLE[r_index][i][1];
            result_piece.x = game_state.curr_piece.x + SRS_TABLE[r_index][i][0];
            result_piece.r = compute_r_index(game_state.curr_piece.r, rotation);

            // remove any obstruction in resulting placement of curr_piece after SRS rotation
            int result_top_left_y = result_piece.y - result_piece.n / 2; 
            int result_top_left_x = result_piece.x - result_piece.n / 2;
            for (size_t j = 0; j < result_piece.n; ++j) {
                for (size_t k = 0; k < result_piece.n; ++k) {
                    if (result_piece.M[result_piece.r][j][k] == 1) {
                        game_state.board[result_top_left_y + j][result_top_left_x + k] = 0;
                    }
                }
            }
            
            // perform SRS rotation on curr_piece
            game_state_rotate_curr_piece_srs(&game_state, rotation);

            // check that curr_piece matches result_piece
            ASSERT(game_state.curr_piece.y == result_piece.y);
            ASSERT(game_state.curr_piece.x == result_piece.x);
            ASSERT(game_state.curr_piece.r == result_piece.r);

            // add obstruction according to curr_piece placement, so that next SRS test is triggered
            int curr_top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
            int curr_top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                for (size_t k = 0; k < game_state.curr_piece.n; ++k) {
                    if (game_state.curr_piece.M[game_state.curr_piece.r][j][k] == 1) {
                        game_state.board[curr_top_left_y + j][curr_top_left_x + k] = 1;
                    }
                }
            }
            
            // remove any obstruction that blocks test_spawn_piece
            int test_top_left_y = test_spawn_piece.y - test_spawn_piece.n / 2; 
            int test_top_left_x = test_spawn_piece.x - test_spawn_piece.n / 2;
            for (size_t j = 0; j < test_spawn_piece.n; ++j) {
                for (size_t k = 0; k < test_spawn_piece.n; ++k) {
                    if (test_spawn_piece.M[test_spawn_piece.r][j][k] == 1) {
                        game_state.board[test_top_left_y + j][test_top_left_x + k] = 0;
                    }
                }
            }
            
            // check that curr_piece doesn't rotate after last test
            if (i == SRS_NUM_TESTS - 1) {
                game_state.curr_piece = test_spawn_piece;
                game_state_rotate_curr_piece_srs(&game_state, rotation);
                ASSERT(game_state.curr_piece.y == test_spawn_piece.y);
                ASSERT(game_state.curr_piece.x == test_spawn_piece.x);
                ASSERT(game_state.curr_piece.r == test_spawn_piece.r);
            }
        }
    }

    return true;
}

bool test_game_state_rotate_curr_piece_srs_t_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    Piece test_spawn_piece = piece_get(T, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // iterate through each possible RIGHT and LEFT rotation and SRS test
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;
        test_spawn_piece.r = r % R_MAX;

        // calculate index into SRS_TABLE
        size_t r_index;
        if (rotation == RIGHT) {
            r_index = 2 * test_spawn_piece.r;
        } else {
            r_index = SRS_NUM_ROTATIONS - 1;
            r_index -= (test_spawn_piece.r > 0) ? 2*(R_MAX - test_spawn_piece.r) : 0;
        }
        
        // clear board of any obstructions
        for (size_t i = 0; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 0;
            }
        }

        for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {

            // for the T piece there are special cases in the SRS_TABLE that not possible
            if (
                (r_index == 0 && i == 3) || (r_index == 4 && i == 2) ||
                (r_index == 7 && i == 3) || (r_index == 3 && i == 2) 
            ) {
                continue;
            }

            // reset curr_piece to test_spawn_piece
            game_state.curr_piece = test_spawn_piece;

            // resulting piece after kick and rotation
            Piece result_piece = game_state.curr_piece;
            result_piece.y = game_state.curr_piece.y - SRS_TABLE[r_index][i][1];
            result_piece.x = game_state.curr_piece.x + SRS_TABLE[r_index][i][0];
            result_piece.r = compute_r_index(game_state.curr_piece.r, rotation);

            // remove any obstruction in resulting placement of curr_piece after SRS rotation
            int result_top_left_y = result_piece.y - result_piece.n / 2; 
            int result_top_left_x = result_piece.x - result_piece.n / 2;
            for (size_t j = 0; j < result_piece.n; ++j) {
                for (size_t k = 0; k < result_piece.n; ++k) {
                    if (result_piece.M[result_piece.r][j][k] == 1) {
                        game_state.board[result_top_left_y + j][result_top_left_x + k] = 0;
                    }
                }
            }

            // perform SRS rotation on curr_piece
            game_state_rotate_curr_piece_srs(&game_state, rotation);

            // check that curr_piece matches result_piece
            ASSERT(game_state.curr_piece.y == result_piece.y);
            ASSERT(game_state.curr_piece.x == result_piece.x);
            ASSERT(game_state.curr_piece.r == result_piece.r);
            ASSERT(game_state.t_rotation_test_num == i + 1);

            // add obstruction according to curr_piece placement, so that next SRS test is triggered
            int curr_top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
            int curr_top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                for (size_t k = 0; k < game_state.curr_piece.n; ++k) {
                    if (game_state.curr_piece.M[game_state.curr_piece.r][j][k] == 1) {
                        game_state.board[curr_top_left_y + j][curr_top_left_x + k] = 1;
                    }
                }
            }
            
            // remove any obstruction that blocks test_spawn_piece
            int test_top_left_y = test_spawn_piece.y - test_spawn_piece.n / 2; 
            int test_top_left_x = test_spawn_piece.x - test_spawn_piece.n / 2;
            for (size_t j = 0; j < test_spawn_piece.n; ++j) {
                for (size_t k = 0; k < test_spawn_piece.n; ++k) {
                    if (test_spawn_piece.M[test_spawn_piece.r][j][k] == 1) {
                        game_state.board[test_top_left_y + j][test_top_left_x + k] = 0;
                    }
                }
            }
            
            // check that curr_piece doesn't rotate after last test
            if (i == SRS_NUM_TESTS - 1) {
                game_state.curr_piece = test_spawn_piece;
                game_state_rotate_curr_piece_srs(&game_state, rotation);
                ASSERT(game_state.curr_piece.y == test_spawn_piece.y);
                ASSERT(game_state.curr_piece.x == test_spawn_piece.x);
                ASSERT(game_state.curr_piece.r == test_spawn_piece.r);
                ASSERT(game_state.t_rotation_test_num == i + 1);
            }
        }
    }

    return true;
}

bool test_game_state_rotate_curr_piece_srs_z_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    Piece test_spawn_piece = piece_get(Z, (BOARD_H-1)/2, (BOARD_W-1)/2);
    
    // iterate through each possible RIGHT and LEFT rotation and SRS test
    for (size_t r = 0; r < 2 * R_MAX; ++r) {
        Rotation rotation = (r < R_MAX) ? RIGHT : LEFT;
        test_spawn_piece.r = r % R_MAX;

        // calculate index into SRS_TABLE
        size_t r_index;
        if (rotation == RIGHT) {
            r_index = 2 * test_spawn_piece.r;
        } else {
            r_index = SRS_NUM_ROTATIONS - 1;
            r_index -= (test_spawn_piece.r > 0) ? 2*(R_MAX - test_spawn_piece.r) : 0;
        }
        
        // clear board of any obstructions
        for (size_t i = 0; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 0;
            }
        }

        for (size_t i = 0; i < SRS_NUM_TESTS; ++i) {
            // reset curr_piece to test_spawn_piece
            game_state.curr_piece = test_spawn_piece;

            // resulting piece after kick and rotation
            Piece result_piece = game_state.curr_piece;
            result_piece.y = game_state.curr_piece.y - SRS_TABLE[r_index][i][1];
            result_piece.x = game_state.curr_piece.x + SRS_TABLE[r_index][i][0];
            result_piece.r = compute_r_index(game_state.curr_piece.r, rotation);

            // remove any obstruction in resulting placement of curr_piece after SRS rotation
            int result_top_left_y = result_piece.y - result_piece.n / 2; 
            int result_top_left_x = result_piece.x - result_piece.n / 2;
            for (size_t j = 0; j < result_piece.n; ++j) {
                for (size_t k = 0; k < result_piece.n; ++k) {
                    if (result_piece.M[result_piece.r][j][k] == 1) {
                        game_state.board[result_top_left_y + j][result_top_left_x + k] = 0;
                    }
                }
            }

            // perform SRS rotation on curr_piece
            game_state_rotate_curr_piece_srs(&game_state, rotation);

            // check that curr_piece matches result_piece
            ASSERT(game_state.curr_piece.y == result_piece.y);
            ASSERT(game_state.curr_piece.x == result_piece.x);
            ASSERT(game_state.curr_piece.r == result_piece.r);

            // add obstruction according to curr_piece placement, so that next SRS test is triggered
            int curr_top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
            int curr_top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
            for (size_t j = 0; j < game_state.curr_piece.n; ++j) {
                for (size_t k = 0; k < game_state.curr_piece.n; ++k) {
                    if (game_state.curr_piece.M[game_state.curr_piece.r][j][k] == 1) {
                        game_state.board[curr_top_left_y + j][curr_top_left_x + k] = 1;
                    }
                }
            }

            // remove any obstruction that blocks test_spawn_piece
            int test_top_left_y = test_spawn_piece.y - test_spawn_piece.n / 2; 
            int test_top_left_x = test_spawn_piece.x - test_spawn_piece.n / 2;
            for (size_t j = 0; j < test_spawn_piece.n; ++j) {
                for (size_t k = 0; k < test_spawn_piece.n; ++k) {
                    if (test_spawn_piece.M[test_spawn_piece.r][j][k] == 1) {
                        game_state.board[test_top_left_y + j][test_top_left_x + k] = 0;
                    }
                }
            }

            // check that curr_piece doesn't rotate after last test
            if (i == SRS_NUM_TESTS - 1) {
                game_state.curr_piece = test_spawn_piece;
                game_state_rotate_curr_piece_srs(&game_state, rotation);
                ASSERT(game_state.curr_piece.y == test_spawn_piece.y);
                ASSERT(game_state.curr_piece.x == test_spawn_piece.x);
                ASSERT(game_state.curr_piece.r == test_spawn_piece.r);
            }
        }
    }

    return true;
}

bool test_game_state_hard_drop_curr_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    
    game_state.board[(BOARD_H-1)/2][(BOARD_W-1)/2] = 1;
    game_state_hard_drop_curr_piece(&game_state);
    ASSERT(game_state.curr_piece.y == (BOARD_H-1)/2 - 1);
    ASSERT(game_state_check_curr_piece_grounded(&game_state));

    game_state.board[(BOARD_H-1)/2][(BOARD_W-1)/2] = 0;
    game_state_hard_drop_curr_piece(&game_state);
    ASSERT(game_state.curr_piece.y == BOARD_H - 1);
    ASSERT(game_state_check_curr_piece_grounded(&game_state));

    return true;
}

bool test_game_state_lock_curr_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state_move_curr_piece(&game_state, (BOARD_H-1)/2, (BOARD_W-1)/2);
    game_state_lock_curr_piece(&game_state);

    int top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
    int top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;
    int bottom_right_y = game_state.curr_piece.y + game_state.curr_piece.n / 2; 
    int bottom_right_x = game_state.curr_piece.x + game_state.curr_piece.n / 2;
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (
                i >= top_left_y && i <= bottom_right_y && 
                j >= top_left_x && j <= bottom_right_x &&
                game_state.curr_piece.M[game_state.curr_piece.r][i - top_left_y][j - top_left_x] > 0
            ) {
                ASSERT(game_state.board[i][j] == game_state.curr_piece.shape); 
            } else {
                ASSERT(game_state.board[i][j] == 0);
            }
        }
    }
    ASSERT(game_state.hold_blocked == false);

    return true;
}

bool test_game_state_apply_stack_gravity(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    for (size_t i = 0; i < BOARD_H/2; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (i % 2 == 0) {
                game_state.board[i][j] = 1;
            }
        }
    }

    game_state_apply_stack_gravity(&game_state, BOARD_H/2);

    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (i < BOARD_H/2 + 1) {
                if (i % 2 == 0) {
                    ASSERT(game_state.board[i][j] == 0);
                } else {
                    ASSERT(game_state.board[i][j] == 1);
                }
            } else {   
                ASSERT(game_state.board[i][j] == 0);
            }
        }
    }

    return true;
}

bool test_game_state_clear_line(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    size_t row = BOARD_H/2;
    for (size_t j = 0; j < BOARD_W; ++j) {
        game_state.board[row][j] = 1;
    }

    game_state_clear_line(&game_state, row);

    for (size_t j = 0; j < BOARD_W; ++j) {
        ASSERT(game_state.board[row][j] == 0);
    }

    return true;
}

bool test_game_state_clear_lines(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    for (size_t num_lines = 0; num_lines <= 4; ++num_lines) {
        for (size_t i = 0; i < BOARD_H - num_lines; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                if (i % 2 == 0) {
                    game_state.board[i][j] = (j % 2 == 0) ? 1 : 0;
                } else {
                    game_state.board[i][j] = (j % 2 == 0) ? 0 : 1;
                }
            }
        }
        
        for (size_t i = BOARD_H - num_lines; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                game_state.board[i][j] = 1;
            }
        }
        
        game_state.level = 1; 
        game_state.lines = LEVEL_LINE_REQ - num_lines; 
        game_state.score = 0; 
        game_state.combo = -1; 
        uint64_t prev_level = game_state.level;
        uint64_t prev_lines = game_state.lines;
        uint64_t prev_score = game_state.score;

        game_state_clear_lines(&game_state);
        
        ASSERT(game_state.level == prev_level + 1);
        ASSERT(game_state.lines == prev_lines + num_lines);
        if (num_lines == 0) {
            ASSERT(game_state.score == 0);
        } else if (num_lines == 1) {
            ASSERT(game_state.score == prev_score + SINGLE_POINTS);
        } else if (num_lines == 2) {
            ASSERT(game_state.score == prev_score + DOUBLE_POINTS);
        } else if (num_lines == 3) {
            ASSERT(game_state.score == prev_score + TRIPLE_POINTS);
        } else if (num_lines == 4) {
            ASSERT(game_state.score == prev_score + TETRIS_POINTS);
        }
    
        for (size_t i = 0; i < num_lines; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                ASSERT(game_state.board[i][j] == 0);
            }
        }
    
        for (size_t i = num_lines; i < BOARD_H; ++i) {
            for (size_t j = 0; j < BOARD_W; ++j) {
                if ((i + num_lines) % 2 == 0) {
                    if (j % 2 == 0) {
                        ASSERT(game_state.board[i][j] == 1);
                    } else {
                        ASSERT(game_state.board[i][j] == 0);
                    }
                } else {
                    if (j % 2 == 0) {
                        ASSERT(game_state.board[i][j] == 0);
                    } else {
                        ASSERT(game_state.board[i][j] == 1);
                    }
                }
            }
        } 
    }

    return true;
}

bool test_game_state_apply_gravity(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    for (size_t level = 1; level <= MAX_GRAVITY_LEVEL; ++level) {
        game_state.level = level;
        game_state.curr_piece.y = 0;
        size_t end_frame_count = (BOARD_H - 1) / GRAVITY_TABLE[level-1] + 1;
        for (size_t frame_count = 0; frame_count < end_frame_count; ++frame_count) {
            game_state_apply_gravity(&game_state);
            ASSERT(game_state.gravity_value < 1);
        }
        ASSERT(game_state.curr_piece.y == BOARD_H - 1);
    }

    return true;
}

bool test_game_state_apply_soft_drop_gravity(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    for (size_t level = 1; level <= MAX_GRAVITY_LEVEL; ++level) {
        game_state.level = level;
        game_state.curr_piece.y = 0;
        size_t end_frame_count = (BOARD_H - 1) / (SOFT_DROP_GRAVITY_MULT * GRAVITY_TABLE[level-1]) + 1;
        for (size_t frame_count = 0; frame_count < end_frame_count; ++frame_count) {
            int prev_y = game_state.curr_piece.y;
            int prev_score = game_state.score;
            game_state.soft_drop = true;
            game_state_apply_soft_drop_gravity(&game_state);
            ASSERT(game_state.gravity_value < 1);
            ASSERT(game_state.score == prev_score + SOFT_DROP_POINTS * (game_state.curr_piece.y - prev_y))
            ASSERT(game_state.soft_drop == false);
        }
        ASSERT(game_state.curr_piece.y == BOARD_H - 1);
    }

    return true;
}

bool test_game_state_soft_drop_curr_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state.soft_drop = false;
    int prev_y = game_state.curr_piece.y;
    game_state_soft_drop_curr_piece(&game_state);
    ASSERT(game_state.curr_piece.y == prev_y + 1);
    ASSERT(game_state.score == SOFT_DROP_POINTS);
    ASSERT(game_state.soft_drop == true);
    return true;
}

bool test_game_state_move_ghost_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    int prev_y = game_state.ghost_piece.y;
    int prev_x = game_state.ghost_piece.x;
    game_state_move_ghost_piece(&game_state, 10, 5);
    ASSERT(game_state.ghost_piece.y == 10);
    ASSERT(game_state.ghost_piece.x == 5);

    prev_y = game_state.ghost_piece.y;
    prev_x = game_state.ghost_piece.x;
    game_state_move_ghost_piece(&game_state, -1, -1);
    ASSERT(game_state.ghost_piece.y == prev_y);
    ASSERT(game_state.ghost_piece.x == prev_x);

    return true;
}

bool test_game_state_update_ghost_piece(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state_move_curr_piece(&game_state, 10, 5);
    game_state_update_ghost_piece(&game_state);
    ASSERT(game_state.ghost_piece.shape == game_state.curr_piece.shape);
    ASSERT(game_state.ghost_piece.y == BOARD_H - 1);
    ASSERT(game_state.ghost_piece.x == game_state.curr_piece.x);
    ASSERT(game_state.ghost_piece.r == game_state.curr_piece.r);
    return true;
}

bool test_game_state_check_t_spin(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state.curr_piece = piece_get(T, (BOARD_H-1)/2, (BOARD_W-1)/2);

    game_state.t_rotation_test_num = 0;
    ASSERT(game_state_check_t_spin(&game_state) == false);

    int top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
    int top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;

    game_state.t_rotation_test_num = 1;
    game_state.curr_piece.r = 0;

    // cases when there should be a t-spin:
    // each corner is specified by a bit in order from top-left, top-right, 
    // bottom-left, bottom-right, from least to most significant bit
    uint8_t true_case_1 = 0b0111;
    uint8_t true_case_2 = 0b1011;
    uint8_t true_case_3 = 0b1111;

    // enumerate and test every possible combination of corners 
    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = 2;
    game_state.curr_piece.r = 1;
    true_case_1 = 0b1011;
    true_case_2 = 0b1110;
    true_case_3 = 0b1111;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = 3;
    game_state.curr_piece.r = 2;
    true_case_1 = 0b1101;
    true_case_2 = 0b1110;
    true_case_3 = 0b1111;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = 4;
    game_state.curr_piece.r = 3;
    true_case_1 = 0b0111;
    true_case_2 = 0b1101;
    true_case_3 = 0b1111;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = SRS_NUM_TESTS;
    game_state.curr_piece.r = 0;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        // check if true when there are at least 3 corners 
        if ((bool)(i & 0b0001) + (bool)(i & 0b0010) + (bool)(i & 0b0100) + (bool)(i & 0b1000) >= 3) {
            ASSERT(game_state_check_t_spin(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin(&game_state) == false);
        }
    }

    return true;
}

bool test_game_state_check_t_spin_mini(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state.curr_piece = piece_get(T, (BOARD_H-1)/2, (BOARD_W-1)/2);

    game_state.t_rotation_test_num = 0;
    ASSERT(game_state_check_t_spin(&game_state) == false);
    game_state.t_rotation_test_num = SRS_NUM_TESTS;
    ASSERT(game_state_check_t_spin(&game_state) == false);

    int top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
    int top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;

    game_state.t_rotation_test_num = 1;
    game_state.curr_piece.r = 0;

    // cases when there should be a mini t-spin:
    // each corner is specified by a bit in order from top-left, top-right, 
    // bottom-left, bottom-right, from least to most significant bit
    uint8_t true_case_1 = 0b1101;
    uint8_t true_case_2 = 0b1110;
    uint8_t true_case_3 = 0b1111;

    // enumerate and test every possible combination of corners 
    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin_mini(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin_mini(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = 2;
    game_state.curr_piece.r = 1;
    true_case_1 = 0b0111;
    true_case_2 = 0b1101;
    true_case_3 = 0b1111;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin_mini(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin_mini(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = 3;
    game_state.curr_piece.r = 2;
    true_case_1 = 0b0111;
    true_case_2 = 0b1011;
    true_case_3 = 0b1111;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin_mini(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin_mini(&game_state) == false);
        }
    }

    game_state.t_rotation_test_num = 4;
    game_state.curr_piece.r = 3;
    true_case_1 = 0b1011;
    true_case_2 = 0b1110;
    true_case_3 = 0b1111;

    for (size_t i = 0; i < 16; ++i) {
        game_state.board[top_left_y][top_left_x] =         (bool)(i & 0b0001);
        game_state.board[top_left_y][top_left_x + 2] =     (bool)(i & 0b0010);
        game_state.board[top_left_y + 2][top_left_x] =     (bool)(i & 0b0100);
        game_state.board[top_left_y + 2][top_left_x + 2] = (bool)(i & 0b1000);

        if (i == true_case_1 || i == true_case_2 || i == true_case_3) {
            ASSERT(game_state_check_t_spin_mini(&game_state) == true);
        } else {
            ASSERT(game_state_check_t_spin_mini(&game_state) == false);
        }
    }

    return true;
}

bool test_game_state_check_empty_board(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state.board[i][j] = 0;
        }
    }

    ASSERT(game_state_check_empty_board(&game_state) == true);

    game_state.board[0][0] = 1;
    ASSERT(game_state_check_empty_board(&game_state) == false);

    return true;
}

bool test_game_state_calc_t_spin_points(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);
    game_state.curr_piece = piece_get(T, (BOARD_H-1)/2, (BOARD_W-1)/2);

    int top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
    int top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;

    // force a t-spin
    game_state.t_rotation_test_num = 1;
    game_state.curr_piece.r = 0;
    game_state.board[top_left_y][top_left_x] = 1;
    game_state.board[top_left_y][top_left_x + 2] = 1;
    game_state.board[top_left_y + 2][top_left_x] = 1;
    game_state.board[top_left_y + 2][top_left_x + 2] = 0;

    game_state.level = 1;
    uint64_t num_lines = 0;
    uint64_t points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_ZERO_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == -1);

    game_state.level = 2;
    num_lines = 1;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_SINGLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 0);

    game_state.level = 3;
    num_lines = 2;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_DOUBLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 1);

    game_state.level = 4;
    num_lines = 3;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_TRIPLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 2);

    game_state.level = 5;
    num_lines = 4;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == 0);

    // force a t-spin mini
    game_state.board[top_left_y][top_left_x] = 1;
    game_state.board[top_left_y][top_left_x + 2] = 0;
    game_state.board[top_left_y + 2][top_left_x] = 1;
    game_state.board[top_left_y + 2][top_left_x + 2] = 1;

    game_state.level = 6;
    num_lines = 0;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_MINI_ZERO_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 2);

    game_state.level = 7;
    num_lines = 1;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_MINI_SINGLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 3);

    game_state.level = 8;
    num_lines = 2;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == T_SPIN_MINI_DOUBLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 4);

    game_state.level = 9;
    num_lines = 3;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == 0);

    game_state.level = 10;
    num_lines = 4;
    points = game_state_calc_t_spin_points(&game_state, num_lines);
    ASSERT(points == 0);

    return true;
}

bool test_game_state_calc_line_clear_points(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    game_state.level = 1;
    uint64_t num_lines = 0;
    uint64_t points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == 0);

    game_state.level = 2;
    num_lines = 1;
    points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == SINGLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == -1);

    game_state.level = 3;
    num_lines = 2;
    points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == DOUBLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == -1);

    game_state.level = 4;
    num_lines = 3;
    points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == TRIPLE_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == -1);

    game_state.level = 5;
    num_lines = 4;
    points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == TETRIS_POINTS * game_state.level);
    ASSERT(game_state.difficult_clear_combo == 0);

    game_state.curr_piece = piece_get(T, (BOARD_H-1)/2, (BOARD_W-1)/2);
    int top_left_y = game_state.curr_piece.y - game_state.curr_piece.n / 2; 
    int top_left_x = game_state.curr_piece.x - game_state.curr_piece.n / 2;

    // force a t-spin
    game_state.t_rotation_test_num = 1;
    game_state.curr_piece.r = 0;
    game_state.board[top_left_y][top_left_x] = 1;
    game_state.board[top_left_y][top_left_x + 2] = 1;
    game_state.board[top_left_y + 2][top_left_x] = 1;
    game_state.board[top_left_y + 2][top_left_x + 2] = 0;

    game_state.level = 6;
    num_lines = 4;
    points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == 0);

    // force a t-spin mini
    game_state.board[top_left_y][top_left_x] = 1;
    game_state.board[top_left_y][top_left_x + 2] = 0;
    game_state.board[top_left_y + 2][top_left_x] = 1;
    game_state.board[top_left_y + 2][top_left_x + 2] = 1;

    game_state.level = 7;
    num_lines = 4;
    points = game_state_calc_line_clear_points(&game_state, num_lines);
    ASSERT(points == 0);    

    return true;
}

bool test_game_state_calc_all_clear_points(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            game_state.board[i][j] = 0;
        }
    }
    
    game_state.level = 1;
    uint64_t num_lines = 0;
    uint64_t points = game_state_calc_all_clear_points(&game_state, num_lines);
    ASSERT(points == 0);

    game_state.level = 2;
    num_lines = 1;
    points = game_state_calc_all_clear_points(&game_state, num_lines);
    ASSERT(points == SINGLE_ALL_CLEAR_POINTS * game_state.level);
    ASSERT(game_state.tetris_all_clear_combo == -1);

    game_state.level = 3;
    num_lines = 2;
    points = game_state_calc_all_clear_points(&game_state, num_lines);
    ASSERT(points == DOUBLE_ALL_CLEAR_POINTS * game_state.level);
    ASSERT(game_state.tetris_all_clear_combo == -1);

    game_state.level = 4;
    num_lines = 3;
    points = game_state_calc_all_clear_points(&game_state, num_lines);
    ASSERT(points == TRIPLE_ALL_CLEAR_POINTS * game_state.level);
    ASSERT(game_state.tetris_all_clear_combo == -1);

    game_state.level = 5;
    num_lines = 4;
    points = game_state_calc_all_clear_points(&game_state, num_lines);
    ASSERT(points == TETRIS_ALL_CLEAR_POINTS * game_state.level);
    ASSERT(game_state.tetris_all_clear_combo == 0);

    game_state.level = 6;
    num_lines = 4;
    points = game_state_calc_all_clear_points(&game_state, num_lines);
    ASSERT(points == B2B_TETRIS_ALL_CLEAR_POINTS * game_state.level);
    ASSERT(game_state.tetris_all_clear_combo == 1);

    return true;
}

bool test_game_state_calc_combo_points(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    game_state.level = 1;
    uint64_t num_lines = 1;
    uint64_t points = game_state_calc_combo_points(&game_state, num_lines);
    ASSERT(points == COMBO_POINTS * game_state.combo * game_state.level);
    ASSERT(game_state.combo == 0);

    game_state.level = 2;
    num_lines = 2;
    points = game_state_calc_combo_points(&game_state, num_lines);
    ASSERT(points == COMBO_POINTS * game_state.combo * game_state.level);
    ASSERT(game_state.combo == 1);

    game_state.level = 3;
    num_lines = 3;
    points = game_state_calc_combo_points(&game_state, num_lines);
    ASSERT(points == COMBO_POINTS * game_state.combo * game_state.level);
    ASSERT(game_state.combo == 2);

    game_state.level = 4;
    num_lines = 4;
    points = game_state_calc_combo_points(&game_state, num_lines);
    ASSERT(points == COMBO_POINTS * game_state.combo * game_state.level);
    ASSERT(game_state.combo == 3);

    game_state.level = 5;
    num_lines = 0;
    points = game_state_calc_combo_points(&game_state, num_lines);
    ASSERT(points == 0);
    ASSERT(game_state.combo == -1);

    return true;
}

bool test_game_state_calc_difficult_clear_mult(void) {
    GameState game_state = game_state_get();
    game_state_start(&game_state);

    uint64_t num_lines = 0;
    float mult = game_state_calc_difficult_clear_mult(&game_state, num_lines);
    ASSERT(mult == 1.0);

    num_lines = 1;
    game_state.difficult_clear_combo = 1;
    mult = game_state_calc_difficult_clear_mult(&game_state, num_lines);
    ASSERT(mult == 1.5);

    return true;
}
