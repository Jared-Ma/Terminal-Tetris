#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include <stdbool.h>
#include <stdlib.h>

/** @file
 ** @brief Unit test definitions and the function to run them.
 **/

// Macro to construct UnitTest object.
#define UNIT_TEST(test) {test, #test}


// The unit test case function.
typedef bool unit_test_function(void);

/**
 ** @brief UnitTest contains the unit test case to be run, and its name. 
 **/
struct UnitTest {
    unit_test_function* test_function;
    const char* test_name;
};

typedef struct UnitTest UnitTest; 

/**
 ** @brief Run the specified unit test.
 ** 
 ** @param test_num The number of the test being run.
 ** @param unit_test The UnitTest object containing the test case to be run.
 **/
bool run_unit_test(size_t test_num, UnitTest unit_test);

#endif
