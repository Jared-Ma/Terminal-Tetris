#ifndef PIECE_H
#define PIECE_H
#include <stdbool.h>
#include <stdint.h>

/** @file
 ** @brief Constants that describe Piece object parameters, and the functions 
 ** that interface with and modify the Piece object. 
 **/

// Number of possible tetromino shapes.
#define NUM_SHAPES 7

// Max length of the matrix containing a piece.
#define N_MAX 5

// Number of possible orientations of a piece.
#define R_MAX 4


/**
 ** @brief Named constants for each tetromino shape, starting from 1.  
 **/
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

/**
 ** @brief Named constants for both right and left rotations.  
 **/
enum Rotation {
    RIGHT,
    LEFT
};

typedef enum Rotation Rotation;

/**
 ** @brief Piece consists of the location of the piece, the size of the nxn 
 ** matrix, its length when oriented horizontally, its current orientation, and 
 ** the matrix describing the location of the minos forming the piece. 
 **/
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

/**
 ** @brief Initialize the specified Piece object.
 ** 
 ** @param shape The shape of the Piece desired.
 ** @param y The initial y-coordinate of the Piece object.
 ** @param x The initial x-coordinate of the Piece object.
 ** 
 ** @return The initialized Piece object.
 **/
Piece piece_get(Shape shape, int8_t y, int8_t x);

/**
 ** @brief Allocate memory and initialize a Piece object.
 ** 
 ** @param shape The shape of the Piece desired.
 ** @param y The initial y-coordinate of the Piece object.
 ** @param x The initial x-coordinate of the Piece object.
 ** 
 ** @return A pointer to the allocated Piece object.
 **/
Piece* piece_init(Shape shape, int8_t y, int8_t x);

/** 
 ** @brief Deallocate the Piece object @piece.
 **
 ** @param piece The Piece object to be deallocated.
 **/
void piece_destroy(Piece* piece);

/** 
 ** @brief Print values of each member in @piece.
 **
 ** @param piece The Piece object to be read. 
 **/
void piece_debug_print(const Piece* piece);

/**
 ** @brief Move @piece to (@y, @x).
 **
 ** @param piece The piece object to be modified.
 ** @param y The y-coordinate to move @piece to.
 ** @param x The x-coordinate to move @piece to.
 **/
void piece_move(Piece* piece, int8_t y, int8_t x);

/**
 ** @brief Calculate the resulting orientation index @r after the rotation
 ** @rotation.
 **
 ** @param r The prior orientation index.
 ** @param rotation The direction to rotate in.
 **
 ** @return The resulting orientation index.  
 **/
uint8_t compute_r_index(uint8_t r, Rotation rotation);

/**
 ** @brief Set the orientation index of @piece to 0.
 ** 
 ** @param piece The Piece object to be modified.
 **/
void piece_reset_rotation(Piece* piece);

/**
 ** @brief Update the orientation index of @piece depending on @rotation.
 **
 ** @param piece The Piece object to be modified.
 ** @param rotation The direction to rotate @piece in.
 **/
void piece_rotate(Piece* piece, Rotation rotation);

/**
 ** @brief Converts named constant @shape to character.
 **
 ** @param shape The shape to convert.
 **
 ** @return The corresponding character.
 **/
char shape_to_char(Shape shape);

#endif
