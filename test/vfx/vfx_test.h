#ifndef VFX_TEST_H
#define VFX_TEST_H
#include "vfx.h"

#include <stdint.h>

#define VFX_TEST(test) {test, #test, PENDING}


typedef void vfx_test_function(GameWindow* game_window, VFX* vfx, int8_t y_offset, int8_t x_offset);

enum TestResult {
    PENDING,
    PASSED,
    FAILED
};

typedef enum TestResult TestResult;

struct VFXTest {
    vfx_test_function* test_function;
    char* test_name;
    TestResult test_result;
};

typedef struct VFXTest VFXTest;

void run_vfx_test(VFXTest vfx_test, int8_t y_offset, int8_t x_offset);

#endif
