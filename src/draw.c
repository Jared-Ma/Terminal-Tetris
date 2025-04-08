#include "draw.h"
#include "game_state.h"
#include "logger.h"
#include "stats.h"

#include <ncurses.h>
#include <stdint.h>
#include <string.h>


// Total dimensions of the game.
const int8_t GAME_H = 24;
const int8_t GAME_W = 50;

// Dimensions and coordinates of each game window.
const int8_t BOARD_WINDOW_H = 24;
const int8_t BOARD_WINDOW_W = 22;
const int8_t BOARD_WINDOW_Y = 0;
const int8_t BOARD_WINDOW_X = 14;

const int8_t HOLD_WINDOW_H = 6;
const int8_t HOLD_WINDOW_W = 14;
const int8_t HOLD_WINDOW_Y = 2;
const int8_t HOLD_WINDOW_X = 0;

const int8_t NEXT_WINDOW_H = 6;
const int8_t NEXT_WINDOW_W = 14;
const int8_t NEXT_WINDOW_Y = 2;
const int8_t NEXT_WINDOW_X = 36;

const int8_t STATS_WINDOW_H = 16;
const int8_t STATS_WINDOW_W = 14;
const int8_t STATS_WINDOW_Y = 8;
const int8_t STATS_WINDOW_X = 0;

const int8_t HELP_WINDOW_H = 16;
const int8_t HELP_WINDOW_W = 14;
const int8_t HELP_WINDOW_Y = 8;
const int8_t HELP_WINDOW_X = 36;

const int8_t MAIN_MENU_WINDOW_H = 18;
const int8_t MAIN_MENU_WINDOW_W = 40;
const int8_t MAIN_MENU_WINDOW_Y = 3;
const int8_t MAIN_MENU_WINDOW_X = 5;

const int8_t PAUSE_WINDOW_H = 5;
const int8_t PAUSE_WINDOW_W = 14;
const int8_t PAUSE_WINDOW_Y = 9;
const int8_t PAUSE_WINDOW_X = 18;

const int8_t GAME_OVER_WINDOW_H = 4;
const int8_t GAME_OVER_WINDOW_W = 14;
const int8_t GAME_OVER_WINDOW_Y = 9;
const int8_t GAME_OVER_WINDOW_X = 18;

const int8_t DEBUG_WINDOW_H = 24;
const int8_t DEBUG_WINDOW_W = 50;
const int8_t DEBUG_WINDOW_Y = 0;
const int8_t DEBUG_WINDOW_X = 50;

const int8_t LOGS_WINDOW_H = 20;
const int8_t LOGS_WINDOW_W = 100;
const int8_t LOGS_WINDOW_Y = 24;
const int8_t LOGS_WINDOW_X = 0;

// Width of the score display at the bottom of the board window.
const int8_t BOARD_SCORE_W = 8;

// Coordinates of each label relative to their corresponding window.
const int8_t STATS_TIME_Y  = 1;
const int8_t STATS_TIME_X  = 0;
const int8_t STATS_LINES_Y = 3;
const int8_t STATS_LINES_X = 0;
const int8_t STATS_LEVEL_Y = 5;
const int8_t STATS_LEVEL_X = 0;
const int8_t STATS_SPS_Y   = 7;
const int8_t STATS_SPS_X   = 0;
const int8_t STATS_PPS_Y   = 8;
const int8_t STATS_PPS_X   = 0;

const int8_t HELP_MOVE_Y      = 1;
const int8_t HELP_MOVE_X      = 0;
const int8_t HELP_ROTATE_Y    = 3;
const int8_t HELP_ROTATE_X    = 0;
const int8_t HELP_HOLD_Y      = 5;
const int8_t HELP_HOLD_X      = 0;
const int8_t HELP_SOFT_DROP_Y = 7;
const int8_t HELP_SOFT_DROP_X = 0;
const int8_t HELP_HARD_DROP_Y = 9;
const int8_t HELP_HARD_DROP_X = 0;
const int8_t HELP_PAUSE_Y     = 11;
const int8_t HELP_PAUSE_X     = 0;
const int8_t HELP_SET_DELAY_Y = 13;
const int8_t HELP_SET_DELAY_X = 0;

