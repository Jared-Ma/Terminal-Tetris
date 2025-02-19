#ifndef PIECE_H
#define PIECE_H
#include <stdlib.h>
#include <stdbool.h>

#define NUM_SHAPES 7
#define N_MAX 5
#define R_MAX 4


enum Shape {
    I = 1,
    J,
    L,
    O,
    S,
    T,
    Z
};

typedef enum Shape Shape;

enum Rotation {
    RIGHT,
    LEFT
};

typedef enum Rotation Rotation;

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

size_t compute_r_index(size_t r, Rotation rotation);

void piece_rotate(Piece* piece, Rotation rotation);

char shape_to_char(Shape shape);

#endif
