#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "stats.h"
#include "logger.h"

#define TARGET_FPS 60
#define TARGET_FRAME_TIME_MS (1e3 / TARGET_FPS)

#define ESC '\e'
#define COLOR_ORANGE 8


enum InputState {
    PLAYING,
    PAUSED,
    GAME_OVER,
};

typedef enum InputState InputState;

int main(int argc, char* argv[argc+1]) {
    if (!debug_log_open("./logs/debug.txt")) {
        return EXIT_FAILURE;
    }

    initscr();          // Initialize curses screen
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
    
    keypad(board_window, true);     // Enables arrow key input
    nodelay(board_window, true);    // wgetch() doesn't block

    GameState* game_state = game_state_init();
    Stats* stats = stats_init();

    InputState input_state = PLAYING;
    clock_t frame_start, frame_end;
    time_t time_start, time_end;
    bool running = true;

    while (running) {
        frame_start = clock();
        time(&time_start);

        draw_stats(stats_window, stats);
        draw_hold_piece(hold_window, game_state);
        draw_next_piece(next_window, game_state);
        wrefresh(stats_window);
        wrefresh(hold_window);
        wrefresh(next_window);
        
        draw_board_state(board_window, game_state);
        if (input_state == PAUSED) {
            draw_paused_text(board_window, game_state);
        } else if (input_state == GAME_OVER) {
            draw_game_over_text(board_window, game_state);
        }
        
        int input = wgetch(board_window);
        if (input_state == PLAYING) {
            switch (input) {
            case 'z':
                game_state_rotate_curr_piece_srs(game_state, LEFT);
                break;
            case 'x':
                game_state_rotate_curr_piece_srs(game_state, RIGHT);
                break;
            case KEY_LEFT:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y, game_state->curr_piece.x - 1);
                break;
            case KEY_RIGHT:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y, game_state->curr_piece.x + 1);
                break;
            case KEY_DOWN:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y + 1, game_state->curr_piece.x);
                break;
            case KEY_UP:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y - 1, game_state->curr_piece.x);
                break;
            case 'c':
                game_state_hold_piece(game_state);
                break;
            case ' ':
                game_state_drop_curr_piece(game_state, stats);
                game_state_clear_lines(game_state, stats);
                game_state_load_next_piece(game_state);
                if (game_state_check_top_out(game_state)) {
                    input_state = GAME_OVER;
                }
                break;
            case ESC:
                input_state = PAUSED;
                break;
            }
        } else if (input_state == PAUSED) {
            switch (input) {
            case ' ':
                input_state = PLAYING;
                break;
            case 'r':
                game_state_restart(game_state);
                stats_restart(stats);
                input_state = PLAYING;
                break;
            case ESC:
                running = false;
                break;
            }
        } else if (input_state == GAME_OVER) {
            switch (input) {
            case 'r':
                game_state_restart(game_state);
                stats_restart(stats);
                input_state = PLAYING;
                break;
            case ESC:
                running = false;
                break;
            }
        }
        
        if (input_state == PLAYING) {
            clear_window(debug_window);
            if (game_state_check_curr_piece_grounded(game_state)) {
                mvwprintw(debug_window, 1, 1, "touching: T");
                game_state_decrement_lock_delay_timer(game_state);
            } else {
                mvwprintw(debug_window, 1, 1, "touching: F");
                game_state_reset_lock_delay_timer(game_state);
            }
            mvwprintw(debug_window, 2, 1, "lock_delay_timer: %u", game_state->lock_delay_timer);
            mvwprintw(debug_window, 3, 1, "move_reset_count: %u", game_state->move_reset_count);
            wrefresh(debug_window);
    
            if (game_state->lock_delay_timer == 0) {
                game_state_lock_curr_piece(game_state);
                game_state_load_next_piece(game_state);
            }
        }

        frame_end = clock();
        double frame_time_ms = (double)(frame_end - frame_start) * 1e3 / CLOCKS_PER_SEC;
        if (frame_time_ms < TARGET_FRAME_TIME_MS) {
            double sleep_time_ms = TARGET_FRAME_TIME_MS - frame_time_ms;
            usleep(sleep_time_ms * 1e3);
        }

        if (input_state == PLAYING) {
            time(&time_end);
            double time_s = difftime(time_end, time_start);
            stats_update_time(stats, time_s);
        }

        stats_increment_frame_count(stats);
    }
    
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
