#include "test_draw_game_vfx.h"
#include "vfx_test.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TESTS 48


static void setup_curses(void) {
    // Initialize curses screen.
    if (initscr() == NULL) {
        fprintf(stderr, "During curses setup, initscr() failed to initialize curses screen.\n");
        exit(EXIT_FAILURE);
    }

    // Check if current terminal size is sufficient.
    int h_max = GAME_H + 4;
    int w_max = GAME_W + 2;
    if (LINES < h_max || COLS < w_max) {
        fprintf(    
            stderr, 
            "Current terminal window size (h=%i, w=%i) did not meet requirements (h=%i, w=%i).",
            LINES, COLS, h_max, w_max
        );
        exit(EXIT_FAILURE);
    }

    // Disable input echoing to screen.
    if (noecho() == ERR) {
        fprintf(stderr, "During curses setup, noecho() failed to disable input echoing.\n");
        exit(EXIT_FAILURE);
    }
    
    // Hide cursor.
    if (curs_set(0) == ERR) {
        fprintf(stderr, "During curses setup, curs_set(0) failed to set cursor to invisible mode.\n");
        exit(EXIT_FAILURE);
    }
    
    // Disable delay after reading escape key.
    if (set_escdelay(0) == ERR) {
        fprintf(stderr, "During curses setup, set_escdelay(0) failed to disable escape key delay.\n");
        exit(EXIT_FAILURE);
    }
    
    // Enable arrow key input.
    if (keypad(stdscr, true) == ERR) {
        fprintf(stderr, "During curses setup, keypad(stdscr, true) failed to enable keypad.\n");
        exit(EXIT_FAILURE);
    }
    
    // Disable non-blocking getch().
    if (nodelay(stdscr, false) == ERR) {
        fprintf(stderr, "During curses setup, nodelay(stdscr, true) failed to enable non-blocking getch().\n");
        exit(EXIT_FAILURE);
    }

    // Initial refresh of stdscr.
    if (refresh() == ERR) {
        fprintf(stderr, "During curses setup, initial refresh() failed.\n");
        exit(EXIT_FAILURE);
    } 

    // Check if terminal supports colors.
    if (!has_colors()) {
        fprintf(stderr, "During curses setup, has_colors() return false, continuing without color.\n");
        return;
    }

    // Initialize default colors.
    if (use_default_colors() == ERR) {
        fprintf(stderr, "During curses setup, use_default_colors() not supported, continuing without color.\n");
        return;
    }

    // Initialize curses colors. 
    if (start_color() == ERR) {
        fprintf(stderr, "During curses setup, start_color() failed to initialize colors, continuing without color.\n");
        return;
    }

    // Initialize non-default orange color.
    short COLOR_ORANGE = 8;
    init_color(COLOR_ORANGE, 900, 600, 0);

    // Initialize color pairs of tetronimos.
    init_pair(I, COLOR_CYAN,    -1);
    init_pair(J, COLOR_BLUE,    -1);
    init_pair(L, COLOR_ORANGE,  -1);
    init_pair(O, COLOR_YELLOW,  -1);
    init_pair(S, COLOR_GREEN,   -1);
    init_pair(T, COLOR_MAGENTA, -1);
    init_pair(Z, COLOR_RED,     -1);
}

static void cleanup(void) {
    // Show cursor.
    if (stdscr != NULL) {
        if (curs_set(2) == ERR) {
            fprintf(stderr, "During cleanup, curs_set(2) failed to set cursor to visible mode.\n");
        }
    }

    // Exit curses.
    if (stdscr != NULL) {
        if (endwin() == ERR) {
            fprintf(stderr, "During cleanup, endwin() failed to restore normal terminal mode.\n");
        }
    }
}