const int8_t MAIN_MENU_TITLE_H          = 4;
const int8_t MAIN_MENU_TITLE_TERMINAL_Y = 0;
const int8_t MAIN_MENU_TITLE_TERMINAL_X = 2;
const int8_t MAIN_MENU_TITLE_TETRIS_Y   = 4;
const int8_t MAIN_MENU_TITLE_TETRIS_X   = 7;

const int8_t MAIN_MENU_LEVEL_W = 8;
const int8_t MAIN_MENU_LEVEL_Y = 10;
const int8_t MAIN_MENU_LEVEL_X = 13;
const int8_t MAIN_MENU_START_Y = 12;
const int8_t MAIN_MENU_START_X = 15;
const int8_t MAIN_MENU_QUIT_Y =  14;
const int8_t MAIN_MENU_QUIT_X =  15;

const int8_t PAUSE_RESUME_Y  = 0;
const int8_t PAUSE_RESUME_X  = 1;
const int8_t PAUSE_RESTART_Y = 1;
const int8_t PAUSE_RESTART_X = 1;
const int8_t PAUSE_QUIT_Y    = 2;
const int8_t PAUSE_QUIT_X    = 1;

const int8_t PAUSE_STATS_SINGLE_Y = 10;
const int8_t PAUSE_STATS_SINGLE_X = 0;
const int8_t PAUSE_STATS_DOUBLE_Y = 11;
const int8_t PAUSE_STATS_DOUBLE_X = 0;
const int8_t PAUSE_STATS_TRIPLE_Y = 12;
const int8_t PAUSE_STATS_TRIPLE_X = 0;
const int8_t PAUSE_STATS_TETRIS_Y = 13;
const int8_t PAUSE_STATS_TETRIS_X = 0;

const int8_t GAME_OVER_RESTART_Y = 0;
const int8_t GAME_OVER_RESTART_X = 1;
const int8_t GAME_OVER_QUIT_Y    = 1;
const int8_t GAME_OVER_QUIT_X    = 1;

// Title strings for each window.
const char* HOLD_TITLE      = "HOLD";
const char* NEXT_TITLE      = "NEXT";
const char* STATS_TITLE     = "STATS";
const char* HELP_TITLE      = "HELP";
const char* PAUSE_TITLE     = "PAUSE";
const char* GAME_OVER_TITLE = "GAME-OVER";
const char* DEBUG_TITLE     = "DEBUG";
const char* LOGS_TITLE      = "LOGS";

// Title string arrays for main menu ASCII art.
const char* MAIN_MENU_TITLE_TERMINAL[4] = {
    " _____              _           _ \n",
    "|_   _|__ _ _ _ __ (_)_ _  __ _| |\n",
    "  | |/ -_) '_| '  \\| | ' \\/ _` | |\n",
    "  |_|\\___|_| |_|_|_|_|_||_\\__,_|_|\n"
};
const char* MAIN_MENU_TITLE_TETRIS[4] = {
    " _____    _       _    \n",
    "|_   _|__| |_ _ _(_)___\n",
    "  | |/ -_)  _| '_| (_-<\n",
    "  |_|\\___|\\__|_| |_/__/\n"
};

// Characters used for pieces and board.
const char BLOCK_LEFT       = '[';
const char BLOCK_RIGHT      = ']';
const char BOARD_SPACE      = ' ';
const char BUFFER_ZONE_LINE = '_';

// Available colors as color pairs.
const int16_t COLOR_PAIR_DEFAULT = 0;
const int16_t COLOR_PAIR_CYAN    = I;
const int16_t COLOR_PAIR_BLUE    = J;
const int16_t COLOR_PAIR_ORANGE  = L;
const int16_t COLOR_PAIR_YELLOW  = O;
const int16_t COLOR_PAIR_GREEN   = S;
const int16_t COLOR_PAIR_MAGENTA = T;
const int16_t COLOR_PAIR_RED     = Z;

