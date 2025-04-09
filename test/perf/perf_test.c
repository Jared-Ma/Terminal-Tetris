#include "perf_test.h"
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void run_perf_test(size_t test_num, size_t num_trials, PerfTest perf_test) {
    printf("Running performance test %lu - %s (num_trials=%lu)\n", test_num, perf_test.test_name, num_trials);    
    struct timespec start_time, end_time;
    double total_time_elapsed_us = 0;
    
    for (size_t i = 0; i < num_trials; ++i) {
        perf_test.test_function(&start_time, &end_time);
        double time_elapsed_us = diff_timespec_us(start_time, end_time);
        total_time_elapsed_us += time_elapsed_us;
        printf("Trial %lu - %lf us\n", i+1, time_elapsed_us);
    }

    double avg_time_elapsed_us = total_time_elapsed_us / num_trials;
    printf("Test %lu average time: %lf us\n", test_num, avg_time_elapsed_us);
}
