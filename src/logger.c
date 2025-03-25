#include "logger.h"

#include <stdbool.h>
#include <stdio.h>


FILE* debug_log = NULL;

bool debug_log_open(const char* filename) {
    debug_log = fopen(filename, "w");
    if (!debug_log) {
        fprintf(stderr, "Failed to open file %s for writing.", filename);
        return false;
    }
    return true;
}
