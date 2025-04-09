#include "test_game_perf.h"
#include "perf_test.h"

#include <stdlib.h>
#include <stdint.h>

/** @file
 ** @brief Runs the specified performance tests.
 **/

// Number of tests to be run. 
#define NUM_TESTS 5


// Number of times each test is run. 
const uint8_t NUM_TRIALS = 5;

int main(void) {
    PerfTest perf_tests[NUM_TESTS] = {
        PERF_TEST(test_game_state_clear_lines_perf),
        PERF_TEST(test_game_state_start_perf),
        PERF_TEST(test_game_state_spawn_curr_piece_perf),
        PERF_TEST(test_game_state_move_curr_piece_perf),
        PERF_TEST(test_game_state_rotate_curr_piece_srs),
    };
    
    for (size_t i = 0; i < NUM_TESTS; ++i) {
        run_perf_test(i+1, NUM_TRIALS, perf_tests[i]);
    } 
    
    return EXIT_SUCCESS;
}
