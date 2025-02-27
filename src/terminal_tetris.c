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
    
    GameWindow* board_window = game_window_init(BOARD_WINDOW_H, BOARD_WINDOW_W, BOARD_WINDOW_Y, BOARD_WINDOW_X);
    GameWindow* hold_window = game_window_init(HOLD_WINDOW_H, HOLD_WINDOW_W, HOLD_WINDOW_Y, HOLD_WINDOW_X);
    GameWindow* next_window = game_window_init(NEXT_WINDOW_H, NEXT_WINDOW_W, NEXT_WINDOW_Y, NEXT_WINDOW_X);
    GameWindow* stats_window = game_window_init(STATS_WINDOW_H, STATS_WINDOW_W, STATS_WINDOW_Y, STATS_WINDOW_X);
    GameWindow* controls_window = game_window_init(CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, CONTROLS_WINDOW_Y, CONTROLS_WINDOW_X);
    GameWindow* pause_window = game_window_init(PAUSE_WINDOW_H, PAUSE_WINDOW_W, PAUSE_WINDOW_Y, PAUSE_WINDOW_X);
    GameWindow* game_over_window = game_window_init(GAME_OVER_WINDOW_H, GAME_OVER_WINDOW_W, GAME_OVER_WINDOW_Y, GAME_OVER_WINDOW_X);
    GameWindow* debug_window = game_window_init(DEBUG_WINDOW_H, DEBUG_WINDOW_W, DEBUG_WINDOW_Y, DEBUG_WINDOW_X);
    
    draw_board_window(board_window);
    draw_hold_window(hold_window);
    draw_next_window(next_window);
    draw_stats_window(stats_window);
    draw_controls_window(controls_window);
    draw_debug_window(debug_window);

    keypad(board_window->content, true);     // Enables arrow key input
    nodelay(board_window->content, true);    // wgetch() doesn't block

    GameState* game_state = game_state_init();
    Stats* stats = stats_init();
    
    srand(time(0));
    game_state_start(game_state);

    InputState input_state = PLAYING;
    clock_t frame_start, frame_end;
    time_t time_start, time_end;
    bool running = true;

    while (running) {
        frame_start = clock();
        time(&time_start);

        if (game_state_check_collision(game_state, game_state->curr_piece)) {
            input_state = GAME_OVER;
        }

        if (input_state == PLAYING) {
            draw_board_state(board_window, game_state);
            draw_hold_piece(hold_window, game_state);
            draw_next_piece(next_window, game_state);
            draw_stats(stats_window, game_state, stats);
        } else if (input_state == PAUSED) {
            draw_pause_window(pause_window);
        } else if (input_state == GAME_OVER) {
            draw_game_over_window(game_over_window);
        }
        
        int input = wgetch(board_window->content);
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
            case KEY_UP:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y - 1, game_state->curr_piece.x);
                break;
            case 'c':
                game_state_hold_piece(game_state);
                break;
            case ' ':
                game_state_hard_drop_curr_piece(game_state);
                game_state_lock_curr_piece(game_state);
                game_state_clear_lines(game_state);
                game_state_load_next_piece(game_state);
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
                game_state_restart(game_state);
                stats_reset(stats);
                input_state = PLAYING;
                break;
            case ESC:
                running = false;
                break;
            }
        }
        
        if (input_state == PLAYING) {
            if (game_state_check_curr_piece_grounded(game_state)) {
                game_state->lock_delay_timer--;
                if (game_state->lock_delay_timer == 0) {
                    game_state_lock_curr_piece(game_state);
                    game_state_clear_lines(game_state);
                    game_state_load_next_piece(game_state);
                }
            }

            if (game_state->soft_drop == true) {
                game_state_apply_soft_drop_gravity(game_state);
            } else {
                game_state_apply_gravity(game_state);
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
            stats->time += time_s;
        }
        
        draw_debug_variables(debug_window, game_state, stats);
        stats->frame_count++;
    }
    
    game_state_destroy(game_state);
    stats_destroy(stats);
    fclose(debug_log);
    game_window_destroy(board_window);
    game_window_destroy(hold_window);
    game_window_destroy(next_window);
    game_window_destroy(stats_window);
    game_window_destroy(controls_window);
    game_window_destroy(debug_window);
    endwin();
    curs_set(1);

    return EXIT_SUCCESS;
}
