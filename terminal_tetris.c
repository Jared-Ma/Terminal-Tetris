#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"


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

    WINDOW* hold_window = draw_hold_window(HOLD_WINDOW_H, HOLD_WINDOW_W, 0, 0);
    WINDOW* stats_window = draw_stats_window(STATS_WINDOW_H, STATS_WINDOW_W, 6, 0);
    WINDOW* board_window = draw_board_window(BOARD_WINDOW_H, BOARD_WINDOW_W, 0, 14);
    WINDOW* next_window = draw_next_window(NEXT_WINDOW_H, NEXT_WINDOW_W, 0, 36);
    WINDOW* controls_window = draw_controls_window(CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, 6, 36);

    GameState* game_state = game_state_init();

    draw_piece_centered(next_window, &game_state->next_piece);
    draw_board_stack(board_window, game_state);
    draw_curr_piece(board_window, game_state);

    bool running = true;
    while (running) {
        int input = getch();
        switch (input) {
            case 'z':
                game_state_rotate_piece_srs(game_state, LEFT);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                break;
            case 'x':
                game_state_rotate_piece_srs(game_state, RIGHT);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                break;
            case KEY_LEFT:
                game_state_move_piece(game_state, game_state->curr_piece.y, game_state->curr_piece.x - 1);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                break;
            case KEY_RIGHT:
                game_state_move_piece(game_state, game_state->curr_piece.y, game_state->curr_piece.x + 1);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                break;
            case KEY_DOWN:
                game_state_move_piece(game_state, game_state->curr_piece.y + 1, game_state->curr_piece.x);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                break;
            case KEY_UP:
                game_state_move_piece(game_state, game_state->curr_piece.y - 1, game_state->curr_piece.x);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                break;
            case ' ':
                game_state_drop_piece(game_state);
                game_state_clear_lines(game_state);
                game_state_load_next_piece(game_state);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                draw_piece_centered(next_window, &game_state->next_piece);
                break;
            case 'c':
                game_state_hold_piece(game_state);
                draw_board_stack(board_window, game_state);
                draw_curr_piece(board_window, game_state);
                draw_piece_centered(next_window, &game_state->next_piece);
                draw_piece_centered(hold_window, &game_state->hold_piece);
                break;
            case '\e':
                running = false;
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
