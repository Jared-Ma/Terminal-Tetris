#ifndef TEST_PIECE_H
#define TEST_PIECE_H
#include <stdbool.h>

/** @file
 ** @brief Collection of unit test cases testing piece.c / piece.h
 **/


/**
 ** @brief Test function piece_get.
 **/
bool test_piece_get(void);

/**
 ** @brief Test function piece_init.
 **/
bool test_piece_init(void);

/**
 ** @brief Test function piece_move.
 **/
bool test_piece_move(void);

/**
 ** @brief Test function compute_r_index_right_rotation.
 **/
bool test_compute_r_index_right_rotation(void);

/**
 ** @brief Test function compute_r_index_left_rotation.
 **/
bool test_compute_r_index_left_rotation(void);

/**
 ** @brief Test function piece_rotate with the rotation direction being right.
 **/
bool test_piece_rotate_right(void);

/**
 ** @brief Test function piece_rotate with the rotation direction being left.
 **/
bool test_piece_rotate_left(void);

/**
 ** @brief Test function shape_to_char.
 **/
bool test_shape_to_char(void);

#endif
