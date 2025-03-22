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

    size_t num_vfx_tests = sizeof(vfx_tests) / sizeof(vfx_tests[0]);

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
    
    wattron(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
    box(test_content_window, 0, 0);
    wattroff(test_content_window, COLOR_PAIR(COLOR_PAIR_RED));
    mvwprintw(test_content_window, 1, TEST_CONTENT_WINDOW_W - strlen("play vfx: _") - 1, "play vfx: _");
    wrefresh(test_content_window);
    
    size_t test_index = 0;    
    bool running = true;

    while (running) {
        if (vfx_tests[test_index].test_result == PENDING) {
            sprintf(title_string, "%s - PENDING - %lu / %lu", vfx_tests[test_index].test_name, test_index + 1, num_vfx_tests);
        } else if (vfx_tests[test_index].test_result == PASSED){
            sprintf(title_string, "%s - PASSED - %lu / %lu", vfx_tests[test_index].test_name, test_index + 1, num_vfx_tests);
        } else if (vfx_tests[test_index].test_result == FAILED) {
            sprintf(title_string, "%s - FAILED - %lu / %lu", vfx_tests[test_index].test_name, test_index + 1, num_vfx_tests);
        }
        mvprintw(0, 0, "%*s", (int)sizeof(title_string), "");
        if (vfx_tests[test_index].test_result == PASSED) {
            attron(COLOR_PAIR(COLOR_PAIR_GREEN));
        } else if (vfx_tests[test_index].test_result == FAILED) {
            attron(COLOR_PAIR(COLOR_PAIR_RED));
        }
        mvprintw(0, 0, "%s", title_string);
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
            break;
            case '\e':
            running = false;
            break;
        }        
    }

    delwin(test_info_window);
    delwin(test_content_window);
    end_curses();

    size_t pending_vfx_tests[NUM_TESTS] = { 0 };
    size_t passed_vfx_tests[NUM_TESTS] = { 0 };
    size_t failed_vfx_tests[NUM_TESTS] = { 0 };

    size_t num_vfx_tests_pending = 0; 
    size_t num_vfx_tests_passed = 0; 
    size_t num_vfx_tests_failed = 0; 

    for (size_t i = 0; i < num_vfx_tests; ++i) {
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
        printf("%lu / %lu VFX tests pending\n", num_vfx_tests_pending, num_vfx_tests);
    }

    if (num_vfx_tests_passed > 0) {
        printf("Passed VFX tests:\n");
        for (size_t i = 0; i < num_vfx_tests_passed; ++i) {
            printf("%lu - %s\n", passed_vfx_tests[i] + 1, vfx_tests[passed_vfx_tests[i]].test_name);
        }
        printf("%lu / %lu VFX tests passed\n", num_vfx_tests_passed, num_vfx_tests);
    }    

    if (num_vfx_tests_failed > 0) {
        printf("Failed VFX tests:\n");
        for (size_t i = 0; i < num_vfx_tests_failed; ++i) {
            printf("%lu - %s\n", failed_vfx_tests[i] + 1, vfx_tests[failed_vfx_tests[i]].test_name);
        }
        printf("%lu / %lu VFX tests failed\n", num_vfx_tests_failed, num_vfx_tests);
    }

    return EXIT_SUCCESS;
}
