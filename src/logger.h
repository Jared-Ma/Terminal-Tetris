#ifndef LOGGER_H
#define LOGGER_H
#include <stdbool.h>
#include <stdio.h>


extern FILE* debug_log;

bool debug_log_open(const char* filename);

#endif
