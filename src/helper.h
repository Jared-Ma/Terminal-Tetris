#ifndef HELPER_H
#define HELPER_H
#include <time.h>
#include <stdint.h>


double diff_timespec_ns(struct timespec start_time, struct timespec end_time);

double diff_timespec_s(struct timespec start_time, struct timespec end_time);

void sleep_ns(uint64_t nanoseconds);

#endif