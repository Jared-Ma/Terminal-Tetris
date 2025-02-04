#include <ncurses.h>
#include "draw.h"
#include "piece.h"


WINDOW* draw_hold_window(int height, int width, int y, int x) {
    WINDOW* hold_window = newwin(height, width, y, x);
    box(hold_window, 0, 0);
    mvwprintw(hold_window, 0, 1, "HOLD");
    mvwprintw(hold_window, 2, 5, "[][]");
    mvwprintw(hold_window, 3, 5, "[][]");
    wrefresh(hold_window);
    return hold_window;
}

WINDOW* draw_stats_window(int height, int width, int y, int x) {
    WINDOW* stats_window = newwin(height, width, y, x);
    box(stats_window, 0, 0);
    mvwprintw(stats_window, 0, 1, "STATS");
    mvwprintw(stats_window, 2, 1, "time:");
    mvwprintw(stats_window, 4, 1, "score:");
    mvwprintw(stats_window, 6, 1, "lines:");
    mvwprintw(stats_window, 8, 1, "level:");
    mvwprintw(stats_window, 10, 1, "combo:");
    mvwprintw(stats_window, 12, 1, "fps:");
    wrefresh(stats_window);
    return stats_window;
}

WINDOW* draw_play_window(int height, int width, int y, int x) {
    WINDOW* play_window = newwin(height, width, y, x);
    box(play_window, 0, 0);
    for (size_t i = 1; i < height-1; ++i) {
        mvwprintw(play_window, i, 1, " . . . . . . . . . .");
    }
    wrefresh(play_window);
    return play_window;
}

WINDOW* draw_next_window(int height, int width, int y, int x) {
    WINDOW* next_window = newwin(height, width, y, x);
    box(next_window, 0, 0);
    mvwprintw(next_window, 0, 1, "NEXT");
    mvwprintw(next_window, 2, 5, "[][]");
    mvwprintw(next_window, 3, 5, "[][]");
    wrefresh(next_window);
    return next_window;
}

WINDOW* draw_controls_window(int height, int width, int y, int x) {
    WINDOW* controls_window = newwin(height, width, y, x);
    box(controls_window, 0, 0);
    mvwprintw(controls_window, 0, 1, "CONTROLS");
    mvwprintw(controls_window, 2, 1, "move:    < >");
    mvwprintw(controls_window, 4, 1, "rotate:  z x");
    mvwprintw(controls_window, 6, 1, "hold:  shift");
    mvwprintw(controls_window, 8, 1, "soft drop: v");
    mvwprintw(controls_window, 10, 1, "hard drop: _");
    mvwprintw(controls_window, 12, 1, "pause:   esc");
    wrefresh(controls_window);
    return controls_window;
}

void draw_piece(WINDOW* window, Piece* piece) {
    size_t start_y = piece->y - piece->n/2;
    size_t start_x = 2*piece->x - piece->n;
    for (size_t i = 0; i < piece->n; ++i) {
        char string[10] = "";
        for (size_t j = 0; j < piece->n; ++j) {
            if (piece->M[piece->r][i][j] == 1) {
                string[2*j] = '[';
                string[2*j+1] = ']';
            } else {
                string[2*j] = ' ';
                string[2*j+1] = '.';
            }
        }
        mvwprintw(window, start_y + i, start_x, "%s", string);
    }
    wrefresh(window);
}

void clear_play_window(WINDOW* window) {
    for (size_t i = 1; i < getmaxy(window)-1; ++i) {
        mvwprintw(window, i, 1, " . . . . . . . . . .");
    }
    wrefresh(window);
}
