#ifndef TEST_GAME_STATE_H
#define TEST_GAME_STATE_H
#include <stdbool.h>


bool test_game_state_get(void);

bool test_game_state_init(void);

bool test_game_state_start(void);

bool test_game_state_reset(void);

bool test_game_state_reset_vfx_vars(void);

bool test_game_state_generate_next_queue(void);

bool test_game_state_load_next_piece(void);

bool test_game_state_spawn_curr_piece(void);

bool test_game_state_hold_piece(void);

bool test_game_state_check_collision(void);

bool test_game_state_check_curr_piece_grounded(void);

bool test_game_state_move_curr_piece(void);

bool test_game_state_rotate_curr_piece(void);

bool test_game_state_rotate_curr_piece_srs_i_piece(void);

bool test_game_state_rotate_curr_piece_srs_j_piece(void);

bool test_game_state_rotate_curr_piece_srs_l_piece(void);

bool test_game_state_rotate_curr_piece_srs_o_piece(void);

bool test_game_state_rotate_curr_piece_srs_s_piece(void);

bool test_game_state_rotate_curr_piece_srs_t_piece(void);

bool test_game_state_rotate_curr_piece_srs_z_piece(void);

bool test_game_state_hard_drop_curr_piece(void);

bool test_game_state_lock_curr_piece(void);

bool test_game_state_apply_stack_gravity(void);

bool test_game_state_clear_line(void);

bool test_game_state_clear_lines(void);

bool test_game_state_apply_gravity(void);

bool test_game_state_apply_soft_drop_gravity(void);

bool test_game_state_soft_drop_curr_piece(void);

bool test_game_state_update_ghost_piece(void);

bool test_game_state_check_t_spin(void);

bool test_game_state_check_t_spin_mini(void);

bool test_game_state_check_empty_board(void);

bool test_game_state_calc_t_spin_points(void);

bool test_game_state_calc_line_clear_points(void);

bool test_game_state_calc_all_clear_points(void);

bool test_game_state_calc_combo_points(void);

bool test_game_state_calc_difficult_clear_mult(void);

#endif