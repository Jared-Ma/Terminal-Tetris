#include "draw.h"
#include "game_state.h"
#include "helper.h"
#include "logger.h"
#include "piece.h"
#include "stats.h"
#include "vfx.h"

#include <ctype.h>
#include <getopt.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_MOVE_LEFT    KEY_LEFT
#define INPUT_MOVE_RIGHT   KEY_RIGHT
#define INPUT_ROTATE_LEFT  'z'
#define INPUT_ROTATE_RIGHT 'x'
#define INPUT_HOLD         'c'
#define INPUT_SOFT_DROP    KEY_DOWN
#define INPUT_HARD_DROP    ' '
#define INPUT_RESTART      'r'
#define INPUT_PAUSE        '\e'


const uint8_t TARGET_FPS = 60;
const uint32_t TARGET_FRAME_TIME_NS = 1e9 / TARGET_FPS;

enum InputState {
    PLAYING,
    MAIN_MENU,
    PAUSED,
    GAME_OVER
};

typedef enum InputState InputState;

static void restart_game(GameState* game_state, Stats* stats, VFX* vfx_list[NUM_VFX], uint8_t start_level) {
    game_state_reset(game_state);
    stats_reset(stats);
    for (size_t i = 0; i < NUM_VFX; ++i) {
        vfx_list[i]->clear_vfx(vfx_list[i]);
        vfx_disable(vfx_list[i]);
    }
    game_state_start(game_state, start_level);
}

