#ifndef LOGGER_H
#define LOGGER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

// Max number of logs in stored LogBuffer.
#define MAX_LOGS 18

// The max length of each log stored in LogBuffer. 
#define LOG_SIZE 100

/**
 ** @brief Converts a macro to a string.
 **/
#define MACRO_TO_STRING(X) TO_STRING(X)
#define TO_STRING(X) #X

/**
 ** @brief Extracts the first argument from a list of arguments.
 **/
#define ARGS_HEAD(...) ARGS_HEAD0(__VA_ARGS__, 0)
#define ARGS_HEAD0(_0, ...) _0

/**
 ** @brief Removes the first argument from a list of arguments.
 **/
#define ARGS_TAIL(...) ARGS_TAIL0(__VA_ARGS__, 0)
#define ARGS_TAIL0(_0, ...) __VA_ARGS__

/**
 ** @brief Trace prints a formatted string and its arguments to the debug log.
 **/
#define TRACE_LOG(...)                    \
TRACE_LOG_AUX(                            \
    ARGS_HEAD(__VA_ARGS__) "%.0d",        \
    ARGS_TAIL(__VA_ARGS__)                \
)

/**
 ** @brief Allows multiple arguments to be printed in the same trace.
 **/
#define TRACE_LOG_AUX(F, ...)                      \
do {                                               \
    if (debug_mode)                                \
        fprintf(                                   \
            debug_log,                             \
            "%s:%s - " F "\n",                     \
            __FILE__,                              \
            MACRO_TO_STRING(__LINE__),             \
            __VA_ARGS__                            \
        );                                         \
} while (false)


extern const char* DEBUG_LOG_FILEPATH;

extern bool debug_mode;
extern FILE* debug_log;

/**
 ** @brief LogBuffer keeps track of the most recent logs in a circular array.
 **/
struct LogBuffer {
    fpos_t file_pos;
    char logs[MAX_LOGS][LOG_SIZE];
    uint8_t start_index;
    uint8_t end_index;
    size_t num_logs;
};

typedef struct LogBuffer LogBuffer;

/**
 ** @brief Open debug log file for reading and writing.
 **
 ** @param filepath Filepath to open as string.
 ** 
 ** @return True on success, otherwise false.  
 **/
bool debug_log_open(const char* filepath);

/**
 ** @brief Initialize the LogBuffer object.
 **
 ** @return The initialized LogBuffer object.
 **/
LogBuffer log_buffer_get(void);

/**
 ** @brief Allocate memory and initialize the LogBuffer object.
 **
 ** @return A pointer to the allocated LogBuffer object.
 **/
LogBuffer* log_buffer_init(void);

/**
 ** @brief Append the specified log to @log_buffer and keep track of indicies.
 ** 
 ** @param log_buffer The LogBuffer object to be appended to. 
 ** @param log The log to be appended. 
 **/
void log_buffer_append(LogBuffer* log_buffer, const char* log);

#endif