// Lock delay frame bounds for DIM and STANDOUT window attributes when drawing current piece.  
const uint16_t LOCK_DELAY_DIM_MAX      = 20;
const uint16_t LOCK_DELAY_DIM_MIN      = 5;
const uint16_t LOCK_DELAY_STANDOUT_MAX = 4;
const uint16_t LOCK_DELAY_STANDOUT_MIN = 0;

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
    delwin(game_window->content);
    delwin(game_window->border);
    *game_window = (GameWindow){ 0 };
    free(game_window);
}

void game_window_refresh(GameWindow* game_window) {
    wrefresh(game_window->border);
    wrefresh(game_window->content);
}

void draw_window_border(GameWindow* game_window, int16_t color_pair) {
    wattron(game_window->border, COLOR_PAIR(color_pair));
    box(game_window->border, 0, 0);
    wattroff(game_window->border, COLOR_PAIR(color_pair));
}

void draw_window_title(GameWindow* game_window, const char* title, int16_t color_pair) {
    wattron(game_window->border, COLOR_PAIR(color_pair));
    mvwprintw(game_window->border, 0, 1, "%s", title);
    wattroff(game_window->border, COLOR_PAIR(color_pair));
}

void draw_board_window(GameWindow* board_window) {
    draw_window_border(board_window, COLOR_PAIR_DEFAULT);
}

void draw_hold_window(GameWindow* hold_window) {
    draw_window_border(hold_window, COLOR_PAIR_DEFAULT);
    draw_window_title(hold_window, HOLD_TITLE, COLOR_PAIR_DEFAULT);
}

void draw_next_window(GameWindow* next_window) {
    draw_window_border(next_window, COLOR_PAIR_DEFAULT);
    draw_window_title(next_window, NEXT_TITLE, COLOR_PAIR_DEFAULT);
}

void draw_stats_window(GameWindow* stats_window) {
    draw_window_border(stats_window, COLOR_PAIR_DEFAULT);
    draw_window_title(stats_window, STATS_TITLE, COLOR_PAIR_DEFAULT);
    mvwprintw(stats_window->content, STATS_TIME_Y, STATS_TIME_X, "time:");
    mvwprintw(stats_window->content, STATS_LEVEL_Y, STATS_LEVEL_X, "level:");
    mvwprintw(stats_window->content, STATS_LINES_Y, STATS_LINES_X, "lines:");
    mvwprintw(stats_window->content, STATS_SPS_Y, STATS_SPS_X, "sps:");
    mvwprintw(stats_window->content, STATS_PPS_Y, STATS_PPS_X, "pps:");
}

