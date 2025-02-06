#ifndef PIECE_H
#define PIECE_H
#include <stdbool.h>
#include <stdint.h>

#define NUM_SHAPES 7
#define N_MAX 5
#define R_MAX 4


enum Shape {
    I,
    J,
    L,
    O,
    S,
    T,
    Z
};

typedef enum Shape Shape;

struct Piece {
    Shape shape;
    int y;
    int x;
    size_t n;
    size_t l;
    size_t r;
    bool M[R_MAX][N_MAX][N_MAX];
};

typedef struct Piece Piece;

Piece piece_get(Shape shape, int y, int x);

Piece* piece_init(Shape shape, int y, int x);

void piece_destroy(Piece* piece);

void piece_debug_print(Piece* piece);

void piece_move(Piece* piece, int y, int x);

void piece_rotate_right(Piece* piece);

void piece_rotate_left(Piece* piece);

char shape_to_char(Shape shape);

#endif
