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
    // curs_set(0); // Hide cursor
    refresh();
    set_escdelay(0);

    WINDOW* hold_window = draw_hold_window(6, 14, 0, 0);
    WINDOW* stats_window = draw_stats_window(16, 14, 6, 0);
    WINDOW* play_window = draw_play_window(22, 22, 0, 14);
    WINDOW* next_window = draw_next_window(6, 14, 0, 36);
    WINDOW* controls_window = draw_controls_window(16, 14, 6, 36);

    GameState* game_state = game_state_init();
    game_state_debug_print(game_state);

    bool running = true;
    while (running) {
        int input = getch();
        switch (input) {
            case 'z':
                piece_rotate_right(&game_state->curr_piece);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
            case 'x':
                piece_rotate_right(&game_state->curr_piece);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
            case '\e':
                running = false;
                break;
            case KEY_LEFT:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y, game_state->curr_piece.x - 1);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
            case KEY_RIGHT:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y, game_state->curr_piece.x + 1);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
            case KEY_DOWN:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y + 1, game_state->curr_piece.x);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
            case KEY_UP:
                piece_move(&game_state->curr_piece, game_state->curr_piece.y - 1, game_state->curr_piece.x);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
            case ' ':
                game_state_load_next_piece(game_state);
                game_state_debug_print(game_state);
                clear_play_window(play_window);
                draw_piece(play_window, &game_state->curr_piece);
                break;
        }
    }

    game_state_destroy(game_state);
    fclose(debug_log);
    delwin(hold_window);
    delwin(stats_window);
    delwin(play_window);
    delwin(next_window);
    delwin(controls_window);
    endwin();

    return EXIT_SUCCESS;
}
