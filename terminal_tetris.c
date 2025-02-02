#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


int main(int argc, char* argv[argc+1]) {
    initscr(); // Initialize curses screen
    keypad(stdscr, TRUE); 
    noecho();  // Don't echo input to screen
    refresh();

    int hold_window_h = 6;
    int hold_window_w = 14;
    int hold_window_y = 0;
    int hold_window_x = 0;
    WINDOW* hold_window = newwin(hold_window_h, hold_window_w, hold_window_y, hold_window_x);
    box(hold_window, 0, 0);
    mvwprintw(hold_window, 0, 1, "HOLD");
    mvwprintw(hold_window, 2, 5, "[][]");
    mvwprintw(hold_window, 3, 5, "[][]");
    wrefresh(hold_window);

    int stats_window_h = 16;
    int stats_window_w = 14;
    int stats_window_y = hold_window_h;
    int stats_window_x = 0;
    WINDOW* stats_window = newwin(stats_window_h, stats_window_w, stats_window_y, stats_window_x);
    box(stats_window, 0, 0);
    mvwprintw(stats_window, 0, 1, "STATS");
    mvwprintw(stats_window, 2, 1, "time:");
    mvwprintw(stats_window, 4, 1, "score:");
    mvwprintw(stats_window, 6, 1, "lines:");
    mvwprintw(stats_window, 8, 1, "level:");
    mvwprintw(stats_window, 10, 1, "combo:");
    mvwprintw(stats_window, 12, 1, "fps:");
    wrefresh(stats_window);

    int play_window_h = 22;
    int play_window_w = 10 * 2 + 2;
    int play_window_y = 0;
    int play_window_x = hold_window_w;
    WINDOW* play_window = newwin(play_window_h, play_window_w, play_window_y, play_window_x);
    box(play_window, 0, 0);
    for (size_t i = 1; i <= 20; ++i) {
        mvwprintw(play_window, i, 1, "[][][][][][][][][][]");
    }
    wrefresh(play_window);

    int next_window_h = 6;
    int next_window_w = 14;
    int next_window_y = 0;
    int next_window_x = play_window_x + play_window_w;
    WINDOW* next_window = newwin(next_window_h, next_window_w, next_window_y, next_window_x);
    box(next_window, 0, 0);
    mvwprintw(next_window, 0, 1, "NEXT");
    mvwprintw(next_window, 2, 5, "[][]");
    mvwprintw(next_window, 3, 5, "[][]");
    wrefresh(next_window);

    int controls_window_h = 16;
    int controls_window_w = 14;
    int controls_window_y = next_window_h;
    int controls_window_x = next_window_x;
    WINDOW* controls_window = newwin(controls_window_h, controls_window_w, controls_window_y, controls_window_x);
    box(controls_window, 0, 0);
    mvwprintw(controls_window, 0, 1, "CONTROLS");
    mvwprintw(controls_window, 2, 1, "move:    < >");
    mvwprintw(controls_window, 4, 1, "rotate:  z x");
    mvwprintw(controls_window, 6, 1, "hold:  shift");
    mvwprintw(controls_window, 8, 1, "soft drop: v");
    mvwprintw(controls_window, 10, 1, "hard drop: _");
    mvwprintw(controls_window, 12, 1, "pause:   esc");
    wrefresh(controls_window);
    
    getch();
    delwin(play_window);
    endwin();

    return EXIT_SUCCESS;
}
