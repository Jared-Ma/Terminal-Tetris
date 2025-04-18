#include "test_draw.h"
#include "test_game_state.h"
#include "test_piece.h"
#include "test_stats.h"
#include "test_vfx.h"
#include "unit_test.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Number of tests to be run. 
#define NUM_TESTS 80


int main(void) {
    UnitTest unit_tests[NUM_TESTS] = {
        UNIT_TEST(test_game_window_get),
        UNIT_TEST(test_game_window_init),

        UNIT_TEST(test_piece_get),
        UNIT_TEST(test_piece_init),
        UNIT_TEST(test_piece_move),
        UNIT_TEST(test_compute_r_index_right_rotation),
        UNIT_TEST(test_compute_r_index_left_rotation),
        UNIT_TEST(test_piece_rotate_right),
        UNIT_TEST(test_piece_rotate_left),
        UNIT_TEST(test_shape_to_char),

        UNIT_TEST(test_stats_get),
        UNIT_TEST(test_stats_init),
        UNIT_TEST(test_stats_reset),
        UNIT_TEST(test_stats_update),

        UNIT_TEST(test_game_state_get),
        UNIT_TEST(test_game_state_init),
        UNIT_TEST(test_game_state_start),
        UNIT_TEST(test_game_state_reset),
        UNIT_TEST(test_game_state_reset_vfx_vars),
        UNIT_TEST(test_game_state_generate_next_queue),
        UNIT_TEST(test_game_state_load_next_piece),
        UNIT_TEST(test_game_state_spawn_curr_piece),
        UNIT_TEST(test_game_state_hold_piece),
        UNIT_TEST(test_game_state_check_collision),
        UNIT_TEST(test_game_state_check_curr_piece_grounded),
        UNIT_TEST(test_game_state_move_curr_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_i_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_j_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_l_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_o_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_s_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_t_piece),
        UNIT_TEST(test_game_state_rotate_curr_piece_srs_z_piece),
        UNIT_TEST(test_game_state_hard_drop_curr_piece),
        UNIT_TEST(test_game_state_lock_curr_piece),
        UNIT_TEST(test_game_state_apply_stack_gravity),
        UNIT_TEST(test_game_state_clear_line),
        UNIT_TEST(test_game_state_clear_lines),
        UNIT_TEST(test_game_state_apply_gravity),
        UNIT_TEST(test_game_state_apply_soft_drop_gravity),
        UNIT_TEST(test_game_state_soft_drop_curr_piece),
        UNIT_TEST(test_game_state_update_ghost_piece),
        UNIT_TEST(test_game_state_check_t_spin),
        UNIT_TEST(test_game_state_check_t_spin_mini),
        UNIT_TEST(test_game_state_check_empty_board),
        UNIT_TEST(test_game_state_calc_t_spin_points),
        UNIT_TEST(test_game_state_calc_line_clear_points),
        UNIT_TEST(test_game_state_calc_all_clear_points),
        UNIT_TEST(test_game_state_calc_combo_points),
        UNIT_TEST(test_game_state_calc_difficult_clear_mult),

        UNIT_TEST(test_vfx_get),
        UNIT_TEST(test_vfx_init),
        UNIT_TEST(test_vfx_enable),
        UNIT_TEST(test_vfx_disable),
        UNIT_TEST(test_vfx_check_lock_piece),
        UNIT_TEST(test_vfx_enable_lock_piece),
        UNIT_TEST(test_vfx_check_line_clear),
        UNIT_TEST(test_vfx_enable_line_clear),
        UNIT_TEST(test_vfx_check_hold_piece),
        UNIT_TEST(test_vfx_enable_hold_piece),
        UNIT_TEST(test_vfx_check_next_piece),
        UNIT_TEST(test_vfx_enable_next_piece),
        UNIT_TEST(test_vfx_check_action),
        UNIT_TEST(test_vfx_enable_action_line_clear),
        UNIT_TEST(test_vfx_enable_action_t_spin),
        UNIT_TEST(test_vfx_enable_action_t_spin_mini),
        UNIT_TEST(test_vfx_enable_action_all_clear),
        UNIT_TEST(test_vfx_check_combo),
        UNIT_TEST(test_vfx_enable_combo),
        UNIT_TEST(test_vfx_check_b2b_combo),
        UNIT_TEST(test_vfx_enable_b2b_combo),
        UNIT_TEST(test_vfx_check_points),
        UNIT_TEST(test_vfx_enable_points),
        UNIT_TEST(test_vfx_check_level_up),
        UNIT_TEST(test_vfx_enable_level_up),
        UNIT_TEST(test_vfx_check_stats_lines),
        UNIT_TEST(test_vfx_enable_stats_lines),
        UNIT_TEST(test_vfx_check_stats_level),
        UNIT_TEST(test_vfx_enable_stats_level)
    };

    size_t failed_unit_tests[NUM_TESTS] = { 0 };

    size_t num_unit_tests_passed = 0;
    size_t num_unit_tests_failed = 0; 

    for (size_t i = 0; i < NUM_TESTS; ++i) {
        bool test_result = run_unit_test(i+1, unit_tests[i]);
        if (test_result) {
            num_unit_tests_passed++;
        } else {
            failed_unit_tests[num_unit_tests_failed++] = i;
        }
    } 
    
    printf("%lu / %u unit tests passed\n", num_unit_tests_passed, NUM_TESTS);
    
    if (num_unit_tests_failed > 0) {
        printf("\nFailed unit tests:\n");
        for (size_t i = 0; i < num_unit_tests_failed; ++i) {
            printf("%lu - %s\n", failed_unit_tests[i]+1, unit_tests[failed_unit_tests[i]].test_name);
        }
    }

    return EXIT_SUCCESS;
}
