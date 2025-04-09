#ifndef TEST_DRAW_GAME_VFX_H
#define TEST_DRAW_GAME_VFX_H
#include "vfx.h"

#include <stdint.h>

/** @file
 ** @brief Collection of VFX test cases.
 **/

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_i_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_j_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_l_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_o_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_s_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_t_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_lock_z_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_lock_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_line_clear_single.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_line_clear_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_line_clear_double.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_line_clear_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_line_clear_triple.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_line_clear_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_line_clear_tetris.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_line_clear_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_line_clear_t_spin.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_line_clear_t_spin(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_line_clear_all_clear.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_line_clear_all_clear(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_i_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_j_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_l_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_o_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_s_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_t_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_hold_z_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_hold_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_i_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_j_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_l_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_o_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_s_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_t_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_next_z_piece.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_next_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_single.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_double.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_triple.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_tetris.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin with 1 
 ** line cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin with 2 
 ** lines cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin with 3 
 ** lines cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin with 
 ** t-spin mini.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin_mini(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin with 
 ** t-spin mini and 1 line cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin_mini_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_t_spin with 
 ** t-spin mini and 2 lines cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_t_spin_mini_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_all_clear with
 ** 1 line cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_all_clear_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_all_clear with
 ** 2 lines cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_all_clear_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_all_clear with
 ** 3 lines cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_all_clear_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_action_all_clear with
 ** 4 lines cleared.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_action_all_clear_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_combo.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_combo(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_b2b_combo.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_b2b_combo(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_points.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_points(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_level_up.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_level_up(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_stats_lines.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_stats_lines(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Enable VFX and register draw function draw_vfx_stats_level.
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param vfx The VFX object to be modified.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_vfx_stats_level(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

#endif