static void run_tetris(
    GameWindow* board_window,
    GameWindow* hold_window,
    GameWindow* next_window,
    GameWindow* stats_window,
    GameWindow* controls_window,
    GameWindow* main_menu_window,
    GameWindow* pause_window,
    GameWindow* game_over_window,
    GameWindow* debug_window,
    GameState* game_state,
    Stats* stats,
    VFX* vfx_list[NUM_VFX]
) {
    srand(time(0));
    uint8_t start_level = 1;
    InputState input_state = MAIN_MENU;
    struct timespec start_time, end_time;
    uint32_t frame_time_ns;
    bool running = true;

    // initial render of game windows
    draw_board_window(board_window);
    draw_hold_window(hold_window);
    draw_next_window(next_window);
    draw_stats_window(stats_window);
    draw_controls_window(controls_window);
    draw_main_menu_window(main_menu_window, start_level);
    if (debug_mode) draw_debug_window(debug_window);
    
    // initial refresh of game windows
    game_window_refresh(board_window);
    game_window_refresh(hold_window);
    game_window_refresh(next_window);
    game_window_refresh(stats_window);
    game_window_refresh(controls_window);
    game_window_refresh(main_menu_window);
    if (debug_mode) game_window_refresh(debug_window);

    while (running) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        // Input
        int input = getch();
        if (input_state == PLAYING) {
            switch (input) {
            case INPUT_ROTATE_LEFT:
                game_state_rotate_curr_piece_srs(game_state, LEFT);
                break;
            case INPUT_ROTATE_RIGHT:
                game_state_rotate_curr_piece_srs(game_state, RIGHT);
                break;
            case INPUT_MOVE_LEFT:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y, game_state->curr_piece.x - 1);
                break;
            case INPUT_MOVE_RIGHT:
                game_state_move_curr_piece(game_state, game_state->curr_piece.y, game_state->curr_piece.x + 1);
                break;
            case INPUT_HOLD:
                game_state_hold_piece(game_state);
                break;
            case INPUT_SOFT_DROP:
                game_state_soft_drop_curr_piece(game_state);
                break;
            case INPUT_HARD_DROP:
                game_state_hard_drop_curr_piece(game_state);
                break;
            case INPUT_PAUSE:
                input_state = PAUSED;
                break;
            }
        } else if (input_state == MAIN_MENU) {
            switch (input) {
            case INPUT_MOVE_LEFT:
                start_level = (start_level > 1) ? start_level - 1 : MAX_GRAVITY_LEVEL;
                break;
            case INPUT_MOVE_RIGHT:
                start_level = start_level % MAX_GRAVITY_LEVEL + 1;
                break;
            case INPUT_HARD_DROP:
                restart_game(game_state, stats, vfx_list, start_level);
                input_state = PLAYING;
                break;
            case INPUT_PAUSE: 
                running = false;
                break;
            }
        } else if (input_state == PAUSED) {
            switch (input) {
            case INPUT_HARD_DROP:
                input_state = PLAYING;
                break;
            case INPUT_RESTART:
                restart_game(game_state, stats, vfx_list, start_level);
                input_state = PLAYING;
                break;
            case INPUT_PAUSE:
                input_state = MAIN_MENU;
                break;
            }
        } else if (input_state == GAME_OVER) {
            switch (input) {
            case INPUT_RESTART:
                restart_game(game_state, stats, vfx_list, start_level);
                input_state = PLAYING;
                break;
            case INPUT_PAUSE:
                input_state = MAIN_MENU;
                break;
            }
        }
        
        // Update
        if (input_state == PLAYING) {
            if (game_state_check_curr_piece_grounded(game_state) && game_state->lock_delay_timer > 0) {
                game_state->lock_delay_timer--;
            }

            if (game_state->lock_delay_timer == 0) {
                game_state_lock_curr_piece(game_state);
                game_state_clear_lines(game_state);
                game_state_load_next_piece(game_state);
            }
            
            if (game_state->soft_drop == true) {
                game_state_apply_soft_drop_gravity(game_state);
            } else {
                game_state_apply_gravity(game_state);
            }

            if (game_state_check_collision(game_state, game_state->curr_piece)) {
                input_state = GAME_OVER;
            }

            stats_update(stats, game_state);
        }

        // Render
        if (input_state == PLAYING) {
            draw_board_window(board_window);
            draw_hold_window(hold_window);
            draw_next_window(next_window);
            draw_stats_window(stats_window);
            draw_controls_window(controls_window);

            draw_board_state(board_window, game_state);
            draw_hold_piece(hold_window, game_state);
            draw_next_piece(next_window, game_state);
            draw_stats(stats_window, game_state, stats);

            for (size_t i = 0; i < NUM_VFX; ++i) {
                if (vfx_list[i]->check_cond(vfx_list[i], game_state)) {
                    vfx_list[i]->enable_vfx(vfx_list[i], game_state);
                }
            }
            for (size_t i = 0; i < NUM_VFX; ++i) {
                draw_vfx_frame(vfx_list[i]);
                game_state_reset_vfx_conditions(game_state);
            }

            game_window_refresh(board_window);
            game_window_refresh(hold_window);
            game_window_refresh(next_window);
            game_window_refresh(stats_window);
            game_window_refresh(controls_window);
        } else if (input_state == MAIN_MENU) {
            draw_main_menu_window(main_menu_window, start_level);
            game_window_refresh(main_menu_window);
        } else if (input_state == PAUSED) {
            draw_pause_window(pause_window);
            draw_pause_stats(stats_window, stats);
            game_window_refresh(pause_window);
            game_window_refresh(stats_window);
        } else if (input_state == GAME_OVER) {
            draw_game_over_window(game_over_window);
            draw_pause_stats(stats_window, stats);
            game_window_refresh(game_over_window);
            game_window_refresh(stats_window);
        }

        if (debug_mode) {
            draw_debug_variables(debug_window, game_state, stats);
            game_window_refresh(debug_window);
        }

        clock_gettime(CLOCK_MONOTONIC, &end_time);
        frame_time_ns = diff_timespec_ns(start_time, end_time);
        if (frame_time_ns < TARGET_FRAME_TIME_NS) {
            sleep_ns(TARGET_FRAME_TIME_NS - frame_time_ns);
        }

        if (input_state == PLAYING) {
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            stats->game_time_s += diff_timespec_s(start_time, end_time);
        }

        clock_gettime(CLOCK_MONOTONIC, &end_time);
        stats->real_time_s += diff_timespec_s(start_time, end_time);
        stats->frame_count++;
    }
}

