#ifndef TEST_GAME_STATE_H
#define TEST_GAME_STATE_H
#include <stdbool.h>

/** @file
 ** @brief Collection of unit test cases testing game_state.c / game_state.h
 **/


/**
 ** @brief Test function game_state_get.
 **/
bool test_game_state_get(void);

/**
 ** @brief Test function game_state_init.
 **/
bool test_game_state_init(void);

/**
 ** @brief Test function game_state_start.
 **/
bool test_game_state_start(void);

/**
 ** @brief Test function game_state_reset.
 **/
bool test_game_state_reset(void);

/**
 ** @brief Test function game_state_reset_vfx_vars.
 **/
bool test_game_state_reset_vfx_vars(void);

/**
 ** @brief Test function game_state_generate_next_queue.
 **/
bool test_game_state_generate_next_queue(void);

/**
 ** @brief Test function game_state_load_next_piece.
 **/
bool test_game_state_load_next_piece(void);

/**
 ** @brief Test function game_state_spawn_curr_piece.
 **/
bool test_game_state_spawn_curr_piece(void);

/**
 ** @brief Test function game_state_hold_piece.
 **/
bool test_game_state_hold_piece(void);

/**
 ** @brief Test function game_state_check_collision.
 **/
bool test_game_state_check_collision(void);

/**
 ** @brief Test function game_state_check_curr_piece_grounded.
 **/
bool test_game_state_check_curr_piece_grounded(void);

/**
 ** @brief Test function game_state_move_curr_piece.
 **/
bool test_game_state_move_curr_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece.
 **/
bool test_game_state_rotate_curr_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being an I piece.
 **/
bool test_game_state_rotate_curr_piece_srs_i_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being a J piece.
 **/
bool test_game_state_rotate_curr_piece_srs_j_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being an L piece.
 **/
bool test_game_state_rotate_curr_piece_srs_l_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being an O piece.
 **/
bool test_game_state_rotate_curr_piece_srs_o_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being an S piece.
 **/
bool test_game_state_rotate_curr_piece_srs_s_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being a T piece.
 **/
bool test_game_state_rotate_curr_piece_srs_t_piece(void);

/**
 ** @brief Test function game_state_rotate_curr_piece_srs with the current piece
 ** being a Z piece.
 **/
bool test_game_state_rotate_curr_piece_srs_z_piece(void);

/**
 ** @brief Test function game_state_hard_drop_curr_piece.
 **/
bool test_game_state_hard_drop_curr_piece(void);

/**
 ** @brief Test function game_state_lock_curr_piece.
 **/
bool test_game_state_lock_curr_piece(void);

/**
 ** @brief Test function game_state_apply_stack_gravity.
 **/
bool test_game_state_apply_stack_gravity(void);

/**
 ** @brief Test function game_state_clear_line.
 **/
bool test_game_state_clear_line(void);

/**
 ** @brief Test function game_state_clear_lines.
 **/
bool test_game_state_clear_lines(void);

/**
 ** @brief Test function game_state_apply_gravity.
 **/
bool test_game_state_apply_gravity(void);

/**
 ** @brief Test function game_state_apply_soft_drop_gravity.
 **/
bool test_game_state_apply_soft_drop_gravity(void);

/**
 ** @brief Test function game_state_soft_drop_curr_piece.
 **/
bool test_game_state_soft_drop_curr_piece(void);

/**
 ** @brief Test function game_state_update_ghost_piece.
 **/
bool test_game_state_update_ghost_piece(void);

/**
 ** @brief Test function game_state_check_t_spin.
 **/
bool test_game_state_check_t_spin(void);

/**
 ** @brief Test function game_state_check_t_spin_mini.
 **/
bool test_game_state_check_t_spin_mini(void);

/**
 ** @brief Test function game_state_check_empty_board.
 **/
bool test_game_state_check_empty_board(void);

/**
 ** @brief Test function game_state_calc_t_spin_points.
 **/
bool test_game_state_calc_t_spin_points(void);

/**
 ** @brief Test function game_state_calc_line_clear_points.
 **/
bool test_game_state_calc_line_clear_points(void);

/**
 ** @brief Test function game_state_calc_all_clear_points.
 **/
bool test_game_state_calc_all_clear_points(void);

/**
 ** @brief Test function game_state_calc_combo_points.
 **/
bool test_game_state_calc_combo_points(void);

/**
 ** @brief Test function game_state_calc_difficult_clear_mult.
 **/
bool test_game_state_calc_difficult_clear_mult(void);

#endif