void draw_help_window(GameWindow* help_window) {
    draw_window_border(help_window, COLOR_PAIR_DEFAULT);
    draw_window_title(help_window, HELP_TITLE, COLOR_PAIR_DEFAULT);

    char* move_label      = "move: ";
    char* rotate_label    = "rotate: ";
    char* hold_label      = "hold: ";
    char* soft_drop_label = "soft drop: ";
    char* hard_drop_label = "hard drop: ";
    char* pause_label     = "pause: ";
    char* set_delay_label = "set delay: ";

    char* move_key      = "< >";
    char* rotate_key    = "z x";
    char* hold_key      = "c";
    char* soft_drop_key = "v";
    char* hard_drop_key = "_";
    char* pause_key     = "esc";
    char* set_delay_key = "d";

    // Print controls so labels are left-aligned and corresponding keys are right-aligned.
    mvwprintw(
        help_window->content, 
        HELP_MOVE_Y, 
        HELP_MOVE_X, 
        "%s%*s", 
        move_label,
        (int)(help_window->content_w - strlen(move_label)), 
        move_key
    );
    mvwprintw(
        help_window->content, 
        HELP_ROTATE_Y, 
        HELP_ROTATE_X, 
        "%s%*s", 
        rotate_label, 
        (int)(help_window->content_w - strlen(rotate_label)),  
        rotate_key
    );
    mvwprintw(
        help_window->content, 
        HELP_HOLD_Y, 
        HELP_HOLD_X, 
        "%s%*s", 
        hold_label,
        (int)(help_window->content_w - strlen(hold_label)), 
        hold_key
    );
    mvwprintw(
        help_window->content, 
        HELP_SOFT_DROP_Y, 
        HELP_SOFT_DROP_X, 
        "%s%*s",
        soft_drop_label, 
        (int)(help_window->content_w - strlen(soft_drop_label)), 
        soft_drop_key
    );
    mvwprintw(
        help_window->content, 
        HELP_HARD_DROP_Y, 
        HELP_HARD_DROP_X, 
        "%s%*s", 
        hard_drop_label, 
        (int)(help_window->content_w - strlen(hard_drop_label)), 
        hard_drop_key
    );
    mvwprintw(
        help_window->content, 
        HELP_PAUSE_Y, 
        HELP_PAUSE_X, 
        "%s%*s", 
        pause_label, 
        (int)(help_window->content_w - strlen(pause_label)), 
        pause_key
    );
    if (debug_mode) {
        mvwprintw(
            help_window->content, 
            HELP_SET_DELAY_Y, 
            HELP_SET_DELAY_X, 
            "%s%*s", 
            set_delay_label, 
            (int)(help_window->content_w - strlen(set_delay_label)), 
            set_delay_key
        );
    }
}

void draw_main_menu_window(GameWindow* main_menu_window, uint8_t start_level) {
    draw_window_border(main_menu_window, COLOR_PAIR_DEFAULT);
    
    // Print each line composing the 'TERMINAL' title.
    for (size_t i = 0; i < MAIN_MENU_TITLE_H; ++i) {
        mvwprintw(
            main_menu_window->content, 
            MAIN_MENU_TITLE_TERMINAL_Y + i, 
            MAIN_MENU_TITLE_TERMINAL_X, 
            "%s", 
            MAIN_MENU_TITLE_TERMINAL[i]
        );
    }

    uint8_t num_colors = 6;
    int16_t title_colors[6] = {
        COLOR_PAIR_RED,
        COLOR_PAIR_ORANGE,
        COLOR_PAIR_YELLOW,
        COLOR_PAIR_GREEN,
        COLOR_PAIR_CYAN,
        COLOR_PAIR_MAGENTA
    };

    // The first and second value of each pair indicate the lower and upper bounds of each of 
    // the six colors, a column for each color, and a row for each line that composes the title.
    int8_t color_bounds[4][6][2] = {
        {{1, 5}, {-1, -1}, {10, 10}, {-1, -1}, {18, 18}, {-1, -1}},
        {{0, 6},   {7, 8},  {9, 12}, {14, 16}, {17, 19}, {20, 22}},
        {{2, 4},   {5, 9}, {10, 13}, {14, 16}, {17, 18}, {19, 22}},
        {{2, 4},   {5, 9}, {10, 12}, {13, 16}, {17, 18}, {19, 22}}
    };

    // Print each character of each line composing the 'TETRIS'.
    for (size_t i = 0; i < MAIN_MENU_TITLE_H; ++i) {
        for (size_t j = 0; j < strlen(MAIN_MENU_TITLE_TETRIS[i]); ++j) {

            // Check which color the current character should be, by checking which bound it fits within.
            size_t color_index = 0;
            for (size_t k = 0; k < num_colors; ++k) {
                if (j >= color_bounds[i][k][0] && j <= color_bounds[i][k][1]) {
                    color_index = k;
                    break;
                }
            }

            wattron(main_menu_window->content, COLOR_PAIR(title_colors[color_index]));
            mvwaddch(
                main_menu_window->content,
                MAIN_MENU_TITLE_TETRIS_Y + i,
                MAIN_MENU_TITLE_TETRIS_X + j,
                MAIN_MENU_TITLE_TETRIS[i][j]
            );
            wattroff(main_menu_window->content, COLOR_PAIR(title_colors[color_index]));
        }
    }

    mvwprintw(
        main_menu_window->content, 
        MAIN_MENU_LEVEL_Y, 
        MAIN_MENU_LEVEL_X, 
        "< level%*u >", 
        (int)(MAIN_MENU_LEVEL_W - strlen("level")), 
        start_level
    );
    mvwprintw(main_menu_window->content, MAIN_MENU_START_Y, MAIN_MENU_START_X, "start: _");
    mvwprintw(main_menu_window->content, MAIN_MENU_QUIT_Y, MAIN_MENU_QUIT_X, "quit: esc");
}

