#include <ncurses.h>
#include <string.h>
#include "game_state.h"
#include "draw.h"
#include "piece.h"
#include "stats.h"
#include "logger.h"


const int HOLD_WINDOW_H = 6;
const int HOLD_WINDOW_W = 14;
const int HOLD_WINDOW_Y = 2;
const int HOLD_WINDOW_X = 0;

const int STATS_WINDOW_H = 16;
const int STATS_WINDOW_W = 14;
const int STATS_WINDOW_Y = 8;
const int STATS_WINDOW_X = 0;

const int BOARD_WINDOW_H = 24;
const int BOARD_WINDOW_W = 22;
const int BOARD_WINDOW_Y = 0;
const int BOARD_WINDOW_X = 14;

const int NEXT_WINDOW_H = 6;
const int NEXT_WINDOW_W = 14;
const int NEXT_WINDOW_Y = 2;
const int NEXT_WINDOW_X = 36;

const int CONTROLS_WINDOW_H = 16;
const int CONTROLS_WINDOW_W = 14;
const int CONTROLS_WINDOW_Y = 8;
const int CONTROLS_WINDOW_X = 36;

const int DEBUG_WINDOW_H = 24;
const int DEBUG_WINDOW_W = 36;
const int DEBUG_WINDOW_Y = 0;
const int DEBUG_WINDOW_X = 50;

const int PAUSE_WINDOW_H = 5;
const int PAUSE_WINDOW_W = 16;
const int PAUSE_WINDOW_Y = 9;
const int PAUSE_WINDOW_X = 17;

const int GAME_OVER_WINDOW_H = 4;
const int GAME_OVER_WINDOW_W = 14;
const int GAME_OVER_WINDOW_Y = 10;
const int GAME_OVER_WINDOW_X = 18;

const int16_t COLOR_PAIR_DEFAULT   = 0;
const int16_t COLOR_PAIR_CYAN      = I;
const int16_t COLOR_PAIR_BLUE      = J;
const int16_t COLOR_PAIR_ORANGE    = L;
const int16_t COLOR_PAIR_YELLOW    = O;
const int16_t COLOR_PAIR_GREEN     = S;
const int16_t COLOR_PAIR_MAGENTA   = T;
const int16_t COLOR_PAIR_RED       = Z;

const char BLOCK_LEFT       = '[';
const char BLOCK_RIGHT      = ']';
const char GHOST_LEFT       = ':';
const char GHOST_RIGHT      = ':';
const char BOARD_SPACE      = ' ';
const char BUFFER_ZONE_LINE = '_';

GameWindow game_window_get(int height, int width, int y, int x) {
    WINDOW* border = newwin(height, width, y, x);
    WINDOW* content = subwin(border, height-2, width-2, y+1, x+1);
    GameWindow game_window = {
        .border = border,
        .content = content,
        .border_h = height,
        .border_w = width,
        .border_y = y,
        .border_x = x,
        .content_h = height-2,
        .content_w = width-2,
        .content_y = y+1,
        .content_x = x+1,
        .title = { 0 },
        .content_text = { 0 }
    };
    return game_window;
}

GameWindow* game_window_init(int height, int width, int y, int x) {
    GameWindow* game_window = malloc(sizeof(GameWindow));
    *game_window = game_window_get(height, width, y, x);
    return game_window;
}

void game_window_destroy(GameWindow* game_window) {
    if (!game_window) {
        return;
    }
    delwin(game_window->border);
    delwin(game_window->content);
    *game_window = (GameWindow){ 0 };
    free(game_window);
}

void draw_window_border(GameWindow* game_window, int16_t color_pair) {
    wattron(game_window->border, COLOR_PAIR(color_pair));
    box(game_window->border, 0, 0);
    wattroff(game_window->border, COLOR_PAIR(color_pair));
}

void draw_window_title(GameWindow* game_window, char* title, int16_t color_pair) {
    wattron(game_window->border, COLOR_PAIR(color_pair));
    mvwprintw(game_window->border, 0, 1, "%s", title);
    wattroff(game_window->border, COLOR_PAIR(color_pair));
}

