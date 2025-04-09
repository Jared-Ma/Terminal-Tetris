#ifndef PERF_TEST_H
#define PERF_TEST_H
#include <stdlib.h>

/** @file
 ** @brief Performance test definitions and the function to run them.
 **/

// Macro to construct PerfTest object. 
#define PERF_TEST(test) {test, #test}


// The performance test case function.
typedef void perf_test_function(struct timespec* start_time, struct timespec* end_time);

/**
 ** @brief PerfTest contains the performance test case to be run and its name.
 **/
struct PerfTest {
    perf_test_function* test_function;
    const char* test_name;
};

typedef struct PerfTest PerfTest;

/**
 ** @brief Run the performance test for the specified number of trials 
 ** @num_trials, output the time of each trial, and the average time overall
 ** in microseconds. 
 ** 
 ** @param test_num The number of the test being run.
 ** @param num_trials The number of times the test will be run.
 ** @param perf_test The PerfTest object containing the test case to be run.
 **/
void run_perf_test(size_t test_num, size_t num_trials, PerfTest perf_test);

#endif
