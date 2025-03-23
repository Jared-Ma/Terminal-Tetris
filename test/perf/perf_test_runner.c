#include "test_game_perf.h"
#include "perf_test.h"

#include <stdlib.h>

#define NUM_TESTS 1


int main(void) {
    PerfTest perf_tests[NUM_TESTS] = {
        PERF_TEST(test_game_state_clear_lines_perf),
    };

    size_t num_perf_tests = sizeof(perf_tests) / sizeof(perf_tests[0]);
    size_t num_trials = 5;
    
    for (size_t i = 0; i < num_perf_tests; ++i) {
        run_perf_test(i+1, num_trials, perf_tests[i]);
    } 
    
    return EXIT_SUCCESS;
}
