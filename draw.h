#ifndef DRAW_H
#define DRAW_H
#include <ncurses.h>
#include "piece.h"
#include "stats.h"

#define HOLD_WINDOW_H 6
#define HOLD_WINDOW_W 14
#define STATS_WINDOW_H 16
#define STATS_WINDOW_W 14
#define BOARD_WINDOW_H 24
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

void draw_paused_text(WINDOW* window, GameState* game_state);

void draw_game_over_text(WINDOW* window, GameState* game_state);

void clear_window(WINDOW* window);

void draw_buffer_zone(WINDOW* window, GameState* game_state);

void draw_board_state(WINDOW* window, GameState* game_state);

void draw_board_stack(WINDOW *window, GameState* game_state);

void draw_curr_piece(WINDOW* window, GameState* game_state);

void draw_hold_piece(WINDOW* window, GameState* game_state);

void draw_next_piece(WINDOW* window, GameState* game_state);

void draw_ghost_piece(WINDOW* window, GameState* game_state);

void draw_stats(WINDOW* window, Stats* stats);

void draw_stats_time(WINDOW* window, Stats* stats);

void draw_stats_score(WINDOW* window, Stats* stats);

void draw_stats_lines(WINDOW* window, Stats* stats);

void draw_stats_level(WINDOW* window, Stats* stats);

void draw_stats_combo(WINDOW* window, Stats* stats);

#endif
