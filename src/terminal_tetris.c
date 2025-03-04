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


enum InputState {
    PLAYING,
    PAUSED,
    GAME_OVER,
};

typedef enum InputState InputState;

static void start_curses(void) {
    initscr();                // initialize curses screen
    noecho();                 // disable echo input to screen
    curs_set(0);              // hide cursor
    set_escdelay(0);          // remove delay after reading escape key
    keypad(stdscr, true);     // enable arrow key input
    nodelay(stdscr, true);    // enable non-blocking getch()
    refresh();                // initial refresh of stdscr
    
    // initialize color pairs of tetronimos
    start_color();
    use_default_colors();

    short COLOR_ORANGE = 8;
    init_color(COLOR_ORANGE, 900, 600, 0);

    init_pair(I, COLOR_CYAN,    -1);
    init_pair(J, COLOR_BLUE,    -1);
    init_pair(L, COLOR_ORANGE,  -1);
    init_pair(O, COLOR_YELLOW,  -1);
    init_pair(S, COLOR_GREEN,   -1);
    init_pair(T, COLOR_MAGENTA, -1);
    init_pair(Z, COLOR_RED,     -1);
}

static void end_curses(void) {
    endwin();
    curs_set(2);
}

static void start_tetris(
    GameState* game_state, 
    Stats* stats,
    GameWindow* board_window,
    GameWindow* hold_window,
    GameWindow* next_window,
    GameWindow* stats_window,
    GameWindow* controls_window,
    GameWindow* debug_window,
    GameWindow* pause_window,
    GameWindow* game_over_window
) {
    srand(time(0));
    game_state_start(game_state);
    
    // render windows
    draw_board_window(board_window);
    draw_hold_window(hold_window);
    draw_next_window(next_window);
    draw_stats_window(stats_window);
    draw_controls_window(controls_window);
    draw_debug_window(debug_window);

    // render initial game state
    draw_board_state(board_window, game_state);
    draw_hold_piece(hold_window, game_state);
    draw_next_piece(next_window, game_state);
    draw_stats(stats_window, game_state, stats);
    draw_debug_variables(debug_window, game_state, stats);
    
    InputState input_state = PLAYING;
    time_t time_start, time_end;
    bool running = true;

    while (running) {
        clock_t frame_start = clock();
        time(&time_start);

        // Input        
        int input = getch();
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
                game_state_soft_drop_curr_piece(game_state);
                break;
            case 'c':
                game_state_hold_piece(game_state);
                break;
            case ' ':
                game_state_hard_drop_curr_piece(game_state);
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
                game_state_reset(game_state);
                stats_reset(stats);
                input_state = PLAYING;
                break;
            case ESC:
                running = false;
                break;
            }
        } else if (input_state == GAME_OVER) {
            switch (input) {
            case 'r':
                game_state_reset(game_state);
                stats_reset(stats);
                input_state = PLAYING;
                break;
            case ESC:
                running = false;
                break;
            }
        }
        
        // Update
        if (input_state == PLAYING) {
            if (game_state_check_curr_piece_grounded(game_state) && game_state->lock_delay_timer > 0) {
                game_state->lock_delay_timer--;
            }

            if (game_state->lock_delay_timer == 0) {
                game_state_lock_curr_piece(game_state);
                game_state_clear_lines(game_state);
                game_state_load_next_piece(game_state);
            }
            
            if (game_state->soft_drop == true) {
                game_state_apply_soft_drop_gravity(game_state);
            } else {
                game_state_apply_gravity(game_state);
            }

            if (game_state_check_collision(game_state, game_state->curr_piece)) {
                input_state = GAME_OVER;
            }

        }

        clock_t frame_end = clock();
        double frame_time_ms = (double)(frame_end - frame_start) * 1e3 / CLOCKS_PER_SEC;
        if (frame_time_ms < TARGET_FRAME_TIME_MS) {
            double sleep_time_ms = TARGET_FRAME_TIME_MS - frame_time_ms;
            usleep(sleep_time_ms * 1e3);
        }
        
        if (input_state == PLAYING) {
            time(&time_end);
            double time_s = difftime(time_end, time_start);
            stats->time += time_s;
        }
        
        stats->frame_count++;

        // Render
        if (input_state == PLAYING) {
            draw_board_state(board_window, game_state);
            draw_hold_piece(hold_window, game_state);
            draw_next_piece(next_window, game_state);
            draw_stats(stats_window, game_state, stats);
            draw_debug_variables(debug_window, game_state, stats);
        } else if (input_state == PAUSED) {
            draw_pause_window(pause_window);
        } else if (input_state == GAME_OVER) {
            draw_game_over_window(game_over_window);
        }
    }
}

int main(int argc, char* argv[argc+1]) {
    if (!debug_log_open("./logs/debug.txt")) {
        fprintf(stderr, "Failed to open debug log file (debug.txt).\n");
        return EXIT_FAILURE;
    }

    start_curses();
    
    GameWindow* board_window = game_window_init(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    GameWindow* hold_window = game_window_init(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y, HOLD_WINDOW_X
    );
    GameWindow* next_window = game_window_init(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y, NEXT_WINDOW_X
    );
    GameWindow* stats_window = game_window_init(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    GameWindow* controls_window = game_window_init(
        CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, 
        CONTROLS_WINDOW_Y, CONTROLS_WINDOW_X
    );
    GameWindow* pause_window = game_window_init(
        PAUSE_WINDOW_H, PAUSE_WINDOW_W, 
        PAUSE_WINDOW_Y, PAUSE_WINDOW_X
    );
    GameWindow* game_over_window = game_window_init(
        GAME_OVER_WINDOW_H, GAME_OVER_WINDOW_W, 
        GAME_OVER_WINDOW_Y, GAME_OVER_WINDOW_X
    );
    GameWindow* debug_window = game_window_init(
        DEBUG_WINDOW_H, DEBUG_WINDOW_W, 
        DEBUG_WINDOW_Y, DEBUG_WINDOW_X
    );
    
    GameState* game_state = game_state_init();
    Stats* stats = stats_init();
    
    start_tetris(
        game_state, 
        stats, 
        board_window, 
        hold_window, 
        next_window, 
        stats_window,
        controls_window, 
        debug_window,
        pause_window,
        game_over_window
    );
    
    game_state_destroy(game_state);
    stats_destroy(stats);
    game_window_destroy(board_window);
    game_window_destroy(hold_window);
    game_window_destroy(next_window);
    game_window_destroy(stats_window);
    game_window_destroy(controls_window);
    game_window_destroy(debug_window);
    end_curses();
    fclose(debug_log);

    return EXIT_SUCCESS;
}
