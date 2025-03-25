#include "logger.h"

#include <stdbool.h>
#include <stdio.h>


const char* DEBUG_LOG_FILEPATH =  "./logs/debug.txt";

FILE* debug_log = NULL;

bool debug_log_open(const char* filepath) {
    debug_log = fopen(filepath, "w");
    if (!debug_log) {
        fprintf(stderr, "Failed to open file (%s) for writing.", filepath);
        return false;
    }
    return true;
}
