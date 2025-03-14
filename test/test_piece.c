#include "test_piece.h"
#include "piece.h"

#include "utils/assert_trace.h"

#include <stdbool.h>
#include <stdio.h>


bool test_piece_get(void) {
    Piece piece = piece_get(I, 2, 3);
    ASSERT(piece.shape == I);
    ASSERT(piece.y == 2);
    ASSERT(piece.x == 3);
    return true;
}

bool test_piece_init(void) {
    Piece* piece = piece_init(J, 4, 5);
    ASSERT(piece->shape == J);
    ASSERT(piece->y == 4);
    ASSERT(piece->x == 5);
    piece_destroy(piece);
    return true;
}

bool test_piece_move(void) {
    Piece piece = piece_get(I, 1, 2);
    piece_move(&piece, 10, 20);
    ASSERT(piece.y == 10);
    ASSERT(piece.x == 20);
    return true;
}

bool test_compute_r_index_right_rotation(void) {
    ASSERT(compute_r_index(0, RIGHT) == 1);
    ASSERT(compute_r_index(1, RIGHT) == 2);
    ASSERT(compute_r_index(2, RIGHT) == R_MAX-1);
    ASSERT(compute_r_index(R_MAX-1, RIGHT) == 0);
    return true;
}

bool test_compute_r_index_left_rotation(void) {
    ASSERT(compute_r_index(0, LEFT) == R_MAX-1);
    ASSERT(compute_r_index(R_MAX-1, LEFT) == 2);
    ASSERT(compute_r_index(2, LEFT) == 1);
    ASSERT(compute_r_index(1, LEFT) == 0);
    return true;
}

bool test_piece_rotate_right(void) {
    Piece piece = piece_get(I, 0, 0);
    ASSERT(piece.r == 0);
    piece_rotate(&piece, RIGHT);
    ASSERT(piece.r == 1);
    piece_rotate(&piece, RIGHT);
    ASSERT(piece.r == 2);
    piece_rotate(&piece, RIGHT);
    ASSERT(piece.r == R_MAX-1);
    piece_rotate(&piece, RIGHT);
    ASSERT(piece.r == 0);
    return true;
}

bool test_piece_rotate_left(void) {
    Piece piece = piece_get(I, 0, 0);
    ASSERT(piece.r == 0);
    piece_rotate(&piece, LEFT);
    ASSERT(piece.r == R_MAX-1);
    piece_rotate(&piece, LEFT);
    ASSERT(piece.r == 2);
    piece_rotate(&piece, LEFT);
    ASSERT(piece.r == 1);
    piece_rotate(&piece, LEFT);
    ASSERT(piece.r == 0);
    return true;
}

bool test_shape_to_char(void) {
    ASSERT(shape_to_char(I) == 'I');
    ASSERT(shape_to_char(J) == 'J');
    ASSERT(shape_to_char(L) == 'L');
    ASSERT(shape_to_char(O) == 'O');
    ASSERT(shape_to_char(S) == 'S');
    ASSERT(shape_to_char(T) == 'T');
    ASSERT(shape_to_char(Z) == 'Z');
    return true;
}
