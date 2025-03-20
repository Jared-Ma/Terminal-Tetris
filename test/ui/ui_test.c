#include "ui_test.h"

#include <stdint.h>


void run_ui_test(UITest ui_test, int8_t y_offset, int8_t x_offset) {
    ui_test.test_function(y_offset, x_offset);
}
