#ifndef DRAW_H
#define DRAW_H
#include "game_state.h"
#include "logger.h"
#include "stats.h"

#include <ncurses.h>
#include <stdint.h>

/** @file
 ** @brief Constants that describe GameWindow parameters and the functions to 
 ** interface with and draw to GameWindow objects.
 **/


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

extern const int8_t HELP_WINDOW_H;
extern const int8_t HELP_WINDOW_W;
extern const int8_t HELP_WINDOW_Y;
extern const int8_t HELP_WINDOW_X;

extern const int8_t MAIN_MENU_WINDOW_H;
extern const int8_t MAIN_MENU_WINDOW_W;
extern const int8_t MAIN_MENU_WINDOW_Y;
extern const int8_t MAIN_MENU_WINDOW_X;

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

extern const int8_t LOGS_WINDOW_H;
extern const int8_t LOGS_WINDOW_W;
extern const int8_t LOGS_WINDOW_Y;
extern const int8_t LOGS_WINDOW_X;

extern const int8_t BOARD_SCORE_W;

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

/**
 ** @brief GameWindow consists of two windows one for the border of the window, 
 ** and the other for the content of the window, it being the subwindow of the 
 ** border. The dimensions and coordinates of each of these windows are 
 ** described by the subsequent members.
 **/
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

/**
 ** @brief Initialize a GameWindow object.
 ** 
 ** @param height The height of the GameWindow including its borders.
 ** @param width The width of the GameWindow including its borders.
 ** @param y The y-coordinate of the GameWindow.
 ** @param x The x-coordinate of the GameWindow.
 ** 
 ** @return The initialized GameWindow object.
 **/
GameWindow game_window_get(int height, int width, int y, int x);

/**
 ** @brief Allocate memory and initialize a GameWindow object.
 ** 
 ** @param height The height of the GameWindow including its borders.
 ** @param width The width of the GameWindow including its borders.
 ** @param y The y-coordinate of the GameWindow.
 ** @param x The x-coordinate of the GameWindow.
 **
 ** @return A pointer to the allocated GameWindow object.
 **/
GameWindow* game_window_init(int height, int width, int y, int x);

/**
 ** @brief Deallocate the GameWindow object @game_window.
 ** 
 ** @param game_window The GameWindow object to be deallocated.
 **/
void game_window_destroy(GameWindow* game_window);

/**
 ** @brief Refresh both the border and content windows of @game_window.
 **
 ** @param game_window The GameWindow object to be refreshed.
 **/
void game_window_refresh(GameWindow* game_window);

/**
 ** @brief Draw the border of @game_window the color specified by @color_pair.
 **
 ** @param game_window The GameWindow object to be drawn to.
 ** @param color_pair The color pair that will be used for the border. 
 **/
void draw_window_border(GameWindow* game_window, int16_t color_pair);

/**
 ** @brief Draw the title specified by @title to the border of @game_window at 
 ** (y, x) = (0, 1), with corresponding color specified by @color_pair. 
 ** 
 ** @param game_window The GameWindow object to be drawn to.
 ** @param title The string that will be printed.
 ** @param color_pair The color pair that will be used for the title.
 **/
void draw_window_title(GameWindow* game_window, const char* title, int16_t color_pair);

/**
 ** @brief Draw the border of @board_window, which will display the play field.  
 ** 
 ** @param board_window The GameWindow object to be drawn to.
 **/
void draw_board_window(GameWindow* board_window);

/**
 ** @brief Draw the border and title of @hold_window, which will display what 
 ** piece is currently being held.
 
 ** @param hold_window The GameWindow object to be drawn to.
 **/
void draw_hold_window(GameWindow* hold_window);

/** 
 ** @brief Draw the border and title of @next_window, which will display the 
 ** next piece to enter the play field. 
 ** 
 ** @param next_window The GameWindow object to be drawn to.
 **/
void draw_next_window(GameWindow* next_window);

/**
 ** @brief Draw the border, title, and labels of @stats_window, which will 
 ** display the current game statistics like, game time, level, number of lines, 
 ** etc.
 **
 ** @param stats_window The GameWindow object to be drawn to.
 **/
void draw_stats_window(GameWindow* stats_window);

/**
 ** @brief Draw the border, title, and game controls of @help_window. 
 ** 
 ** @param help_window The GameWindow object to be drawn to.
 **/
void draw_help_window(GameWindow* help_window);

