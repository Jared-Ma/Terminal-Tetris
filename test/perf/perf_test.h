#ifndef PERF_TEST_H
#define PERF_TEST_H
#include <stdlib.h>

#define PERF_TEST(test) {test, #test}


typedef void perf_test_function(struct timespec* start_time, struct timespec* end_time);

struct PerfTest {
    perf_test_function* test_function;
    const char* test_name;
};

typedef struct PerfTest PerfTest;

double diff_timespec_us(struct timespec start_time, struct timespec end_time);

void run_perf_test(size_t test_num, size_t num_trials, PerfTest perf_test);

#endif
