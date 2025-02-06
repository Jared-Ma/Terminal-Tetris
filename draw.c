#include <ncurses.h>
#include <string.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"


WINDOW* draw_hold_window(int height, int width, int y, int x) {
    WINDOW* hold_window = newwin(height, width, y, x);
    box(hold_window, 0, 0);
    mvwprintw(hold_window, 0, 1, "HOLD");
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

WINDOW* draw_board_window(int height, int width, int y, int x) {
    WINDOW* board_window = newwin(height, width, y, x);
    box(board_window, 0, 0);
    wrefresh(board_window);
    return board_window;
}

WINDOW* draw_next_window(int height, int width, int y, int x) {
    WINDOW* next_window = newwin(height, width, y, x);
    box(next_window, 0, 0);
    mvwprintw(next_window, 0, 1, "NEXT");
    wrefresh(next_window);
    return next_window;
}

WINDOW* draw_controls_window(int height, int width, int y, int x) {
    WINDOW* controls_window = newwin(height, width, y, x);
    box(controls_window, 0, 0);
    mvwprintw(controls_window, 0, 1, "CONTROLS");
    mvwprintw(controls_window, 2, 1, "move:    < >");
    mvwprintw(controls_window, 4, 1, "rotate:  z x");
    mvwprintw(controls_window, 6, 1, "hold:      c");
    mvwprintw(controls_window, 8, 1, "soft drop: v");
    mvwprintw(controls_window, 10, 1, "hard drop: _");
    mvwprintw(controls_window, 12, 1, "pause:   esc");
    wrefresh(controls_window);
    return controls_window;
}

void clear_window(WINDOW* window) {
    size_t internal_h = getmaxy(window) - 2;
    size_t internal_w = getmaxx(window) - 2;
    for (size_t i = 1; i <= internal_h; ++i) {
        for (size_t j = 1; j <= internal_w; ++j) {
            mvwprintw(window, i, j, " ");
        }
    }
    wrefresh(window);
}

void draw_board_piece(WINDOW* window, Piece* piece) {
    size_t internal_h = getmaxy(window) - 2;
    size_t internal_w = getmaxx(window) - 2;
    int start_y = piece->y - piece->n/2 + 1;
    int start_x = 2*(piece->x - piece->n/2) + 1;

    for (size_t i = 0; i < piece->n; ++i) {
        for (size_t j = 0; j < piece->n; ++j) {
            if (
                start_y + i >= 1 && start_y + i <= internal_h &&
                start_x + 2*j >= 1 && start_x + 2*j <= internal_w
            ) {
                if (piece->M[piece->r][i][j] == 1) {
                    mvwprintw(window, start_y + i, start_x + 2*j, "[]");
                } else {
                    mvwprintw(window, start_y + i, start_x + 2*j, "  ");
                }
            }
        }
    }

    wrefresh(window);
}

void draw_piece_centered(WINDOW* window, Piece* piece) {
    clear_window(window);

    size_t internal_h = getmaxy(window) - 2;
    size_t internal_w = getmaxx(window) - 2;
    size_t horizontal_padding = 2*(piece->n - piece->l);
    size_t start_y = getmaxy(window) / 2 - piece->n/2;
    size_t start_x = getmaxx(window) / 2 - piece->l - horizontal_padding;

    for (size_t i = 0; i < piece->n; ++i) {
        for (size_t j = 0; j < piece->n; ++j) {
            if (
                start_y + i >= 1 && start_y + i <= internal_h &&
                start_x + 2*j >= 1 && start_x + 2*j <= internal_w
            ) {
                if (piece->M[0][i][j] == 1) {
                    mvwprintw(window, start_y + i, start_x + 2*j, "[]");
                } else {
                    mvwprintw(window, start_y + i, start_x + 2*j, "  ");
                }
            }
        }
    }

    wrefresh(window);
}
