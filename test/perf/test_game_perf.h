#ifndef TEST_GAME_PERF_H
#define TEST_GAME_PERF_H
#include <time.h>


void test_game_state_clear_lines_perf(struct timespec* start_time, struct timespec* end_time);

void test_game_state_start_perf(struct timespec* start_time, struct timespec* end_time);

void test_game_state_spawn_curr_piece_perf(struct timespec* start_time, struct timespec* end_time);

void test_game_state_move_curr_piece_perf(struct timespec* start_time, struct timespec* end_time);

void test_game_state_rotate_curr_piece_srs(struct timespec* start_time, struct timespec* end_time);

#endif
