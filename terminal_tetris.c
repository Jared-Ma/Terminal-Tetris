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
    draw_next_piece(next_window, &game_state->next_piece);
    draw_board_piece(board_window, &game_state->curr_piece);

    bool running = true;
    while (running) {
        int input = getch();
        switch (input) {
            case 'z':
                piece_rotate_right(&game_state->curr_piece);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                break;
            case 'x':
                piece_rotate_right(&game_state->curr_piece);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                break;
            case '\e':
                running = false;
                break;
            case KEY_LEFT:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y, game_state->curr_piece.x - 1);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                break;
            case KEY_RIGHT:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y, game_state->curr_piece.x + 1);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                break;
            case KEY_DOWN:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y + 1, game_state->curr_piece.x);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                break;
            case KEY_UP:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y - 1, game_state->curr_piece.x);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                break;
            case ' ':
                game_state_load_next_piece(game_state);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                // clear_next_window(next_window);
                draw_next_piece(next_window, &game_state->next_piece);
                break;
            case 'c':
                game_state_hold_piece(game_state);
                draw_board_empty(board_window);
                draw_board_piece(board_window, &game_state->curr_piece);
                // clear_next_window(next_window);
                draw_next_piece(next_window, &game_state->next_piece);
                draw_hold_piece(hold_window, &game_state->hold_piece);
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