/**
 ** @brief Draw the border, title, and level select of @main_menu_window.
 **
 ** @param main_menu_window The GameWindow object to be drawn to.
 ** @param start_level The current start level of the game.
 **/
void draw_main_menu_window(GameWindow* main_menu_window, uint8_t start_level);

/**
 ** @brief Draw the border, title, and controls of @pause_window.
 ** 
 ** @param pause_window The GameWindow object to be drawn to.
 **/
void draw_pause_window(GameWindow* pause_window);

/**
 ** @brief Draw the border, title, and controls of @game_over_window.
 **
 ** @param game_over_window The GameWindow object to be drawn to.
 **/
void draw_game_over_window(GameWindow* game_over_window);

/**
 ** @brief Draw the border and title of @debug_window, which will display
 ** current values of game state and stats variables. 
 ** 
 ** @param debug_window The GameWindow object to be drawn to.
 **/
void draw_debug_window(GameWindow* debug_window);

/**
 ** @brief Draw the border and title of the @logs_window, which will display 
 ** the most recent debug logs.
 **
 ** @param logs_window The GameWindow object to be drawn to.
 **/
void draw_logs_window(GameWindow* logs_window);

/**
 ** @brief Draw the current board state consisting of the buffer zone line, 
 ** board stack, ghost piece, current play piece, and score.
 **
 ** @param board_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object representing the current game state 
 ** that will be displayed.
 **/
void draw_board_state(GameWindow* board_window, const GameState* game_state);

/**
 ** @brief Draw the buffer zone line indicating the height at which pieces will 
 ** spawn.
 **
 ** @param board_window The GameWindow object to be drawn to. 
 **/
void draw_buffer_zone_line(GameWindow* board_window);

/**
 ** @brief Draw the board stack, i.e., the left over pieces that have been 
 ** placed. 
 ** 
 ** @param board_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object that has the board stack data. 
 **/
void draw_board_stack(GameWindow* board_window, const GameState* game_state);

/**
 ** @brief Draw the current piece being played. 
 ** 
 ** @param board_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object that has the current piece data. 
 **/
void draw_curr_piece(GameWindow* board_window, const GameState* game_state);

/**
 ** @brief Draw the current piece's corresponding ghost piece, which indicates 
 ** where the current piece would be placed if hard dropped. 
 **
 ** @param board_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object that has the ghost piece data. 
 **/
void draw_ghost_piece(GameWindow* board_window, const GameState* game_state);

/**
 ** @brief Draw the current game score.
 **
 ** @param board_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object the score will be retrieved from. 
 **/
void draw_score(GameWindow* board_window, const GameState* game_state);

/**
 ** @brief Draw the piece currently being held, if it exists.
 ** 
 ** @param hold_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object that has the hold piece data. 
 **/
void draw_hold_piece(GameWindow* hold_window, const GameState* game_state);

/**
 ** @brief Draw the piece currently next in queue.
 ** 
 ** @param next_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object that has the next piece data. 
 **/
void draw_next_piece(GameWindow* next_window, const GameState* game_state);

/**
 ** @brief Draw current game time, number of lines, current level, score per 
 ** second, and pieces placed per second.
 ** 
 ** @param stats_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object that has the number of lines and 
 ** current level.
 ** @param stats The Stats object that has the game time, score per second, and 
 ** pieces placed per second.
 **/
void draw_stats(GameWindow* stats_window, const GameState* game_state, const Stats* stats);

/**
 ** @brief Draw the number of singles, doubles, triples, and tetrises that have 
 ** been completed when paused.
 ** 
 ** @param stats_window The GameWindow object to be drawn to. 
 ** @param stats The Stats object that has the number of singles, doubles, 
 ** triples, and tetrises.
 **/
void draw_pause_stats(GameWindow* stats_window, const Stats* stats);

/**
 ** @brief Draw the current values of various @game_state and @stats variables.
 ** 
 ** @param debug_window The GameWindow object to be drawn to. 
 ** @param game_state The GameState object to be read from.
 ** @param stats The Stats object to be read from.
 **/
void draw_debug_variables(GameWindow* debug_window, const GameState* game_state, const Stats* stats);

/**
 ** @brief Draw the most recent logs written to @debug_log.
 ** 
 ** @param logs_window The GameWindow object to be drawn to. 
 ** @param debug_log The file the logs will be read from.
 ** @param log_buffer The LogBuffer object that keeps track of the most recent 
 ** logs.
 **/
void draw_debug_logs(GameWindow* logs_window, FILE* debug_log, LogBuffer* log_buffer);

#endif
