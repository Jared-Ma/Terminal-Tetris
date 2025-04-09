#ifndef TEST_VFX_H
#define TEST_VFX_H
#include <stdbool.h>

/** @file
 ** @brief Collection of unit test cases testing vfx.c / vfx.h
 **/


/**
 ** @brief Test function vfx_get.
 **/
bool test_vfx_get(void);

/**
 ** @brief Test function vfx_init.
 **/
bool test_vfx_init(void);

/**
 ** @brief Test function vfx_enable.
 **/
bool test_vfx_enable(void);

/**
 ** @brief Test function vfx_disable.
 **/
bool test_vfx_disable(void);

/**
 ** @brief Test function vfx_check_lock_piece.
 **/
bool test_vfx_check_lock_piece(void);

/**
 ** @brief Test function vfx_enable_lock_piece.
 **/
bool test_vfx_enable_lock_piece(void);

/**
 ** @brief Test function vfx_check_line_clear.
 **/
bool test_vfx_check_line_clear(void);

/**
 ** @brief Test function vfx_enable_line_clear.
 **/
bool test_vfx_enable_line_clear(void);

/**
 ** @brief Test function vfx_check_hold_piece.
 **/
bool test_vfx_check_hold_piece(void);

/**
 ** @brief Test function vfx_enable_hold_piece.
 **/
bool test_vfx_enable_hold_piece(void);

/**
 ** @brief Test function vfx_check_next_piece.
 **/
bool test_vfx_check_next_piece(void);

/**
 ** @brief Test function vfx_enable_next_piece.
 **/
bool test_vfx_enable_next_piece(void);

/**
 ** @brief Test function vfx_check_action.
 **/
bool test_vfx_check_action(void);

/**
 ** @brief Test function vfx_enable_action where the action is a line clear.
 **/
bool test_vfx_enable_action_line_clear(void);

/**
 ** @brief Test function vfx_enable_action where the action is a t-spin.
 **/
bool test_vfx_enable_action_t_spin(void);

/**
 ** @brief Test function vfx_enable_action where the action is a t-spin mini.
 **/
bool test_vfx_enable_action_t_spin_mini(void);

/**
 ** @brief Test function vfx_enable_action where the action is an all/perfect 
 ** clear.
 **/
bool test_vfx_enable_action_all_clear(void);

/**
 ** @brief Test function vfx_check_combo.
 **/
bool test_vfx_check_combo(void);

/**
 ** @brief Test function vfx_enable_combo.
 **/
bool test_vfx_enable_combo(void);

/**
 ** @brief Test function vfx_check_b2b_combo.
 **/
bool test_vfx_check_b2b_combo(void);

/**
 ** @brief Test function vfx_enable_b2b_combo.
 **/
bool test_vfx_enable_b2b_combo(void);

/**
 ** @brief Test function vfx_check_points.
 **/
bool test_vfx_check_points(void);

/**
 ** @brief Test function vfx_enable_points.
 **/
bool test_vfx_enable_points(void);

/**
 ** @brief Test function vfx_check_level_up.
 **/
bool test_vfx_check_level_up(void);

/**
 ** @brief Test function vfx_enable_level_up.
 **/
bool test_vfx_enable_level_up(void);

/**
 ** @brief Test function vfx_check_stats_lines.
 **/
bool test_vfx_check_stats_lines(void);

/**
 ** @brief Test function vfx_enable_stats_lines.
 **/
bool test_vfx_enable_stats_lines(void);

/**
 ** @brief Test function vfx_check_stats_level.
 **/
bool test_vfx_check_stats_level(void);

/**
 ** @brief Test function vfx_enable_stats_level.
 **/
bool test_vfx_enable_stats_level(void);

#endif
