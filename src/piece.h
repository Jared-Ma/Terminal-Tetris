#ifndef PIECE_H
#define PIECE_H
#include <stdbool.h>
#include <stdint.h>

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
    int8_t y;
    int8_t x;
    uint8_t n;
    uint8_t l;
    uint8_t r;
    bool M[R_MAX][N_MAX][N_MAX];
};

typedef struct Piece Piece;

Piece piece_get(Shape shape, int8_t y, int8_t x);

Piece* piece_init(Shape shape, int8_t y, int8_t x);

void piece_destroy(Piece* piece);

void piece_debug_print(Piece* piece);

void piece_move(Piece* piece, int8_t y, int8_t x);

uint8_t compute_r_index(uint8_t r, Rotation rotation);

void piece_reset_rotation(Piece* piece);

void piece_rotate(Piece* piece, Rotation rotation);

char shape_to_char(Shape shape);

#endif
