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
const int PAUSE_WINDOW_W = 14;
const int PAUSE_WINDOW_Y = 9;
const int PAUSE_WINDOW_X = 18;

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
const char GHOST_LEFT       = '[';
const char GHOST_RIGHT      = ']';
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
        .content_x = x+1
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

    char* key_bind_move    = "< >";
    char* key_bind_rotate  = "z x";
    char* key_bind_hold      = "c";
    char* key_bind_soft_drop = "v";
    char* key_bind_hard_drop = "_";
    char* key_bind_pause   = "esc";

    mvwprintw(
        controls_window->content, 0, 0, 
        "\n"
        "move: %*s\n"
        "rotate: %*s\n"
        "hold: %*s\n"
        "soft drop: %*s\n"
        "hard drop: %*s\n"
        "pause: %*s\n",
        controls_window->content_w-6, key_bind_move,
        controls_window->content_w-8, key_bind_rotate,
        controls_window->content_w-6, key_bind_hold,
        controls_window->content_w-11, key_bind_soft_drop,
        controls_window->content_w-11, key_bind_hard_drop,
        controls_window->content_w-7, key_bind_pause
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
        " resume:  _\n"
        " restart: r\n"
        " quit:  esc\n"
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
        " restart: r\n"
        " quit:  esc\n"
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
    wrefresh(board_window->content);
}

void draw_buffer_zone_line(GameWindow* board_window, GameState* game_state) {
    wattron(board_window->content, COLOR_PAIR(COLOR_PAIR_RED) | A_DIM);
    for (size_t i = 0; i < board_window->content_w; ++i) {
        mvwprintw(board_window->content, BUFFER_ZONE_H-1, i, "%c", BUFFER_ZONE_LINE);
    }
    wattroff(board_window->content, COLOR_PAIR(COLOR_PAIR_RED) | A_DIM);
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
    if (game_state->lock_delay_timer >= 5 && game_state->lock_delay_timer <= 20) {
        wattron(board_window->content, A_DIM);
    } else if (game_state->lock_delay_timer < 5) {
        wattron(board_window->content, A_STANDOUT);
    }

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1) {
                mvwprintw(board_window->content, start_y + i, start_x + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }
    
    wattroff(board_window->content, COLOR_PAIR(game_state->curr_piece.shape));
    if (game_state->lock_delay_timer >= 5 && game_state->lock_delay_timer <= 20) {
        wattroff(board_window->content, A_DIM);
    } else if (game_state->lock_delay_timer < 5) {
        wattroff(board_window->content, A_STANDOUT);
    }
}

void draw_ghost_piece(GameWindow* board_window, GameState* game_state) {
    if (game_state->ghost_piece.y != game_state->curr_piece.y) {
        int start_y = game_state->ghost_piece.y - game_state->ghost_piece.n/2;
        int start_x = 2*(game_state->ghost_piece.x - game_state->ghost_piece.n/2);
        wattron(board_window->content, COLOR_PAIR(game_state->ghost_piece.shape) | A_DIM);

        for (size_t i = 0; i < game_state->ghost_piece.n; ++i) {
            for (size_t j = 0; j < game_state->ghost_piece.n; ++j) {
                if (game_state->ghost_piece.M[game_state->ghost_piece.r][i][j] == 1) {
                    mvwprintw(board_window->content, start_y + i, start_x + 2*j, "%c%c", GHOST_LEFT, GHOST_RIGHT);
                }
            }
        }
        
        wattroff(board_window->content, COLOR_PAIR(game_state->ghost_piece.shape) | A_DIM);
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
    wrefresh(board_window->border);
}

void draw_hold_piece(GameWindow* hold_window, GameState* game_state) {
    werase(hold_window->content);
    
    if (game_state->holding_piece) {
        size_t horizontal_padding = 2*(game_state->hold_piece.n - game_state->hold_piece.l);
        size_t start_y = hold_window->content_h / 2 - game_state->hold_piece.n/2;
        size_t start_x = hold_window->content_w / 2 - game_state->hold_piece.l - horizontal_padding;
        wattron(hold_window->content, COLOR_PAIR(game_state->hold_piece.shape));
        if (game_state->hold_blocked) {
            wattron(hold_window->content, A_DIM);
        }
    
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
        if (game_state->hold_blocked) {
            wattroff(hold_window->content, A_DIM);
        }
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
    // werase(stats_window->content);

    size_t h = stats->seconds / 3600;
    size_t m = (stats->seconds - 3600*h) / 60;
    size_t s = stats->seconds - 3600*h - 60*m;

    mvwprintw(
        stats_window->content, 0, 0,
        "\ntime: %02lu:%02lu\n"
        "\nlines: %lu\n"
        "\nlevel: %lu\n",
        m, s,
        game_state->lines,
        game_state->level
    );

    wrefresh(stats_window->content);
}

void draw_debug_variables(GameWindow* debug_window, GameState* game_state, Stats* stats) {
    werase(debug_window->content);
    mvwprintw(
        debug_window->content, 0, 0,
        "y, x: %i, %i\n"
        "lock_delay_timer: %u\n"
        "move_reset_count: %u\n"
        "gravity_value: %f\n"
        "last_action_points: %lu\n"
        "frame_count: %lu\n",
        game_state->curr_piece.y,
        game_state->curr_piece.x,
        game_state->lock_delay_timer,
        game_state->move_reset_count,
        game_state->gravity_value,
        game_state->last_action_points,
        stats->frame_count
    );
    wrefresh(debug_window->content);
}
