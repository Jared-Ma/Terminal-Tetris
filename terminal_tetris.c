#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"


#define ESC '\e'

int main(int argc, char* argv[argc+1]) {
    if (!debug_log_open("./logs/debug.txt")) {
        return EXIT_FAILURE;
    }

    initscr(); // Initialize curses screen
    keypad(stdscr, TRUE); // Enables arrow key input
    noecho(); // Don't echo input to screen
    curs_set(0); // Hide cursor
    refresh();
    set_escdelay(0);

    WINDOW* hold_window = draw_hold_window(HOLD_WINDOW_H, HOLD_WINDOW_W, BUFFER_ZONE_H, 0);
    WINDOW* stats_window = draw_stats_window(STATS_WINDOW_H, STATS_WINDOW_W, 6 + BUFFER_ZONE_H, 0);
    WINDOW* board_window = draw_board_window(BOARD_WINDOW_H, BOARD_WINDOW_W, 0, 14);
    WINDOW* next_window = draw_next_window(NEXT_WINDOW_H, NEXT_WINDOW_W, BUFFER_ZONE_H, 36);
    WINDOW* controls_window = draw_controls_window(CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, 6 + BUFFER_ZONE_H, 36);

    GameState* game_state = game_state_init();

    bool paused = false;
    bool game_over = false;
    bool running = true;
    while (running) {
        draw_board_state(board_window, game_state);
        draw_hold_piece(hold_window, game_state);
        draw_next_piece(next_window, game_state);
        int input = getch();
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
                game_state_drop_curr_piece(game_state);
                game_state_clear_lines(game_state);
                game_state_load_next_piece(game_state);
                if (game_state_check_top_out(game_state)) {
                    draw_game_over_text(board_window, game_state);
                    game_over = true;
                    while (game_over) {
                        input = getch();
                        switch (input) {
                            case 'r':
                                game_state_restart(game_state);
                                game_over = false;
                                break;
                            case ESC:
                                game_over = false;
                                running = false;
                                break;
                        }
                    }
                }
                break;
            case ESC:
                draw_paused_text(board_window, game_state);
                paused = true;
                while (paused) {
                    input = getch();
                    switch (input) {
                        case ' ':
                            paused = false;
                            break;
                        case 'r':
                            game_state_restart(game_state);
                            paused = false;
                            break;
                        case ESC:
                            paused = false;
                            running = false;
                            break;
                    }
                }
                break;
        }
    }

    game_state_destroy(game_state);
    fclose(debug_log);
    delwin(hold_window);
    delwin(stats_window);
    delwin(board_window);
    delwin(next_window);
    delwin(controls_window);
    endwin();
    curs_set(1); // unhide cursor

    return EXIT_SUCCESS;
}
