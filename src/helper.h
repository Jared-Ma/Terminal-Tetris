#ifndef HELPER_H
#define HELPER_H
#include <time.h>
#include <stdint.h>

/** @file
 ** @brief Collection of helper functions to be used throughout program.
 **/


/**
 ** @brief Calculate the difference of two different timespec objects in 
 ** nanoseconds. 
 ** 
 ** @param start_time The start time as a timespec object.
 ** @param end_time The end time as a timespec object.
 ** 
 ** @return The difference in nanoseconds as a double.
 **/
double diff_timespec_ns(struct timespec start_time, struct timespec end_time);

/**
 ** @brief Calculate the difference of two different timespec objects in 
 ** microseconds. 
 ** 
 ** @param start_time The start time as a timespec object.
 ** @param end_time The end time as a timespec object.
 ** 
 ** @return The difference in microseconds as a double.
 **/
double diff_timespec_us(struct timespec start_time, struct timespec end_time);

/**
 ** @brief Calculate the difference of two different timespec objects in 
 ** seconds. 
 ** 
 ** @param start_time The start time as a timespec object.
 ** @param end_time The end time as a timespec object.
 ** 
 ** @return The difference in seconds as a double.
 **/
double diff_timespec_s(struct timespec start_time, struct timespec end_time);

/**
 ** @brief Suspend execution by specified amount of @nanoseconds. 
 ** 
 ** @param nanoseconds The amount of nanoseconds to sleep. 
 **/
void sleep_ns(uint64_t nanoseconds);

#endif