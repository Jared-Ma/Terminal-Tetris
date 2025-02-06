#ifndef DRAW_H
#define DRAW_H
#include <ncurses.h>
#include "piece.h"

#define HOLD_WINDOW_H 6
#define HOLD_WINDOW_W 14
#define STATS_WINDOW_H 16
#define STATS_WINDOW_W 14
#define BOARD_WINDOW_H 22
#define BOARD_WINDOW_W 22
#define NEXT_WINDOW_H 6
#define NEXT_WINDOW_W 14
#define CONTROLS_WINDOW_H 16
#define CONTROLS_WINDOW_W 14


WINDOW *draw_hold_window(int height, int width, int y, int x);

WINDOW *draw_stats_window(int height, int width, int y, int x);

WINDOW *draw_board_window(int height, int width, int y, int x);

WINDOW *draw_next_window(int height, int width, int y, int x);

WINDOW *draw_controls_window(int height, int width, int y, int x);

void draw_board_piece(WINDOW *window, Piece* piece);

void draw_board_empty(WINDOW *window);

void draw_next_piece(WINDOW *window, Piece *piece);

void draw_next_window_empty(WINDOW *window);

#endif
