#ifndef TEST_DRAW_GAME_UI_H
#define TEST_DRAW_GAME_UI_H

#include <stdint.h>

/** @file
 ** @brief Collection of UI test cases.
 **/

 
/**
 ** @brief Test draw function draw_hold_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_board_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_board_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_stats_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_stats_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_help_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_help_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_main_menu_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_main_menu_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_pause_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_pause_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_game_over_window.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_game_over_window(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_board_stack.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_board_stack(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_buffer_zone_line.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_buffer_zone_line(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being an I
 ** piece. 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_i_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being a J
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_j_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being an L
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_l_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being an O
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_o_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being an S
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_s_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being a T
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_t_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the current piece being a Z
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_z_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the lock delay timer in
 ** between LOCK_DELAY_DIM_MIN and LOCK_DELAY_DIM_MAX.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_lock_delay_dim(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_curr_piece with the lock delay timer in
 ** between LOCK_DELAY_STANDOUT_MIN and LOCK_DELAY_STANDOUT_MAX.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_curr_piece_lock_delay_standout(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being an I
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_i_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being a J
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_j_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being an L
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_l_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being an O
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_o_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being an S
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_s_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being a T
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_t_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_ghost_piece with the ghost piece being a Z
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_ghost_piece_z_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_score.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_score(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_board_state.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_board_state(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an I
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_i_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being a J
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_j_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an L
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_l_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an O
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_o_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an S
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_s_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being a T
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_t_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being a Z
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_z_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an I
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_i_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being a J
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_j_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an L
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_l_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an O
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_o_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being an S
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_s_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being a T
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_t_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_hold_piece with the hold piece being a Z
 ** piece and hold being blocked.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_hold_piece_z_piece_blocked(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being an I
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_i_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being a J
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_j_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being an L
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_l_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being an O
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_o_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being an S
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_s_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being a T
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_t_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_next_piece with the next piece being a Z
 ** piece.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_next_piece_z_piece(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_stats.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_stats(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Test draw function draw_pause_stats.
 ** 
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void test_draw_pause_stats(int8_t y_offset, int8_t x_offset);

#endif
