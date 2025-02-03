#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "draw.h"
#include "piece.h"


int main(int argc, char* argv[argc+1]) {
    initscr(); // Initialize curses screen
    keypad(stdscr, TRUE); 
    noecho();  // Don't echo input to screen
    refresh();

    WINDOW* hold_window = draw_hold_window(6, 14, 0, 0);
    WINDOW* stats_window = draw_stats_window(16, 14, 6, 0);
    WINDOW* play_window = draw_play_window(22, 22, 0, 14);
    WINDOW* next_window = draw_next_window(6, 14, 0, 36);
    WINDOW* controls_window = draw_controls_window(16, 14, 6, 36);

    Piece t_piece = piece_init(T, 3, 3);
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();

    t_piece.r = (t_piece.r + 1) % 4;
    draw_piece(play_window, t_piece);
    getch();


    delwin(hold_window);
    delwin(stats_window);
    delwin(play_window);
    delwin(next_window);
    delwin(controls_window);
    endwin();

    return EXIT_SUCCESS;
}
