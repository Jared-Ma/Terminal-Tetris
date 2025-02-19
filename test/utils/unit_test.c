#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "unit_test.h"


bool run_unit_test(size_t test_num, UnitTest unit_test) {
    printf("Running unit test %lu - %s\n", test_num, unit_test.test_name);
    bool test_result = unit_test.test_function();
    printf("Test %lu %s\n", test_num, (test_result) ? "passed" : "failed");
    return test_result;
}
