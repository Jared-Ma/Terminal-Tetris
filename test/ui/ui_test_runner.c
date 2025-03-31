#include "test_draw_game_ui.h"
#include "ui_test.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 51


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
    
    // disable non-blocking getch()
    if (nodelay(stdscr, false) == ERR) {
        fprintf(stderr, "During curses setup, nodelay(stdscr, false) failed to disable non-blocking getch().\n");
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
}

int main(void) {
    // register cleanup function on exit
    if (atexit(cleanup) != 0) {
        fprintf(stderr, "Failed to register cleanup function.\n");
        return EXIT_FAILURE;
    }

    setup_curses();

    UITest ui_tests[NUM_TESTS] = {
        UI_TEST(test_draw_hold_window),
        UI_TEST(test_draw_board_window),
        UI_TEST(test_draw_next_window),
        UI_TEST(test_draw_stats_window),
        UI_TEST(test_draw_help_window),
        UI_TEST(test_draw_main_menu_window),
        UI_TEST(test_draw_pause_window),
        UI_TEST(test_draw_game_over_window),
        UI_TEST(test_draw_board_stack),
        UI_TEST(test_draw_buffer_zone_line),
        UI_TEST(test_draw_curr_piece_i_piece),
        UI_TEST(test_draw_curr_piece_j_piece),
        UI_TEST(test_draw_curr_piece_l_piece),
        UI_TEST(test_draw_curr_piece_o_piece),
        UI_TEST(test_draw_curr_piece_s_piece),
        UI_TEST(test_draw_curr_piece_t_piece),
        UI_TEST(test_draw_curr_piece_z_piece),
        UI_TEST(test_draw_curr_piece_lock_delay_dim),
        UI_TEST(test_draw_curr_piece_lock_delay_standout),
        UI_TEST(test_draw_ghost_piece_i_piece),
        UI_TEST(test_draw_ghost_piece_j_piece),
        UI_TEST(test_draw_ghost_piece_l_piece),
        UI_TEST(test_draw_ghost_piece_o_piece),
        UI_TEST(test_draw_ghost_piece_s_piece),
        UI_TEST(test_draw_ghost_piece_t_piece),
        UI_TEST(test_draw_ghost_piece_z_piece),
        UI_TEST(test_draw_score),
        UI_TEST(test_draw_board_state),
        UI_TEST(test_draw_hold_piece_i_piece),
        UI_TEST(test_draw_hold_piece_j_piece),
        UI_TEST(test_draw_hold_piece_l_piece),
        UI_TEST(test_draw_hold_piece_o_piece),
        UI_TEST(test_draw_hold_piece_s_piece),
        UI_TEST(test_draw_hold_piece_t_piece),
        UI_TEST(test_draw_hold_piece_z_piece),
        UI_TEST(test_draw_hold_piece_i_piece_blocked),
        UI_TEST(test_draw_hold_piece_j_piece_blocked),
        UI_TEST(test_draw_hold_piece_l_piece_blocked),
        UI_TEST(test_draw_hold_piece_o_piece_blocked),
        UI_TEST(test_draw_hold_piece_s_piece_blocked),
        UI_TEST(test_draw_hold_piece_t_piece_blocked),
        UI_TEST(test_draw_hold_piece_z_piece_blocked),
        UI_TEST(test_draw_next_piece_i_piece),
        UI_TEST(test_draw_next_piece_j_piece),
        UI_TEST(test_draw_next_piece_l_piece),
        UI_TEST(test_draw_next_piece_o_piece),
        UI_TEST(test_draw_next_piece_s_piece),
        UI_TEST(test_draw_next_piece_t_piece),
        UI_TEST(test_draw_next_piece_z_piece),
        UI_TEST(test_draw_stats),
        UI_TEST(test_draw_pause_stats),
    };

    const int8_t TEST_INFO_WINDOW_H = GAME_H + 4;
    const int8_t TEST_INFO_WINDOW_W = GAME_W + 2;
    const int8_t TEST_INFO_WINDOW_Y = 0;
    const int8_t TEST_INFO_WINDOW_X = 0;

    const int8_t TEST_CONTENT_WINDOW_H = TEST_INFO_WINDOW_H - 2;
    const int8_t TEST_CONTENT_WINDOW_W = TEST_INFO_WINDOW_W;
    const int8_t TEST_CONTENT_WINDOW_Y = 1;
    const int8_t TEST_CONTENT_WINDOW_X = 0;

    WINDOW* test_info_window = newwin(
        TEST_INFO_WINDOW_H, TEST_INFO_WINDOW_W, 
        TEST_INFO_WINDOW_Y, TEST_INFO_WINDOW_X
    );

    WINDOW* test_content_window = newwin(
        TEST_CONTENT_WINDOW_H, TEST_CONTENT_WINDOW_W, 
        TEST_CONTENT_WINDOW_Y, TEST_CONTENT_WINDOW_X
    );

    const int8_t game_window_y_offset = TEST_CONTENT_WINDOW_Y + 1;
    const int8_t game_window_x_offset = TEST_CONTENT_WINDOW_X + 1;

    const char* controls_string = "< prev | pass: z | fail: x | end: esc | next >";
    mvwprintw(test_info_window, TEST_INFO_WINDOW_H - 1, TEST_INFO_WINDOW_W / 2 - strlen(controls_string) / 2, "%s", controls_string);
    wrefresh(test_info_window);
    
    char title_string[64];
    size_t test_index = 0;
    bool running = true;
    
    while (running) {
        if (ui_tests[test_index].test_result == PENDING) {
            sprintf(title_string, "%s - PENDING - %lu / %u", ui_tests[test_index].test_name, test_index + 1, NUM_TESTS);
        } else if (ui_tests[test_index].test_result == PASSED){
            sprintf(title_string, "%s - PASSED - %lu / %u", ui_tests[test_index].test_name, test_index + 1, NUM_TESTS);
        } else if (ui_tests[test_index].test_result == FAILED) {
            sprintf(title_string, "%s - FAILED - %lu / %u", ui_tests[test_index].test_name, test_index + 1, NUM_TESTS);
        }
        mvprintw(0, 0, "%*s", (int)sizeof(title_string), "");
        if (ui_tests[test_index].test_result == PASSED) {
            attron(COLOR_PAIR(COLOR_PAIR_GREEN));
        } else if (ui_tests[test_index].test_result == FAILED) {
            attron(COLOR_PAIR(COLOR_PAIR_RED));
        }
        mvprintw(0, 0, "%s", title_string);
        if (ui_tests[test_index].test_result == PASSED) {
            attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
        } else if (ui_tests[test_index].test_result == FAILED) {
            attroff(COLOR_PAIR(COLOR_PAIR_RED));
        }
        refresh();

        werase(test_content_window);
        wattron(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
        box(test_content_window, 0, 0);
        wattroff(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
        wrefresh(test_content_window);
        
        run_ui_test(ui_tests[test_index], game_window_y_offset, game_window_x_offset);

        int input = getch();
        switch (input) {
        case KEY_LEFT:
            test_index = (test_index > 0) ? test_index - 1 : NUM_TESTS - 1;
            break;
        case KEY_RIGHT:
            test_index = (test_index + 1) % NUM_TESTS;
            break;
        case 'z':
            ui_tests[test_index].test_result = PASSED;
            break;
        case 'x':
            ui_tests[test_index].test_result = FAILED;
            break;
        case '\e':
            running = false;
            break;
        }
    }

    delwin(test_info_window);
    delwin(test_content_window);
    cleanup();

    size_t pending_ui_tests[NUM_TESTS] = { 0 };
    size_t passed_ui_tests[NUM_TESTS] = { 0 };
    size_t failed_ui_tests[NUM_TESTS] = { 0 };

    size_t num_ui_tests_pending = 0; 
    size_t num_ui_tests_passed = 0; 
    size_t num_ui_tests_failed = 0; 

    for (size_t i = 0; i < NUM_TESTS; ++i) {
        if (ui_tests[i].test_result == PENDING) {
            pending_ui_tests[num_ui_tests_pending++] = i;
        } else if (ui_tests[i].test_result == PASSED) {
            passed_ui_tests[num_ui_tests_passed++] = i;
        } else if (ui_tests[i].test_result == FAILED) {
            failed_ui_tests[num_ui_tests_failed++] = i;
        }
    }

    if (num_ui_tests_pending > 0) {
        printf("Pending UI tests:\n");
        for (size_t i = 0; i < num_ui_tests_pending; ++i) {
            printf("%lu - %s\n", pending_ui_tests[i] + 1, ui_tests[pending_ui_tests[i]].test_name);
        }   
        printf("%lu / %u UI tests pending\n", num_ui_tests_pending, NUM_TESTS);
    }

    if (num_ui_tests_passed > 0) {
        printf("Passed UI tests:\n");
        for (size_t i = 0; i < num_ui_tests_passed; ++i) {
            printf("%lu - %s\n", passed_ui_tests[i] + 1, ui_tests[passed_ui_tests[i]].test_name);
        }
        printf("%lu / %u UI tests passed\n", num_ui_tests_passed, NUM_TESTS);
    }    

    if (num_ui_tests_failed > 0) {
        printf("Failed UI tests:\n");
        for (size_t i = 0; i < num_ui_tests_failed; ++i) {
            printf("%lu - %s\n", failed_ui_tests[i] + 1, ui_tests[failed_ui_tests[i]].test_name);
        }
        printf("%lu / %u UI tests failed\n", num_ui_tests_failed, NUM_TESTS);
    }

    return EXIT_SUCCESS;
}
