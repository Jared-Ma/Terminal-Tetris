#ifndef PIECE_H
#define PIECE_H
#include <stdbool.h>
#include <stdint.h>


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
    uint8_t y;
    uint8_t x;
    uint8_t n;
    uint8_t r;
    bool M[4][5][5];
};

typedef struct Piece Piece;

Piece piece_init(Shape shape, uint8_t y, uint8_t x);

#endif
