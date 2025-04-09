#ifndef UI_TEST_H
#define UI_TEST_H
#include <stdint.h>

/** @file
 ** @brief UI test definitions and the function to run them.
 **/

// Macro to construct UITest object. 
#define UI_TEST(test) {test, #test, PENDING}


// The UI test case function.
typedef void ui_test_function(int8_t y_offset, int8_t x_offset);

/**
 ** @brief Named constants for the possible UI test results. 
 **/
enum TestResult {
    PENDING,
    PASSED,
    FAILED
};

typedef enum TestResult TestResult;

/**
 ** @brief UITest contains the UI test case to be run, its name, and its result. 
 **/
struct UITest {
    ui_test_function* test_function;
    const char* test_name;
    TestResult test_result;
};

typedef struct UITest UITest;

/**
 ** @brief Run the specified UI test and draw its output.
 ** 
 ** @param ui_test The UITest object containing the test case to be run.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void run_ui_test(UITest ui_test, int8_t y_offset, int8_t x_offset);

#endif
