#include "test_draw_game_ui.h"
#include "test_draw_game_vfx.h"
#include "ui_test.h"
#include "draw.h"
#include "piece.h"
#include "logger.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 50


static void start_curses(void) {
    initscr();                // initialize curses screen
    noecho();                 // disable echo input to screen
    curs_set(0);              // hide cursor
    set_escdelay(0);          // remove delay after reading escape key
    keypad(stdscr, true);     // enable arrow key input
    nodelay(stdscr, false);   // disable non-blocking getch()
    refresh();                // initial refresh of stdscr

    // initialize color pairs of tetronimos
    start_color();
    use_default_colors();

    short COLOR_ORANGE = 8;
    init_color(COLOR_ORANGE, 900, 600, 0);

    init_pair(I, COLOR_CYAN,    -1);
    init_pair(J, COLOR_BLUE,    -1);
    init_pair(L, COLOR_ORANGE,  -1);
    init_pair(O, COLOR_YELLOW,  -1);
    init_pair(S, COLOR_GREEN,   -1);
    init_pair(T, COLOR_MAGENTA, -1);
    init_pair(Z, COLOR_RED,     -1);
}

static void end_curses(void) {
    endwin();
    curs_set(2);
}

int main(void) {
    start_curses();

    UITest ui_tests[NUM_TESTS] = {
        UI_TEST(test_draw_hold_window),
        UI_TEST(test_draw_board_window),
        UI_TEST(test_draw_next_window),
        UI_TEST(test_draw_stats_window),
        UI_TEST(test_draw_controls_window),
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

    size_t num_ui_tests = sizeof(ui_tests) / sizeof(ui_tests[0]);

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

    int8_t game_window_y_offset = TEST_CONTENT_WINDOW_Y + 1;
    int8_t game_window_x_offset = TEST_CONTENT_WINDOW_X + 1;

    char title_string[64];
    char* controls_string = "< prev | pass: z | fail: x | end: esc | next >";
    mvwprintw(test_info_window, TEST_INFO_WINDOW_H - 1, TEST_INFO_WINDOW_W / 2 - strlen(controls_string) / 2, "%s", controls_string);
    wrefresh(test_info_window);

    bool running = true;
    size_t test_index = 0;
    
    while (running) {
        if (ui_tests[test_index].test_result == PENDING) {
            sprintf(title_string, "%s - PENDING - %lu / %lu", ui_tests[test_index].test_name, test_index + 1, num_ui_tests);
        } else if (ui_tests[test_index].test_result == PASSED){
            sprintf(title_string, "%s - PASSED - %lu / %lu", ui_tests[test_index].test_name, test_index + 1, num_ui_tests);
        } else if (ui_tests[test_index].test_result == FAILED) {
            sprintf(title_string, "%s - FAILED - %lu / %lu", ui_tests[test_index].test_name, test_index + 1, num_ui_tests);
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
    end_curses();

    size_t pending_ui_tests[NUM_TESTS] = { 0 };
    size_t passed_ui_tests[NUM_TESTS] = { 0 };
    size_t failed_ui_tests[NUM_TESTS] = { 0 };

    size_t num_ui_tests_pending = 0; 
    size_t num_ui_tests_passed = 0; 
    size_t num_ui_tests_failed = 0; 

    for (size_t i = 0; i < num_ui_tests; ++i) {
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
        printf("%lu / %lu UI tests pending\n", num_ui_tests_pending, num_ui_tests);
    }

    if (num_ui_tests_passed > 0) {
        printf("Passed UI tests:\n");
        for (size_t i = 0; i < num_ui_tests_passed; ++i) {
            printf("%lu - %s\n", passed_ui_tests[i] + 1, ui_tests[passed_ui_tests[i]].test_name);
        }
        printf("%lu / %lu UI tests passed\n", num_ui_tests_passed, num_ui_tests);
    }    

    if (num_ui_tests_failed > 0) {
        printf("Failed UI tests:\n");
        for (size_t i = 0; i < num_ui_tests_failed; ++i) {
            printf("%lu - %s\n", failed_ui_tests[i] + 1, ui_tests[failed_ui_tests[i]].test_name);
        }
        printf("%lu / %lu UI tests failed\n", num_ui_tests_failed, num_ui_tests);
    }

    return EXIT_SUCCESS;
}
