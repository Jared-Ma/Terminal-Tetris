#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include <stdbool.h>
#include <stdlib.h>

#define UNIT_TEST(test) {test, #test}


typedef bool unit_test_function(void);

struct UnitTest {
    unit_test_function* test_function;
    char* test_name;
};

typedef struct UnitTest UnitTest; 

bool run_unit_test(size_t test_num, UnitTest unit_test);

#endif
