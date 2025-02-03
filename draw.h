#ifndef DRAW_H
#define DRAW_H
#include <ncurses.h>


WINDOW *draw_hold_window(int height, int width, int y, int x);

WINDOW *draw_stats_window(int height, int width, int y, int x);

WINDOW *draw_play_window(int height, int width, int y, int x);

WINDOW *draw_next_window(int height, int width, int y, int x);

WINDOW *draw_controls_window(int height, int width, int y, int x);

#endif