void draw_board_window(GameWindow* board_window) {
    draw_window_border(board_window, COLOR_PAIR_DEFAULT);
    wrefresh(board_window->border);
}

void draw_hold_window(GameWindow* hold_window) {
    draw_window_border(hold_window, COLOR_PAIR_DEFAULT);
    draw_window_title(hold_window, "HOLD", COLOR_PAIR_DEFAULT);
    wrefresh(hold_window->border);
}

void draw_next_window(GameWindow* next_window) {
    draw_window_border(next_window, COLOR_PAIR_DEFAULT);
    draw_window_title(next_window, "NEXT", COLOR_PAIR_DEFAULT);
    wrefresh(next_window->border);
}

void draw_stats_window(GameWindow* stats_window) {
    draw_window_border(stats_window, COLOR_PAIR_DEFAULT);
    draw_window_title(stats_window, "STATS", COLOR_PAIR_DEFAULT);
    mvwprintw(
        stats_window->content, 0, 0,
        "\ntime:\n"
        "\nlines:\n"
        "\nlevel:\n"
    );
    wrefresh(stats_window->border);
    wrefresh(stats_window->content);
}

void draw_controls_window(GameWindow* controls_window) {
    draw_window_border(controls_window, COLOR_PAIR_DEFAULT);
    draw_window_title(controls_window, "CONTROLS", COLOR_PAIR_DEFAULT);
    mvwprintw(
        controls_window->content, 0, 0, 
        "\n"
        "move:    < >\n"
        "rotate:  z x\n"
        "hold:      c\n"
        "soft drop: v\n"
        "hard drop: _\n"
        "pause:   esc\n"
    );
    wrefresh(controls_window->border);
    wrefresh(controls_window->content);
}

void draw_pause_window(GameWindow* pause_window) {
    draw_window_border(pause_window, COLOR_PAIR_CYAN);
    draw_window_title(pause_window, "PAUSE", COLOR_PAIR_CYAN);
    mvwprintw(
        pause_window->content,
        0, 0,
        "space: resume\n"
        "r: restart\n"
        "esc: quit\n"
    );
    wrefresh(pause_window->border);
    wrefresh(pause_window->content);
}

void draw_game_over_window(GameWindow* game_over_window) {
    draw_window_border(game_over_window, COLOR_PAIR_RED);
    draw_window_title(game_over_window, "GAME-OVER", COLOR_PAIR_RED);
    mvwprintw(
        game_over_window->content,
        0, 0,
        "r: restart\n"
        "esc: quit\n"
    );
    wrefresh(game_over_window->border);
    wrefresh(game_over_window->content);
}

void draw_debug_window(GameWindow* debug_window) {
    draw_window_border(debug_window, COLOR_PAIR_RED);
    draw_window_title(debug_window, "DEBUG", COLOR_PAIR_RED);
    wrefresh(debug_window->border);
}

void draw_board_state(GameWindow* board_window, GameState* game_state) {
    werase(board_window->content);
    draw_buffer_zone_line(board_window, game_state);
    draw_board_stack(board_window, game_state);
    draw_ghost_piece(board_window, game_state);
    draw_curr_piece(board_window, game_state);
    draw_score(board_window, game_state);
}

void draw_buffer_zone_line(GameWindow* board_window, GameState* game_state) {
    for (size_t i = 0; i < board_window->content_w; ++i) {
        mvwprintw(board_window->content, BUFFER_ZONE_H-1, i, "%c", BUFFER_ZONE_LINE);
    }
}

