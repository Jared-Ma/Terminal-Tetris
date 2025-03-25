#ifndef UI_TEST_H
#define UI_TEST_H
#include <stdint.h>

#define UI_TEST(test) {test, #test, PENDING}


typedef void ui_test_function(int8_t y_offset, int8_t x_offset);

enum TestResult {
    PENDING,
    PASSED,
    FAILED
};

typedef enum TestResult TestResult;

struct UITest {
    ui_test_function* test_function;
    const char* test_name;
    TestResult test_result;
};

typedef struct UITest UITest;

void run_ui_test(UITest ui_test, int8_t y_offset, int8_t x_offset);

#endif
