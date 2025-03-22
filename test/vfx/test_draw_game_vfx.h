#ifndef TEST_DRAW_GAME_VFX_H
#define TEST_DRAW_GAME_VFX_H
#include "vfx.h"

#include <stdint.h>


void test_vfx_lock_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_lock_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_lock_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_lock_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_lock_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_lock_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_lock_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_line_clear_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_line_clear_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_line_clear_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_line_clear_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_line_clear_t_spin(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_line_clear_all_clear(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_hold_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_i_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_j_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_l_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_o_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_s_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_t_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_next_z_piece(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin_mini(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin_mini_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_t_spin_mini_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_all_clear_single(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_all_clear_double(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_all_clear_triple(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_action_all_clear_tetris(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_combo(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_b2b_combo(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_points(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_level_up(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_stats_lines(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

void test_vfx_stats_level(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

#endif
