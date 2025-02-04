#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>


extern FILE* debug_log;

bool debug_log_open(char *filename);

#endif
