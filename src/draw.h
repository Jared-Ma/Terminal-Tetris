#ifndef DRAW_H
#define DRAW_H
#include "game_state.h"
#include "stats.h"

#include <ncurses.h>
#include <stdint.h>


extern const int8_t GAME_H;
extern const int8_t GAME_W;

extern const int8_t BOARD_WINDOW_H;
extern const int8_t BOARD_WINDOW_W;
extern const int8_t BOARD_WINDOW_Y;
extern const int8_t BOARD_WINDOW_X;

extern const int8_t HOLD_WINDOW_H;
extern const int8_t HOLD_WINDOW_W;
extern const int8_t HOLD_WINDOW_Y;
extern const int8_t HOLD_WINDOW_X;

extern const int8_t NEXT_WINDOW_H;
extern const int8_t NEXT_WINDOW_W;
extern const int8_t NEXT_WINDOW_Y;
extern const int8_t NEXT_WINDOW_X;

extern const int8_t STATS_WINDOW_H;
extern const int8_t STATS_WINDOW_W;
extern const int8_t STATS_WINDOW_Y;
extern const int8_t STATS_WINDOW_X;

extern const int8_t CONTROLS_WINDOW_H;
extern const int8_t CONTROLS_WINDOW_W;
extern const int8_t CONTROLS_WINDOW_Y;
extern const int8_t CONTROLS_WINDOW_X;

extern const int8_t PAUSE_WINDOW_H;
extern const int8_t PAUSE_WINDOW_W;
extern const int8_t PAUSE_WINDOW_Y;
extern const int8_t PAUSE_WINDOW_X;

extern const int8_t GAME_OVER_WINDOW_H;
extern const int8_t GAME_OVER_WINDOW_W;
extern const int8_t GAME_OVER_WINDOW_Y;
extern const int8_t GAME_OVER_WINDOW_X;

extern const int8_t PAUSE_WINDOW_H;
extern const int8_t PAUSE_WINDOW_W;
extern const int8_t PAUSE_WINDOW_Y;
extern const int8_t PAUSE_WINDOW_X;

extern const int8_t GAME_OVER_WINDOW_H;
extern const int8_t GAME_OVER_WINDOW_W;
extern const int8_t GAME_OVER_WINDOW_Y;
extern const int8_t GAME_OVER_WINDOW_X;

extern const int8_t DEBUG_WINDOW_H;
extern const int8_t DEBUG_WINDOW_W;
extern const int8_t DEBUG_WINDOW_Y;
extern const int8_t DEBUG_WINDOW_X;

extern const int8_t STATS_LINES_Y;
extern const int8_t STATS_LINES_X;
extern const int8_t STATS_LEVEL_Y;
extern const int8_t STATS_LEVEL_X;

extern const char* HOLD_TITLE;
extern const char* NEXT_TITLE;

extern const int16_t COLOR_PAIR_DEFAULT;
extern const int16_t COLOR_PAIR_CYAN;
extern const int16_t COLOR_PAIR_BLUE;
extern const int16_t COLOR_PAIR_ORANGE;
extern const int16_t COLOR_PAIR_YELLOW;
extern const int16_t COLOR_PAIR_GREEN;
extern const int16_t COLOR_PAIR_MAGENTA;
extern const int16_t COLOR_PAIR_RED;

extern const uint16_t LOCK_DELAY_DIM_MAX;
extern const uint16_t LOCK_DELAY_DIM_MIN;
extern const uint16_t LOCK_DELAY_STANDOUT_MAX;
extern const uint16_t LOCK_DELAY_STANDOUT_MIN;

struct GameWindow {
    WINDOW* border;
    WINDOW* content;
    int8_t border_h;
    int8_t border_w;
    int8_t border_y;
    int8_t border_x;
    int8_t content_h;
    int8_t content_w;
    int8_t content_y;
    int8_t content_x;
};

typedef struct GameWindow GameWindow;

GameWindow game_window_get(int height, int width, int y, int x);

GameWindow* game_window_init(int height, int width, int y, int x);

void game_window_destroy(GameWindow* game_window);

void game_window_refresh(GameWindow* game_window);

void draw_window_border(GameWindow* game_window, int16_t color_pair);

void draw_window_title(GameWindow* game_window, const char* title, int16_t color_pair);

void draw_board_window(GameWindow* board_window);

void draw_hold_window(GameWindow* game_window);

void draw_next_window(GameWindow* next_window);

void draw_stats_window(GameWindow* stats_window);

void draw_controls_window(GameWindow* controls_window);

void draw_pause_window(GameWindow* pause_window);

void draw_game_over_window(GameWindow* game_over_window);

void draw_debug_window(GameWindow* debug_window);

void draw_board_state(GameWindow* board_window, GameState* game_state);

void draw_buffer_zone_line(GameWindow* board_window);

void draw_board_stack(GameWindow* board_window, GameState* game_state);

void draw_curr_piece(GameWindow* board_window, GameState* game_state);

void draw_ghost_piece(GameWindow* board_window, GameState* game_state);

void draw_score(GameWindow* board_window, GameState* game_state);

void draw_hold_piece(GameWindow* hold_window, GameState* game_state);

void draw_next_piece(GameWindow* next_window, GameState* game_state);

void draw_stats(GameWindow* stats_window, GameState* game_state, Stats* stats);

void draw_pause_stats(GameWindow* stats_window, Stats* stats);

void draw_debug_variables(GameWindow* debug_window, GameState* game_state, Stats* stats);

#endif
