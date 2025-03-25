#ifndef LOGGER_H
#define LOGGER_H
#include <stdbool.h>
#include <stdio.h>


extern const char* DEBUG_LOG_FILEPATH;

extern FILE* debug_log;

bool debug_log_open(const char* filepath);

#endif