int main(void) {
    VFXTest vfx_tests[NUM_TESTS] = {
        VFX_TEST(test_vfx_lock_i_piece),
        VFX_TEST(test_vfx_lock_j_piece),
        VFX_TEST(test_vfx_lock_l_piece),
        VFX_TEST(test_vfx_lock_o_piece),
        VFX_TEST(test_vfx_lock_s_piece),
        VFX_TEST(test_vfx_lock_t_piece),
        VFX_TEST(test_vfx_lock_z_piece),
        VFX_TEST(test_vfx_line_clear_single),
        VFX_TEST(test_vfx_line_clear_double),
        VFX_TEST(test_vfx_line_clear_triple),
        VFX_TEST(test_vfx_line_clear_tetris),
        VFX_TEST(test_vfx_line_clear_t_spin),
        VFX_TEST(test_vfx_line_clear_all_clear),
        VFX_TEST(test_vfx_hold_i_piece),
        VFX_TEST(test_vfx_hold_j_piece),
        VFX_TEST(test_vfx_hold_l_piece),
        VFX_TEST(test_vfx_hold_o_piece),
        VFX_TEST(test_vfx_hold_s_piece),
        VFX_TEST(test_vfx_hold_t_piece),
        VFX_TEST(test_vfx_hold_z_piece),
        VFX_TEST(test_vfx_next_i_piece),
        VFX_TEST(test_vfx_next_j_piece),
        VFX_TEST(test_vfx_next_l_piece),
        VFX_TEST(test_vfx_next_o_piece),
        VFX_TEST(test_vfx_next_s_piece),
        VFX_TEST(test_vfx_next_t_piece),
        VFX_TEST(test_vfx_next_z_piece),
        VFX_TEST(test_vfx_action_single),
        VFX_TEST(test_vfx_action_double),
        VFX_TEST(test_vfx_action_triple),
        VFX_TEST(test_vfx_action_tetris),
        VFX_TEST(test_vfx_action_t_spin),
        VFX_TEST(test_vfx_action_t_spin_single),
        VFX_TEST(test_vfx_action_t_spin_double),
        VFX_TEST(test_vfx_action_t_spin_triple),
        VFX_TEST(test_vfx_action_t_spin_mini),
        VFX_TEST(test_vfx_action_t_spin_mini_single),
        VFX_TEST(test_vfx_action_t_spin_mini_double),
        VFX_TEST(test_vfx_action_all_clear_single),
        VFX_TEST(test_vfx_action_all_clear_double),
        VFX_TEST(test_vfx_action_all_clear_triple),
        VFX_TEST(test_vfx_action_all_clear_tetris),
        VFX_TEST(test_vfx_combo),
        VFX_TEST(test_vfx_b2b_combo),
        VFX_TEST(test_vfx_points),
        VFX_TEST(test_vfx_level_up),
        VFX_TEST(test_vfx_stats_lines),
        VFX_TEST(test_vfx_stats_level),
    };

    // Register cleanup function on exit.
    if (atexit(cleanup) != 0) {
        fprintf(stderr, "Failed to register cleanup function.\n");
        return EXIT_FAILURE;
    }

    setup_curses();

    const int8_t TEST_INFO_WINDOW_H = GAME_H + 4;
    const int8_t TEST_INFO_WINDOW_W = GAME_W + 2;
    const int8_t TEST_INFO_WINDOW_Y = 0;
    const int8_t TEST_INFO_WINDOW_X = 0;

    const int8_t TEST_CONTENT_WINDOW_H = TEST_INFO_WINDOW_H - 2;
    const int8_t TEST_CONTENT_WINDOW_W = TEST_INFO_WINDOW_W;
    const int8_t TEST_CONTENT_WINDOW_Y = 1;
    const int8_t TEST_CONTENT_WINDOW_X = 0;

    // Calculate offset of test window so UI is centered in terminal.
    int y_offset = LINES / 2 - TEST_INFO_WINDOW_H / 2;
    int x_offset = COLS / 2 - TEST_INFO_WINDOW_W / 2;

    WINDOW* test_info_window = newwin(
        TEST_INFO_WINDOW_H, 
        TEST_INFO_WINDOW_W, 
        TEST_INFO_WINDOW_Y + y_offset, 
        TEST_INFO_WINDOW_X + x_offset
    );
    WINDOW* test_content_window = newwin(
        TEST_CONTENT_WINDOW_H, 
        TEST_CONTENT_WINDOW_W, 
        TEST_CONTENT_WINDOW_Y + y_offset, 
        TEST_CONTENT_WINDOW_X + x_offset
    );

    const int8_t game_window_y_offset = TEST_CONTENT_WINDOW_Y + y_offset + 1;
    const int8_t game_window_x_offset = TEST_CONTENT_WINDOW_X + x_offset + 1;

    const char* help_string = "< prev | pass: z | fail: x | end: esc | next >";
    mvwprintw(test_info_window, TEST_INFO_WINDOW_H - 1, TEST_INFO_WINDOW_W / 2 - strlen(help_string) / 2, "%s", help_string);
    wrefresh(test_info_window);
    
    wattron(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
    box(test_content_window, 0, 0);
    wattroff(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
    mvwprintw(test_content_window, 1, TEST_CONTENT_WINDOW_W - strlen("play vfx: _") - 1, "play vfx: _");
    wrefresh(test_content_window);
    
    char header_string[64];
    size_t test_index = 0;    
    bool running = true;

    while (running) {
        if (vfx_tests[test_index].test_result == PENDING) {
            sprintf(header_string, "%s - PENDING - %lu / %u", vfx_tests[test_index].test_name, test_index + 1, NUM_TESTS);
        } else if (vfx_tests[test_index].test_result == PASSED){
            sprintf(header_string, "%s - PASSED - %lu / %u", vfx_tests[test_index].test_name, test_index + 1, NUM_TESTS);
        } else if (vfx_tests[test_index].test_result == FAILED) {
            sprintf(header_string, "%s - FAILED - %lu / %u", vfx_tests[test_index].test_name, test_index + 1, NUM_TESTS);
        }
        mvprintw(y_offset, x_offset, "%*s", (int)sizeof(header_string), "");
        if (vfx_tests[test_index].test_result == PASSED) {
            attron(COLOR_PAIR(COLOR_PAIR_GREEN));
        } else if (vfx_tests[test_index].test_result == FAILED) {
            attron(COLOR_PAIR(COLOR_PAIR_RED));
        }
        mvprintw(y_offset, x_offset, "%s", header_string);
        if (vfx_tests[test_index].test_result == PASSED) {
            attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
        } else if (vfx_tests[test_index].test_result == FAILED) {
            attroff(COLOR_PAIR(COLOR_PAIR_RED));
        }
        refresh();
        
        int input = getch();
        switch (input) {
            case KEY_LEFT:
            test_index = (test_index > 0) ? test_index - 1 : NUM_TESTS - 1;
            wattron(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
            box(test_content_window, 0, 0);
            wattroff(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
            wrefresh(test_content_window);
            break;
            case KEY_RIGHT:
            test_index = (test_index + 1) % NUM_TESTS;
            wattron(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
            box(test_content_window, 0, 0);
            wattroff(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
            wrefresh(test_content_window);
            break;
            case 'z':
            vfx_tests[test_index].test_result = PASSED;
            break;
            case 'x':
            vfx_tests[test_index].test_result = FAILED;
            break;
            case ' ':
            run_vfx_test(vfx_tests[test_index], game_window_y_offset, game_window_x_offset);
            flushinp();
            break;
            case '\e':
            running = false;
            break;
        }        
    }

    delwin(test_info_window);
    delwin(test_content_window);
    cleanup();

    size_t pending_vfx_tests[NUM_TESTS] = { 0 };
    size_t passed_vfx_tests[NUM_TESTS] = { 0 };
    size_t failed_vfx_tests[NUM_TESTS] = { 0 };

    size_t num_vfx_tests_pending = 0; 
    size_t num_vfx_tests_passed = 0; 
    size_t num_vfx_tests_failed = 0; 

    for (size_t i = 0; i < NUM_TESTS; ++i) {
        if (vfx_tests[i].test_result == PENDING) {
            pending_vfx_tests[num_vfx_tests_pending++] = i;
        } else if (vfx_tests[i].test_result == PASSED) {
            passed_vfx_tests[num_vfx_tests_passed++] = i;
        } else if (vfx_tests[i].test_result == FAILED) {
            failed_vfx_tests[num_vfx_tests_failed++] = i;
        }
    }

    if (num_vfx_tests_pending > 0) {
        printf("Pending VFX tests:\n");
        for (size_t i = 0; i < num_vfx_tests_pending; ++i) {
            printf("%lu - %s\n", pending_vfx_tests[i] + 1, vfx_tests[pending_vfx_tests[i]].test_name);
        }   
        printf("%lu / %u VFX tests pending\n", num_vfx_tests_pending, NUM_TESTS);
    }

    if (num_vfx_tests_passed > 0) {
        printf("Passed VFX tests:\n");
        for (size_t i = 0; i < num_vfx_tests_passed; ++i) {
            printf("%lu - %s\n", passed_vfx_tests[i] + 1, vfx_tests[passed_vfx_tests[i]].test_name);
        }
        printf("%lu / %u VFX tests passed\n", num_vfx_tests_passed, NUM_TESTS);
    }    

    if (num_vfx_tests_failed > 0) {
        printf("Failed VFX tests:\n");
        for (size_t i = 0; i < num_vfx_tests_failed; ++i) {
            printf("%lu - %s\n", failed_vfx_tests[i] + 1, vfx_tests[failed_vfx_tests[i]].test_name);
        }
        printf("%lu / %u VFX tests failed\n", num_vfx_tests_failed, NUM_TESTS);
    }

    return EXIT_SUCCESS;
}
