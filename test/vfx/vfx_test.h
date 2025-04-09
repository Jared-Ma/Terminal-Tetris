#ifndef VFX_TEST_H
#define VFX_TEST_H
#include "vfx.h"

#include <stdint.h>

/** @file
 ** @brief VFX test definitions and the function to run them.
 **/

// Macro to construct VFXTest object. 
#define VFX_TEST(test) {test, #test, PENDING}


// The VFX test case function.
typedef void vfx_test_function(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

/**
 ** @brief Named constants for the possible VFX test results. 
 **/
enum TestResult {
    PENDING,
    PASSED,
    FAILED
};

typedef enum TestResult TestResult;

/**
 ** @brief VFXTest contains the VFX test case to be run, its name, and its 
 ** result. 
 **/
struct VFXTest {
    vfx_test_function* test_function;
    const char* test_name;
    TestResult test_result;
};

typedef struct VFXTest VFXTest;

/**
 ** @brief Run the specified VFX test and draw its output.
 **
 ** @param vfx_test The VFXTest object containing the test case to be run.
 ** @param y_offset Offset in the y-axis applied to the drawn output.
 ** @param x_offset Offset in the x-axis applied to the drawn output.
 **/
void run_vfx_test(VFXTest vfx_test, int8_t y_offset, int8_t x_offset);

#endif
