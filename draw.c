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

void draw_board_piece(WINDOW* window, Piece* piece) {
    size_t start_y = piece->y - piece->n/2;
    size_t start_x = 2*piece->x - piece->n;
    for (size_t i = 0; i < piece->n; ++i) {
        char string[BOARD_WINDOW_W] = "";
        for (size_t j = 0; j < piece->n; ++j) {
            if (piece->M[piece->r][i][j] == 1) {
                string[2*j] = '[';
                string[2*j+1] = ']';
            } else {
                string[2*j] = ' ';
                string[2*j+1] = ' ';
            }
        }
        mvwprintw(window, start_y + i, start_x, "%s", string);
    }
    wrefresh(window);
}

void draw_board_empty(WINDOW* window) {
    for (size_t i = 1; i < getmaxy(window)-1; ++i) {
        mvwprintw(window, i, 1, "                    ");
    }
    wrefresh(window);
}

void draw_next_piece(WINDOW* window, Piece* piece) {
    clear_next_window(window);

    size_t horizontal_padding = 2*(piece->n - piece->l);
    size_t start_y = NEXT_WINDOW_H / 2 - piece->n/2;
    size_t start_x = NEXT_WINDOW_W / 2 - piece->l - horizontal_padding;
    size_t internal_h = NEXT_WINDOW_H - 2;
    size_t internal_w = NEXT_WINDOW_W - 2;

    for (size_t i = 0; i < piece->n; ++i) {
        if (start_y + i <= internal_h) {
            char string[NEXT_WINDOW_W] = "";
            for (size_t j = 0; j < piece->n; ++j) {
                if (start_x + 2*j <= internal_w) {
                    if (piece->M[0][i][j] == 1) {
                        string[2*j] = '[';
                        string[2*j+1] = ']';
                    } else {
                        string[2*j] = ' ';
                        string[2*j+1] = ' ';
                    }
                }
            }
            mvwprintw(window, start_y + i, start_x, "%s", string);
        }
    }

    wrefresh(window);
}

void clear_next_window(WINDOW* window) {
    size_t internal_h = NEXT_WINDOW_H - 2;
    size_t internal_w = NEXT_WINDOW_W - 2;
    for (size_t i = 0; i < internal_h; ++i) {
        char string[NEXT_WINDOW_W] = "";
        for (size_t j = 0; j < internal_w; ++j) {
            string[j] = ' ';
        }
        mvwprintw(window, i+1, 1, "%s", string);
    }
    wrefresh(window);
}

void draw_hold_piece(WINDOW* window, Piece* piece) {
    clear_hold_window(window);

    size_t horizontal_padding = 2*(piece->n - piece->l);
    size_t start_y = HOLD_WINDOW_H / 2 - piece->n/2;
    size_t start_x = HOLD_WINDOW_W / 2 - piece->l - horizontal_padding;
    size_t internal_h = HOLD_WINDOW_H - 2;
    size_t internal_w = HOLD_WINDOW_W - 2;

    for (size_t i = 0; i < piece->n; ++i) {
        if (start_y + i <= internal_h) {
            char string[HOLD_WINDOW_W] = "";
            for (size_t j = 0; j < piece->n; ++j) {
                if (start_x + 2*j <= internal_w) {
                    if (piece->M[0][i][j] == 1) {
                        string[2*j] = '[';
                        string[2*j+1] = ']';
                    } else {
                        string[2*j] = ' ';
                        string[2*j+1] = ' ';
                    }
                }
            }
            mvwprintw(window, start_y + i, start_x, "%s", string);
        }
    }

    wrefresh(window);
}

void clear_hold_window(WINDOW* window) {
    size_t internal_h = HOLD_WINDOW_H - 2;
    size_t internal_w = HOLD_WINDOW_W - 2;
    for (size_t i = 0; i < internal_h; ++i) {
        char string[HOLD_WINDOW_W] = "";
        for (size_t j = 0; j < internal_w; ++j) {
            string[j] = ' ';
        }
        mvwprintw(window, i+1, 1, "%s", string);
    }
    wrefresh(window);
}