void draw_board_stack(GameWindow* board_window, GameState* game_state) {
    for (size_t i = 0; i < BOARD_H; ++i) {
        for (size_t j = 0; j < BOARD_W; ++j) {
            if (game_state->board[i][j] > 0) {
                wattron(board_window->content, COLOR_PAIR(game_state->board[i][j]));
                mvwprintw(board_window->content, i, 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
                wattroff(board_window->content, COLOR_PAIR(game_state->board[i][j]));
            }
        }
    }
}

void draw_curr_piece(GameWindow* board_window, GameState* game_state) {
    int start_y = game_state->curr_piece.y - game_state->curr_piece.n/2;
    int start_x = 2*(game_state->curr_piece.x - game_state->curr_piece.n/2);
    wattron(board_window->content, COLOR_PAIR(game_state->curr_piece.shape));

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1) {
                mvwprintw(board_window->content, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }
    
    wattroff(board_window->content, COLOR_PAIR(game_state->curr_piece.shape));
}

void draw_ghost_piece(GameWindow* board_window, GameState* game_state) {
    if (game_state->ghost_piece.y != game_state->curr_piece.y) {
        int start_y = game_state->ghost_piece.y - game_state->ghost_piece.n/2;
        int start_x = 2*(game_state->ghost_piece.x - game_state->ghost_piece.n/2);
        wattron(board_window->content, COLOR_PAIR(game_state->ghost_piece.shape));

        for (size_t i = 0; i < game_state->ghost_piece.n; ++i) {
            for (size_t j = 0; j < game_state->ghost_piece.n; ++j) {
                if (game_state->ghost_piece.M[game_state->ghost_piece.r][i][j] == 1) {
                    mvwprintw(board_window->content, start_y + i, start_x + 2*j, "%c%c", GHOST_LEFT, GHOST_RIGHT);
                }
            }
        }
        
        wattroff(board_window->content, COLOR_PAIR(game_state->ghost_piece.shape));
    }
}

void draw_score(GameWindow* board_window, GameState* game_state) {
    mvwprintw(
        board_window->border, 
        board_window->border_h-1, 
        board_window->border_w/2-4, 
        "%08lu", 
        game_state->score
    );
}

void draw_hold_piece(GameWindow* hold_window, GameState* game_state) {
    werase(hold_window->content);
    
    if (game_state->holding_piece) {
        size_t horizontal_padding = 2*(game_state->hold_piece.n - game_state->hold_piece.l);
        size_t start_y = hold_window->content_h / 2 - game_state->hold_piece.n/2;
        size_t start_x = hold_window->content_w / 2 - game_state->hold_piece.l - horizontal_padding;
        wattron(hold_window->content, COLOR_PAIR(game_state->hold_piece.shape));
    
        for (size_t i = 0; i < game_state->hold_piece.n; ++i) {
            for (size_t j = 0; j < game_state->hold_piece.n; ++j) {
                if (game_state->hold_piece.M[0][i][j] == 1) {
                    if (game_state->hold_blocked) {
                        mvwprintw(hold_window->content, start_y + i, start_x + 2*j, "%c%c", GHOST_LEFT, GHOST_RIGHT);
                    } else {
                        mvwprintw(hold_window->content, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
                    }
                }
            }
        }

        wattroff(hold_window->content, COLOR_PAIR(game_state->hold_piece.shape));
    }

    wrefresh(hold_window->content);
}

void draw_next_piece(GameWindow* next_window, GameState* game_state) {
    werase(next_window->content);

    size_t horizontal_padding = 2*(game_state->next_piece.n - game_state->next_piece.l);
    size_t start_y = next_window->content_h / 2 - game_state->next_piece.n/2;
    size_t start_x = next_window->content_w / 2 - game_state->next_piece.l - horizontal_padding;
    wattron(next_window->content, COLOR_PAIR(game_state->next_piece.shape));

    for (size_t i = 0; i < game_state->next_piece.n; ++i) {
        for (size_t j = 0; j < game_state->next_piece.n; ++j) {
            if (game_state->next_piece.M[0][i][j] == 1) {
                mvwprintw(next_window->content, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }
    
    wattroff(next_window->content, COLOR_PAIR(game_state->next_piece.shape));

    wrefresh(next_window->content);
}

void draw_stats(GameWindow* stats_window, GameState* game_state, Stats* stats) {
    werase(stats_window->content);

    size_t h = stats->time / 3600;
    size_t m = (stats->time - 3600*h) / 60;
    size_t s = stats->time - 3600*h - 60*m;

    mvwprintw(
        stats_window->content, 0, 0,
        "\ntime: %02lu:%02lu\n"
        "\nlines: %lu\n"
        "\nlevel: %lu\n",
        m, s,
        game_state->lines,
        game_state->level
    );

    // draw last action point information from bottom to top
    size_t start_y = stats_window->content_h - 1;
    if (game_state->last_action_points > 0) {
        draw_stats_last_action_points(stats_window, game_state, start_y);
        start_y--;
    }
    if (game_state->difficult_clear_combo > 0) {
        draw_stats_difficult_clear_combo(stats_window, game_state, start_y);
        start_y--;
    }
    if (game_state->combo > 0) {
        draw_stats_combo(stats_window, game_state, start_y);
        start_y--;
    }
    if (strlen(game_state->last_action_string) > 0) {
        draw_stats_last_action_string(stats_window, game_state, start_y);
    }

    wrefresh(stats_window->content);
}

void draw_stats_last_action_string(GameWindow* stats_window, GameState* game_state, size_t start_y) {
    int space_index = strlen(game_state->last_action_string) - 1;
    int end_index = strlen(game_state->last_action_string) - 1;

    // traverse last_action_string backwards and print maximum length, space 
    // delimited, chunks of last_action_string from botttom to top
    for (int i = strlen(game_state->last_action_string); i >= 0; --i) {
        if (game_state->last_action_string[i] == ' ') {
            if (end_index - i > stats_window->content_w) {
                mvwprintw(
                    stats_window->content, 
                    start_y--, 
                    0, 
                    "%.*s", 
                    end_index - space_index, 
                    game_state->last_action_string + space_index + 1
                );
                end_index = space_index - 1;
            }
            space_index = i;
        }
    }
    
    // print remaining chunk after space if it doesn't fit within internal_w
    if (end_index + 1 > stats_window->content_w) {
        mvwprintw(
            stats_window->content, 
            start_y--, 
            1, 
            "%.*s", 
            end_index - space_index, 
            game_state->last_action_string + space_index + 1
        );
        end_index = space_index - 1;
    }

    // print chunk that reaches from beginning of string to either last space or end of string
    mvwprintw(stats_window->content, start_y--, 0, "%.*s", end_index + 1, game_state->last_action_string);
}

void draw_stats_combo(GameWindow* stats_window, GameState* game_state, size_t start_y) {
    mvwprintw(stats_window->content, start_y, 0, "%li x combo", game_state->combo);
}

void draw_stats_difficult_clear_combo(GameWindow* stats_window, GameState* game_state, size_t start_y) {
    mvwprintw(stats_window->content, start_y, 0, "%li x b2b", game_state->difficult_clear_combo);
}

void draw_stats_last_action_points(GameWindow* stats_window, GameState* game_state, size_t start_y) {
    mvwprintw(stats_window->content, start_y, 0, "%*lu", stats_window->content_w, game_state->last_action_points);
}

void draw_debug_variables(GameWindow* debug_window, GameState* game_state, Stats* stats) {
    werase(debug_window->content);
    mvwprintw(
        debug_window->content, 0, 0,
        "y: %i\n"
        "x: %i\n"
        "lock_delay_timer: %u\n"
        "move_reset_count: %u\n"
        "gravity_value: %f\n"
        "last_action_points: %lu\n"
        "last_action_string: %s\n"
        "frame_count: %lu\n",
        game_state->curr_piece.y,
        game_state->curr_piece.x,
        game_state->lock_delay_timer,
        game_state->move_reset_count,
        game_state->gravity_value,
        game_state->last_action_points,
        game_state->last_action_string,
        stats->frame_count
    );
    wrefresh(debug_window->content);
}
