#include <ncurses.h>
#include <string.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"


#define BLOCK_LEFT '['
#define BLOCK_RIGHT ']'
#define GHOST_LEFT ':'
#define GHOST_RIGHT ':'
#define SPACE ' '
#define BUFFER_ZONE_LINE '_'

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

void draw_paused_text(WINDOW* window, GameState* game_state) {
    mvwprintw(window, BOARD_WINDOW_H/2-4, BOARD_WINDOW_W/2 - 4, "        ");
    mvwprintw(window, BOARD_WINDOW_H/2-5, BOARD_WINDOW_W/2 - 4, " PAUSED ");
    mvwprintw(window, BOARD_WINDOW_H/2-6, BOARD_WINDOW_W/2 - 4, "        ");
    
    mvwprintw(window, BOARD_WINDOW_H/2-1, BOARD_WINDOW_W/2 - 8, "               ");
    mvwprintw(window, BOARD_WINDOW_H/2  , BOARD_WINDOW_W/2 - 8, " space: resume ");
    mvwprintw(window, BOARD_WINDOW_H/2+1, BOARD_WINDOW_W/2 - 8, " r: restart    ");
    mvwprintw(window, BOARD_WINDOW_H/2+2, BOARD_WINDOW_W/2 - 8, " esc: quit     ");
    mvwprintw(window, BOARD_WINDOW_H/2+3, BOARD_WINDOW_W/2 - 8, "               ");
    wrefresh(window);
}

void draw_game_over_text(WINDOW* window, GameState* game_state) {
    mvwprintw(window, BOARD_WINDOW_H/2-4, BOARD_WINDOW_W/2 - 6, "            ");
    mvwprintw(window, BOARD_WINDOW_H/2-5, BOARD_WINDOW_W/2 - 6, " GAME  OVER ");
    mvwprintw(window, BOARD_WINDOW_H/2-6, BOARD_WINDOW_W/2 - 6, "            ");

    mvwprintw(window, BOARD_WINDOW_H/2-1, BOARD_WINDOW_W/2 - 6, "            ");
    mvwprintw(window, BOARD_WINDOW_H/2,   BOARD_WINDOW_W/2 - 6, " r: restart ");
    mvwprintw(window, BOARD_WINDOW_H/2+1, BOARD_WINDOW_W/2 - 6, " esc: quit  ");
    mvwprintw(window, BOARD_WINDOW_H/2+2, BOARD_WINDOW_W/2 - 6, "            ");
    wrefresh(window);
}

void clear_window(WINDOW* window) {
    size_t internal_h = getmaxy(window) - 2;
    size_t internal_w = getmaxx(window) - 2;

    for (size_t i = 1; i <= internal_h; ++i) {
        for (size_t j = 1; j <= internal_w; ++j) {
            mvwprintw(window, i, j, "%c", SPACE);
        }
    }

    wrefresh(window);
}

void draw_buffer_zone(WINDOW* window, GameState* game_state) {
    size_t internal_w = getmaxx(window) - 2;
    for (size_t i = 1; i <= internal_w; ++i) {
        mvwprintw(window, BUFFER_ZONE_H, i, "%c", BUFFER_ZONE_LINE);
    }
}

void draw_board_state(WINDOW* window, GameState* game_state) {
    clear_window(window);
    draw_buffer_zone(window, game_state);
    draw_board_stack(window, game_state);
    draw_ghost_piece(window, game_state);
    draw_curr_piece(window, game_state);
}

void draw_board_stack(WINDOW* window, GameState* game_state) {
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (game_state->board[i][j] == 1) {
                mvwprintw(window, i+1, 2*j+1, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }
    wrefresh(window);
}

void draw_curr_piece(WINDOW* window, GameState* game_state) {
    int start_y = game_state->curr_piece.y - game_state->curr_piece.n/2 + 1;
    int start_x = 2*(game_state->curr_piece.x - game_state->curr_piece.n/2) + 1;

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1) {
                mvwprintw(window, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }

    wrefresh(window);
}

void draw_hold_piece(WINDOW* window, GameState* game_state) {
    clear_window(window);

    if (game_state->holding_piece) {
        size_t horizontal_padding = 2*(game_state->hold_piece.n - game_state->hold_piece.l);
        size_t start_y = getmaxy(window) / 2 - game_state->hold_piece.n/2;
        size_t start_x = getmaxx(window) / 2 - game_state->hold_piece.l - horizontal_padding;
    
        for (size_t i = 0; i < game_state->hold_piece.n; ++i) {
            for (size_t j = 0; j < game_state->hold_piece.n; ++j) {
                if (game_state->hold_piece.M[0][i][j] == 1) {
                    if (game_state->hold_allowed) {
                        mvwprintw(window, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
                    } else {
                        mvwprintw(window, start_y + i, start_x + 2*j, "%c%c", GHOST_LEFT, GHOST_RIGHT);
                    }
                }
            }
        }
    } 
    
    wrefresh(window);
}

void draw_next_piece(WINDOW* window, GameState* game_state) {
    clear_window(window);

    size_t horizontal_padding = 2*(game_state->next_piece.n - game_state->next_piece.l);
    size_t start_y = getmaxy(window) / 2 - game_state->next_piece.n/2;
    size_t start_x = getmaxx(window) / 2 - game_state->next_piece.l - horizontal_padding;

    for (size_t i = 0; i < game_state->next_piece.n; ++i) {
        for (size_t j = 0; j < game_state->next_piece.n; ++j) {
            if (game_state->next_piece.M[0][i][j] == 1) {
                mvwprintw(window, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }

    wrefresh(window);
}

void draw_ghost_piece(WINDOW* window, GameState* game_state) {
    if (
        game_state->ghost_piece.y != game_state->curr_piece.y ||
        game_state->ghost_piece.x != game_state->curr_piece.x
    ) {
        int start_y = game_state->ghost_piece.y - game_state->ghost_piece.n/2 + 1;
        int start_x = 2*(game_state->ghost_piece.x - game_state->ghost_piece.n/2) + 1;

        for (size_t i = 0; i < game_state->ghost_piece.n; ++i) {
            for (size_t j = 0; j < game_state->ghost_piece.n; ++j) {
                if (game_state->ghost_piece.M[game_state->ghost_piece.r][i][j] == 1) {
                    mvwprintw(window, start_y + i, start_x + 2*j, "%c%c", GHOST_LEFT, GHOST_RIGHT);
                }
            }
        }
        
        wrefresh(window);
    }
}