void draw_pause_window(GameWindow* pause_window) {
    draw_window_border(pause_window, COLOR_PAIR_CYAN);
    draw_window_title(pause_window, PAUSE_TITLE, COLOR_PAIR_CYAN);
    mvwprintw(pause_window->content, PAUSE_RESUME_Y, PAUSE_RESUME_X, "resume:  _");
    mvwprintw(pause_window->content, PAUSE_RESTART_Y, PAUSE_RESTART_X, "restart: r");
    mvwprintw(pause_window->content, PAUSE_QUIT_Y, PAUSE_QUIT_X, "back:  esc");
}

void draw_game_over_window(GameWindow* game_over_window) {
    draw_window_border(game_over_window, COLOR_PAIR_RED);
    draw_window_title(game_over_window, GAME_OVER_TITLE, COLOR_PAIR_RED);
    mvwprintw(game_over_window->content, GAME_OVER_RESTART_Y, GAME_OVER_RESTART_X, "restart: r");
    mvwprintw(game_over_window->content, GAME_OVER_QUIT_Y, GAME_OVER_QUIT_X, "back:  esc");
}

void draw_debug_window(GameWindow* debug_window) {
    draw_window_border(debug_window, COLOR_PAIR_RED);
    draw_window_title(debug_window, DEBUG_TITLE, COLOR_PAIR_RED);
}

void draw_logs_window(GameWindow* logs_window) {
    draw_window_border(logs_window, COLOR_PAIR_RED);
    draw_window_title(logs_window, LOGS_TITLE, COLOR_PAIR_RED);
}

void draw_board_state(GameWindow* board_window, const GameState* game_state) {
    werase(board_window->content);
    draw_buffer_zone_line(board_window);
    draw_board_stack(board_window, game_state);
    draw_ghost_piece(board_window, game_state);
    draw_curr_piece(board_window, game_state);
    draw_score(board_window, game_state);
}

void draw_buffer_zone_line(GameWindow* board_window) {
    wattron(board_window->content, COLOR_PAIR(COLOR_PAIR_RED) | A_DIM);
    for (size_t i = 0; i < board_window->content_w; ++i) {
        mvwprintw(board_window->content, BUFFER_ZONE_H-1, i, "%c", BUFFER_ZONE_LINE);
    }
    wattroff(board_window->content, COLOR_PAIR(COLOR_PAIR_RED) | A_DIM);
}

