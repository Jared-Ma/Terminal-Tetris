#ifndef TEST_GAME_STATE_H
#define TEST_GAME_STATE_H
#include <stdbool.h>


bool test_game_state_get(void);

bool test_game_state_init(void);

bool test_game_state_start(void);

bool test_game_state_restart(void);

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

#endif