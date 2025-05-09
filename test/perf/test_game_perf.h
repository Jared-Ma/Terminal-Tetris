#ifndef TEST_GAME_PERF_H
#define TEST_GAME_PERF_H
#include <time.h>

/** @file
 ** @brief Collection of performance test cases.
 **/


/**
 ** @brief Test game_state_clear_lines performance.
 ** 
 ** @param start_time Used to store start time of test. 
 ** @param end_time Used to store end time of test. 
 **/
void test_game_state_clear_lines_perf(struct timespec* start_time, struct timespec* end_time);

/**
 ** @brief Test game_state_start performance.
 ** 
 ** @param start_time Used to store start time of test. 
 ** @param end_time Used to store end time of test. 
 **/
void test_game_state_start_perf(struct timespec* start_time, struct timespec* end_time);

/**
 ** @brief Test game_state_spawn_curr_piece performance.
 ** 
 ** @param start_time Used to store start time of test. 
 ** @param end_time Used to store end time of test. 
 **/
void test_game_state_spawn_curr_piece_perf(struct timespec* start_time, struct timespec* end_time);

/**
 ** @brief Test game_state_move_curr_piece performance.
 ** 
 ** @param start_time Used to store start time of test. 
 ** @param end_time Used to store end time of test. 
 **/
void test_game_state_move_curr_piece_perf(struct timespec* start_time, struct timespec* end_time);

/**
 ** @brief Test game_state_rotate_curr_piece performance.
 ** 
 ** @param start_time Used to store start time of test. 
 ** @param end_time Used to store end time of test. 
 **/
void test_game_state_rotate_curr_piece_srs(struct timespec* start_time, struct timespec* end_time);

#endif