static void setup_curses(void) {
    // initialize curses screen
    if (initscr() == NULL) {
        fprintf(stderr, "During curses setup, initscr() failed to initialize curses screen.\n");
        exit(EXIT_FAILURE);
    }

    // disable input echoing to screen
    if (noecho() == ERR) {
        fprintf(stderr, "During curses setup, noecho() failed to disable input echoing.\n");
        exit(EXIT_FAILURE);
    }
    
    // hide cursor
    if (curs_set(0) == ERR) {
        fprintf(stderr, "During curses setup, curs_set(0) failed to set cursor to invisible mode.\n");
        exit(EXIT_FAILURE);
    }
    
    // disable delay after reading escape key
    if (set_escdelay(0) == ERR) {
        fprintf(stderr, "During curses setup, set_escdelay(0) failed to disable escape key delay.\n");
        exit(EXIT_FAILURE);
    }
    
    // enable arrow key input
    if (keypad(stdscr, true) == ERR) {
        fprintf(stderr, "During curses setup, keypad(stdscr, true) failed to enable keypad.\n");
        exit(EXIT_FAILURE);
    }
    
    // enable non-blocking getch()
    if (nodelay(stdscr, true) == ERR) {
        fprintf(stderr, "During curses setup, nodelay(stdscr, true) failed to enable non-blocking getch().\n");
        exit(EXIT_FAILURE);
    }

    // initial refresh of stdscr
    if (refresh() == ERR) {
        fprintf(stderr, "During curses setup, initial refresh() failed.\n");
        exit(EXIT_FAILURE);
    } 

    // check if terminal supports colors
    if (!has_colors()) {
        fprintf(stderr, "During curses setup, has_colors() return false, continuing without color.\n");
        return;
    }

    // initialize default colors
    if (use_default_colors() == ERR) {
        fprintf(stderr, "During curses setup, use_default_colors() not supported, continuing without color.\n");
        return;
    }

    // initialize curses colors 
    if (start_color() == ERR) {
        fprintf(stderr, "During curses setup, start_color() failed to initialize colors, continuing without color.\n");
        return;
    }

    // initialize non-default orange color
    short COLOR_ORANGE = 8;
    init_color(COLOR_ORANGE, 900, 600, 0);

    // initialize color pairs of tetronimos
    init_pair(I, COLOR_CYAN,    -1);
    init_pair(J, COLOR_BLUE,    -1);
    init_pair(L, COLOR_ORANGE,  -1);
    init_pair(O, COLOR_YELLOW,  -1);
    init_pair(S, COLOR_GREEN,   -1);
    init_pair(T, COLOR_MAGENTA, -1);
    init_pair(Z, COLOR_RED,     -1);
}

static void cleanup(void) {
    // show cursor
    if (stdscr != NULL) {
        if (curs_set(2) == ERR) {
            fprintf(stderr, "During cleanup, curs_set(2) failed to set cursor to visible mode.\n");
        }
    }

    // exit curses
    if (stdscr != NULL) {
        if (endwin() == ERR) {
            fprintf(stderr, "During cleanup, endwin() failed to restore normal terminal mode.\n");
        }
    }

    // close debug log file
    if (debug_log != NULL) {
        if (fclose(debug_log) == EOF) {
            fprintf(stderr, "During cleanup, failed to close debug log file.\n");
        }
    }
}