void draw_board_stack(GameWindow* board_window, const GameState* game_state) {
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

void draw_curr_piece(GameWindow* board_window, const GameState* game_state) {
    // Calculate where to start printing from according to piece shape
    int8_t y_start = game_state->curr_piece.y - game_state->curr_piece.n/2;
    int8_t x_start = 2*(game_state->curr_piece.x - game_state->curr_piece.n/2);

    wattron(board_window->content, COLOR_PAIR(game_state->curr_piece.shape));
    if (
        game_state->lock_delay_timer >= LOCK_DELAY_DIM_MIN && 
        game_state->lock_delay_timer <= LOCK_DELAY_DIM_MAX
    ) {
        wattron(board_window->content, A_DIM);
    } else if (
        game_state->lock_delay_timer >= LOCK_DELAY_STANDOUT_MIN && 
        game_state->lock_delay_timer <= LOCK_DELAY_STANDOUT_MAX
    ) {
        wattron(board_window->content, A_STANDOUT);
    }

    for (size_t i = 0; i < game_state->curr_piece.n; ++i) {
        for (size_t j = 0; j < game_state->curr_piece.n; ++j) {
            if (game_state->curr_piece.M[game_state->curr_piece.r][i][j] == 1) {
                mvwprintw(board_window->content, y_start + i, x_start + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }
    
    wattroff(board_window->content, COLOR_PAIR(game_state->curr_piece.shape));
    if (
        game_state->lock_delay_timer >= LOCK_DELAY_DIM_MIN && 
        game_state->lock_delay_timer <= LOCK_DELAY_DIM_MAX
    ) {
        wattroff(board_window->content, A_DIM);
    } else if (
        game_state->lock_delay_timer >= LOCK_DELAY_STANDOUT_MIN && 
        game_state->lock_delay_timer <= LOCK_DELAY_STANDOUT_MAX
    ) {
        wattroff(board_window->content, A_STANDOUT);
    }
}

void draw_ghost_piece(GameWindow* board_window, const GameState* game_state) {
    if (game_state->ghost_piece.y != game_state->curr_piece.y) {
        // Calculate where to start printing from according to piece shape
        int8_t y_start = game_state->ghost_piece.y - game_state->ghost_piece.n/2;
        int8_t x_start = 2*(game_state->ghost_piece.x - game_state->ghost_piece.n/2);
        wattron(board_window->content, COLOR_PAIR(game_state->ghost_piece.shape) | A_DIM);

        for (size_t i = 0; i < game_state->ghost_piece.n; ++i) {
            for (size_t j = 0; j < game_state->ghost_piece.n; ++j) {
                if (game_state->ghost_piece.M[game_state->ghost_piece.r][i][j] == 1) {
                    mvwprintw(board_window->content, y_start + i, x_start + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
                }
            }
        }
        
        wattroff(board_window->content, COLOR_PAIR(game_state->ghost_piece.shape) | A_DIM);
    }
}

void draw_score(GameWindow* board_window, const GameState* game_state) {
    mvwprintw(
        board_window->border, 
        board_window->border_h - 1, 
        board_window->border_w / 2 - BOARD_SCORE_W / 2, 
        "%0*lu",
        BOARD_SCORE_W, 
        game_state->score
    );
}

void draw_hold_piece(GameWindow* hold_window, const GameState* game_state) {
    werase(hold_window->content);
    
    if (game_state->holding_piece) {
        // Calculate where to start printing from according to piece shape
        int8_t x_padding = 2*(game_state->hold_piece.n - game_state->hold_piece.l);
        int8_t y_start = hold_window->content_h / 2 - game_state->hold_piece.n / 2;
        int8_t x_start = hold_window->content_w / 2 - game_state->hold_piece.l - x_padding;
        
        wattron(hold_window->content, COLOR_PAIR(game_state->hold_piece.shape));
        if (game_state->hold_blocked) {
            wattron(hold_window->content, A_DIM);
        }
    
        for (size_t i = 0; i < game_state->hold_piece.n; ++i) {
            for (size_t j = 0; j < game_state->hold_piece.n; ++j) {
                if (game_state->hold_piece.M[0][i][j] == 1) {   
                    mvwprintw(hold_window->content, y_start + i, x_start + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
                }
            }
        }

        wattroff(hold_window->content, COLOR_PAIR(game_state->hold_piece.shape));
        if (game_state->hold_blocked) {
            wattroff(hold_window->content, A_DIM);
        }
    }
}

void draw_next_piece(GameWindow* next_window, const GameState* game_state) {
    werase(next_window->content);

    // Calculate where to start printing from according to piece shape
    int8_t x_padding = 2*(game_state->next_piece.n - game_state->next_piece.l);
    int8_t y_start = next_window->content_h / 2 - game_state->next_piece.n / 2;
    int8_t x_start = next_window->content_w / 2 - game_state->next_piece.l - x_padding;
    wattron(next_window->content, COLOR_PAIR(game_state->next_piece.shape));

    for (size_t i = 0; i < game_state->next_piece.n; ++i) {
        for (size_t j = 0; j < game_state->next_piece.n; ++j) {
            if (game_state->next_piece.M[0][i][j] == 1) {
                mvwprintw(next_window->content, y_start + i, x_start + 2*j, "%c%c", BLOCK_LEFT, BLOCK_RIGHT);
            }
        }
    }
    
    wattroff(next_window->content, COLOR_PAIR(game_state->next_piece.shape));
}

void draw_stats(GameWindow* stats_window, const GameState* game_state, const Stats* stats) {
    werase(stats_window->content);

    uint8_t h = stats->game_time_s / 3600;
    uint8_t m = (stats->game_time_s - 3600*h) / 60;
    uint8_t s = stats->game_time_s - 3600*h - 60*m;

    mvwprintw(stats_window->content, STATS_TIME_Y, STATS_TIME_X, "time: %02u:%02u", m, s);
    mvwprintw(stats_window->content, STATS_LINES_Y, STATS_LINES_X, "lines: %u", game_state->lines);
    mvwprintw(stats_window->content, STATS_LEVEL_Y, STATS_LEVEL_X, "level: %u", game_state->level);

    // Adjust print precision to account for leading 0
    if (stats->score_per_s > 0 && stats->score_per_s < 1) {
        mvwprintw(stats_window->content, STATS_SPS_Y, STATS_SPS_X, "sps: %#.4g\n", stats->score_per_s);
    } else {
        mvwprintw(stats_window->content, STATS_SPS_Y, STATS_SPS_X, "sps: %#.5g\n", stats->score_per_s);
    }
    
    // Adjust print precision to account for leading 0
    if (stats->piece_per_s > 0 && stats->piece_per_s < 1) {
        mvwprintw(stats_window->content, STATS_PPS_Y, STATS_PPS_X, "pps: %#.4g\n", stats->piece_per_s);
    } else {
        mvwprintw(stats_window->content, STATS_PPS_Y, STATS_PPS_X, "pps: %#.5g\n", stats->piece_per_s);
    }
}

void draw_pause_stats(GameWindow* stats_window, const Stats* stats) {
    // Clear each line of pause stats, since they may overlap with VFX
    mvwprintw(stats_window->content, PAUSE_STATS_SINGLE_Y, PAUSE_STATS_SINGLE_X, "%*s", stats_window->content_w, "");
    mvwprintw(stats_window->content, PAUSE_STATS_DOUBLE_Y, PAUSE_STATS_DOUBLE_X, "%*s", stats_window->content_w, "");
    mvwprintw(stats_window->content, PAUSE_STATS_TRIPLE_Y, PAUSE_STATS_TRIPLE_X, "%*s", stats_window->content_w, "");
    mvwprintw(stats_window->content, PAUSE_STATS_TETRIS_Y, PAUSE_STATS_TETRIS_X, "%*s", stats_window->content_w, "");
    
    mvwprintw(stats_window->content, PAUSE_STATS_SINGLE_Y, PAUSE_STATS_SINGLE_X, "single: %u", stats->num_single);
    mvwprintw(stats_window->content, PAUSE_STATS_DOUBLE_Y, PAUSE_STATS_DOUBLE_X, "double: %u", stats->num_double);
    mvwprintw(stats_window->content, PAUSE_STATS_TRIPLE_Y, PAUSE_STATS_TRIPLE_X, "triple: %u", stats->num_triple);
    mvwprintw(stats_window->content, PAUSE_STATS_TETRIS_Y, PAUSE_STATS_TETRIS_X, "tetris: %u", stats->num_tetris);
}

void draw_debug_variables(GameWindow* debug_window, const GameState* game_state, const Stats* stats) {
    werase(debug_window->content);
    mvwprintw(
        debug_window->content, 0, 0,
        "curr_piece: (y=%i, x=%i, r=%i, shape=%c)\n"
        "hold_piece: (y=%i, x=%i, r=%i, shape=%c)\n"
        "next_piece: (y=%i, x=%i, r=%i, shape=%c)\n"
        "ghost_piece: (y=%i, x=%i, r=%i, shape=%c)\n"
        "holding_piece: %s\n"
        "hold_blocked: %s\n"
        "next_index: %u\n"
        "next_queue: [%c, %c, %c, %c, %c, %c, %c]\n"
        "gravity_value: %f\n"
        "lock_delay_timer: %u\n"
        "move_reset_count: %u\n"
        "combo: %i\n"
        "difficult_clear_combo: %i\n"
        "tetris_all_clear_combo: %i\n"
        "t_rotation_test_num: %i\n"
        "\n"
        "game_time_s: %f\n"
        "real_time_s: %f\n"
        "num_pieces: %u\n"
        "frame_count: %lu\n"
        "fps: %f\n"
        "frame-by-frame: %s\n",
        game_state->curr_piece.y,
        game_state->curr_piece.x,
        game_state->curr_piece.r,
        shape_to_char(game_state->curr_piece.shape),
        game_state->hold_piece.y,
        game_state->hold_piece.x,
        game_state->hold_piece.r,
        (game_state->holding_piece) ? shape_to_char(game_state->hold_piece.shape) : ' ',
        game_state->next_piece.y,
        game_state->next_piece.x,
        game_state->next_piece.r,
        shape_to_char(game_state->next_piece.shape),
        game_state->ghost_piece.y,
        game_state->ghost_piece.x,
        game_state->ghost_piece.r,
        shape_to_char(game_state->ghost_piece.shape),
        (game_state->holding_piece) ? "true" : "false",
        (game_state->hold_blocked) ? "true" : "false",
        game_state->next_index,
        shape_to_char(game_state->next_queue[0]),
        shape_to_char(game_state->next_queue[1]),
        shape_to_char(game_state->next_queue[2]),
        shape_to_char(game_state->next_queue[3]),
        shape_to_char(game_state->next_queue[4]),
        shape_to_char(game_state->next_queue[5]),
        shape_to_char(game_state->next_queue[6]),
        game_state->gravity_value,
        game_state->lock_delay_timer,
        game_state->move_reset_count,
        game_state->combo,
        game_state->difficult_clear_combo,
        game_state->tetris_all_clear_combo,
        game_state->t_rotation_test_num,
        stats->game_time_s,
        stats->real_time_s,
        stats->num_pieces,
        stats->frame_count,
        stats->fps,
        (is_nodelay(stdscr)) ? "false" : "true"
    );
}

void draw_debug_logs(GameWindow* logs_window, FILE* debug_log, LogBuffer* log_buffer) {
    char line[1024];
    fflush(debug_log);

    // Set position of file pointer to the end of last log that has been printed.
    fsetpos(debug_log, &log_buffer->file_pos);

    // Append each new log that has been written.
    while (fgets(line, sizeof(line), debug_log)) {
        log_buffer_append(log_buffer, line);
    }

    // Print each log starting from the start_index of log_buffer.
    for (size_t i = 0; i < MAX_LOGS; ++i) {
        if (log_buffer->logs[(i + log_buffer->start_index) % MAX_LOGS]) {
            mvwprintw(
                logs_window->content,
                i, 0,
                "%.*s",
                logs_window->content_w, 
                log_buffer->logs[(i + log_buffer->start_index) % MAX_LOGS]
            );
        }
    }

    // Store position of file pointer, which is pointing to end of the last log printed (EOF). 
    fgetpos(debug_log, &log_buffer->file_pos);
}
