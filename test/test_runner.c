#include <stdio.h>
#include <stdlib.h>
#include "unit_test.h"
#include "test_piece.h"

#define NUM_TESTS 7


int main(void) {
    UnitTest unit_tests[NUM_TESTS] = {
        UNIT_TEST(test_piece_get),
        UNIT_TEST(test_piece_init),
        UNIT_TEST(test_piece_move),
        UNIT_TEST(test_compute_r_index_right_rotation),
        UNIT_TEST(test_compute_r_index_left_rotation),
        UNIT_TEST(test_piece_rotate_right),
        UNIT_TEST(test_piece_rotate_left),
        UNIT_TEST(test_shape_to_char)
    };

    size_t failed_unit_tests[NUM_TESTS] = { 0 };

    size_t num_unit_tests = sizeof(unit_tests) / sizeof(unit_tests[0]);
    size_t num_unit_tests_passed = 0;
    size_t num_unit_tests_failed = 0; 

    for (size_t i = 0; i < num_unit_tests; ++i) {
        bool test_result = run_unit_test(i+1, unit_tests[i]);
        if (test_result) {
            num_unit_tests_passed++;
        } else {
            failed_unit_tests[num_unit_tests_failed++] = i;
        }
    } 
    
    printf("%lu / %lu unit tests passed\n", num_unit_tests_passed, num_unit_tests);
    
    if (num_unit_tests_failed > 0) {
        printf("\nFailed unit tests:\n");
        for (size_t i = 0; i < num_unit_tests_failed; ++i) {
            printf("%lu - %s\n", failed_unit_tests[i]+1, unit_tests[failed_unit_tests[i]].test_name);
        }
    }

    return EXIT_SUCCESS;
}