int main(int argc, char* argv[argc + 1]) {
    int option;
    while ((option = getopt(argc, argv, "d")) != -1) {
        switch (option) {
        case 'd':
            debug_mode = true;
            break;
        case '?':
            if (isprint(optopt)) {
                fprintf(stderr, "Unknown option '-%c' provided.\n", optopt);
            } else {
                fprintf(stderr, "Unknown option character provided.\n");
            }
            return EXIT_FAILURE;
        default:
            return EXIT_FAILURE;
        }
    }

    // register cleanup function on exit
    if (atexit(cleanup) != 0) {
        fprintf(stderr, "Failed to register cleanup function.\n");
        return EXIT_FAILURE;
    }

    // open debug log file
    if (debug_mode) {
        if (!debug_log_open(DEBUG_LOG_FILEPATH)) {
            fprintf(stderr, "Failed to open debug log file.\n");
            return EXIT_FAILURE;
        }
    }

    setup_curses();
    
    GameWindow* board_window = game_window_init(
        BOARD_WINDOW_H, BOARD_WINDOW_W, 
        BOARD_WINDOW_Y, BOARD_WINDOW_X
    );
    GameWindow* hold_window = game_window_init(
        HOLD_WINDOW_H, HOLD_WINDOW_W, 
        HOLD_WINDOW_Y, HOLD_WINDOW_X
    );
    GameWindow* next_window = game_window_init(
        NEXT_WINDOW_H, NEXT_WINDOW_W, 
        NEXT_WINDOW_Y, NEXT_WINDOW_X
    );
    GameWindow* stats_window = game_window_init(
        STATS_WINDOW_H, STATS_WINDOW_W, 
        STATS_WINDOW_Y, STATS_WINDOW_X
    );
    GameWindow* controls_window = game_window_init(
        CONTROLS_WINDOW_H, CONTROLS_WINDOW_W, 
        CONTROLS_WINDOW_Y, CONTROLS_WINDOW_X
    );
    GameWindow* main_menu_window = game_window_init(
        MAIN_MENU_WINDOW_H, MAIN_MENU_WINDOW_W, 
        MAIN_MENU_WINDOW_Y, MAIN_MENU_WINDOW_X
    );
    GameWindow* pause_window = game_window_init(
        PAUSE_WINDOW_H, PAUSE_WINDOW_W, 
        PAUSE_WINDOW_Y, PAUSE_WINDOW_X
    );
    GameWindow* game_over_window = game_window_init(
        GAME_OVER_WINDOW_H, GAME_OVER_WINDOW_W, 
        GAME_OVER_WINDOW_Y, GAME_OVER_WINDOW_X
    );
    GameWindow* debug_window = game_window_init(
        DEBUG_WINDOW_H, DEBUG_WINDOW_W, 
        DEBUG_WINDOW_Y, DEBUG_WINDOW_X
    );

    GameState* game_state = game_state_init();
    Stats* stats = stats_init();

    VFX* vfx_list[NUM_VFX] = { 
        vfx_init(board_window, clear_vfx_lock_piece,  vfx_check_lock_piece,  vfx_enable_lock_piece,  LOCK_PIECE_VFX_FRAMES),
        vfx_init(board_window, clear_vfx_line_clear,  vfx_check_line_clear,  vfx_enable_line_clear,  LINE_CLEAR_VFX_FRAMES),
        vfx_init(hold_window,  clear_vfx_hold_piece,  vfx_check_hold_piece,  vfx_enable_hold_piece,  HOLD_PIECE_VFX_FRAMES),
        vfx_init(next_window,  clear_vfx_next_piece,  vfx_check_next_piece,  vfx_enable_next_piece,  NEXT_PIECE_VFX_FRAMES),
        vfx_init(stats_window, clear_vfx_action,      vfx_check_action,      vfx_enable_action,      ACTION_VFX_FRAMES),
        vfx_init(stats_window, clear_vfx_combo,       vfx_check_combo,       vfx_enable_combo,       COMBO_VFX_FRAMES),
        vfx_init(stats_window, clear_vfx_b2b_combo,   vfx_check_b2b_combo,   vfx_enable_b2b_combo,   B2B_COMBO_VFX_FRAMES),
        vfx_init(stats_window, clear_vfx_points,      vfx_check_points,      vfx_enable_points,      POINTS_VFX_FRAMES),
        vfx_init(board_window, clear_vfx_level_up,    vfx_check_level_up,    vfx_enable_level_up,    LEVEL_UP_VFX_FRAMES),
        vfx_init(stats_window, clear_vfx_stats_lines, vfx_check_stats_lines, vfx_enable_stats_lines, STATS_LINES_VFX_FRAMES),
        vfx_init(stats_window, clear_vfx_stats_level, vfx_check_stats_level, vfx_enable_stats_level, STATS_LEVEL_VFX_FRAMES)
    };
    
    run_tetris(
        board_window, 
        hold_window, 
        next_window, 
        stats_window,
        controls_window,
        main_menu_window, 
        pause_window,
        game_over_window,
        debug_window,
        game_state,
        stats,
        vfx_list
    );
    
    game_window_destroy(board_window);
    game_window_destroy(hold_window);
    game_window_destroy(next_window);
    game_window_destroy(stats_window);
    game_window_destroy(controls_window);
    game_window_destroy(main_menu_window);
    game_window_destroy(pause_window);
    game_window_destroy(game_over_window);
    game_window_destroy(debug_window);
    game_state_destroy(game_state);
    stats_destroy(stats);
    for (size_t i = 0; i < NUM_VFX; ++i) {
        vfx_destroy(vfx_list[i]);
    }

    return EXIT_SUCCESS;
}
