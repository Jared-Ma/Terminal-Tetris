#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "stats.h"
#include "logger.h"
#include "test_draw.h"

#define COLOR_ORANGE 8


int main(void) {
    if (!debug_log_open("./logs/debug.txt")) {
        return EXIT_FAILURE;
    }
    
    // initscr();          // Initialize curses screen
    newterm(0, debug_log, stdin);
    noecho();           // Don't echo input to screen
    curs_set(0);        // Hide cursor
    set_escdelay(0);    // Remove delay after reading escape key
    
    start_color();
    use_default_colors();
    init_color(COLOR_ORANGE, 900, 600, 0);
    
    init_pair(I, COLOR_CYAN,    -1);
    init_pair(J, COLOR_BLUE,    -1);
    init_pair(L, COLOR_ORANGE,  -1);
    init_pair(O, COLOR_YELLOW,  -1);
    init_pair(S, COLOR_GREEN,   -1);
    init_pair(T, COLOR_MAGENTA, -1);
    init_pair(Z, COLOR_RED,     -1);

    WINDOW* hold_window = draw_hold_window(HOLD_WINDOW_H, HOLD_WINDOW_W, BUFFER_ZONE_H, 0);
    WINDOW* stats_window = draw_stats_window(STATS_WINDOW_H, STATS_WINDOW_W, 6 + BUFFER_ZONE_H, 0);
    WINDOW* board_window = draw_board_window(BOARD_WINDOW_H, BOARD_WINDOW_W, 0, 14);
    WINDOW* next_window = draw_next_window(NEXT_WINDOW_H, NEXT_WINDOW_W, BUFFER_ZONE_H, 36);
    WINDOW* controls_window = draw_controls_window(CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, 6 + BUFFER_ZONE_H, 36);
    WINDOW* debug_window = draw_debug_window(DEBUG_WINDOW_H, DEBUG_WINDOW_W, 0, 50);

    GameState* game_state = game_state_init();
    Stats* stats = stats_init();
    game_state_start(game_state);

    // src_dump(debug_log)
    test_draw_windows();

    game_state_destroy(game_state);
    stats_destroy(stats);
    fclose(debug_log);
    delwin(hold_window);
    delwin(stats_window);
    delwin(board_window);
    delwin(next_window);
    delwin(controls_window);
    endwin();
    curs_set(1);

    return EXIT_SUCCESS;
}
