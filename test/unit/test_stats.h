#ifndef TEST_STATS_H
#define TEST_STATS_H
#include <stdbool.h>

/** @file
 ** @brief Collection of unit test cases testing stats.c / stats.h
 **/


/**
 ** @brief Test function stats_get.
 **/
bool test_stats_get(void);

/**
 ** @brief Test function stats_init.
 **/
bool test_stats_init(void);

/**
 ** @brief Test function stats_reset.
 **/
bool test_stats_reset(void);

/**
 ** @brief Test function stats_update.
 **/
bool test_stats_update(void);

#endif
