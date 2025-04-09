#include <time.h>
#include <stdint.h>


double diff_timespec_ns(struct timespec start_time, struct timespec end_time) {
    return (end_time.tv_sec - start_time.tv_sec) / 1e9 + (end_time.tv_nsec - start_time.tv_nsec);
}

double diff_timespec_us(struct timespec start_time, struct timespec end_time) {
    return (end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_nsec - start_time.tv_nsec) / 1e3;
}

double diff_timespec_s(struct timespec start_time, struct timespec end_time) {
    return (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
}

void sleep_ns(uint64_t nanoseconds) {
    struct timespec duration, remainder;
    duration.tv_sec = 0;
    duration.tv_nsec = nanoseconds;

    // Make sure the tv_nsec field is in the range [0, 1e9 - 1], such that the 
    // call to clock_nanosleep is valid.
    while (duration.tv_nsec >= 1e9) {
        duration.tv_nsec -= 1e9;
        duration.tv_sec++;
    }

    while (clock_nanosleep(CLOCK_MONOTONIC, 0, &duration, &remainder) == -1) {
        duration = remainder;
    }
}
