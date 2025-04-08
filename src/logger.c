#include "logger.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Filepath to debug log to be read and written. 
const char* DEBUG_LOG_FILEPATH =  "./logs/debug.txt";

bool debug_mode = false;
FILE* debug_log = NULL;

bool debug_log_open(const char* filepath) {
    debug_log = fopen(filepath, "w+");
    if (!debug_log) {
        fprintf(stderr, "Failed to open file (%s) for writing.", filepath);
        return false;
    }
    return true;
}

LogBuffer log_buffer_get(void) {
    LogBuffer log_buffer = {
        .file_pos = { 0 },
        .logs = {{ 0 }},
        .start_index = 0,
        .end_index = 0,
        .num_logs = 0
    };
    return log_buffer;
}

LogBuffer* log_buffer_init(void) {
    LogBuffer* log_buffer = malloc(sizeof(LogBuffer));
    *log_buffer = log_buffer_get();
    return log_buffer;
}

void log_buffer_destroy(LogBuffer* log_buffer) {
    if (!log_buffer) {
        return;
    }
    *log_buffer = (LogBuffer){ 0 };
    free(log_buffer);
}

void log_buffer_append(LogBuffer* log_buffer, const char* log) {
    if (!log_buffer || !log) {
        return;
    }

    // Update start_index if buffer is full and end_index has reached start_index.
    if (log_buffer->num_logs >= MAX_LOGS && log_buffer->end_index == log_buffer->start_index) {
        log_buffer->start_index = (log_buffer->start_index + 1) % MAX_LOGS;
    } 

    // Prepend log number to log before appending. 
    snprintf(log_buffer->logs[log_buffer->end_index], LOG_SIZE, "%lu - ", ++log_buffer->num_logs);
    strncat(log_buffer->logs[log_buffer->end_index], log, LOG_SIZE - strlen(log_buffer->logs[log_buffer->end_index]));
    log_buffer->end_index = (log_buffer->end_index + 1) % MAX_LOGS;
}
