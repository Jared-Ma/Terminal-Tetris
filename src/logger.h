#ifndef LOGGER_H
#define LOGGER_H
#include <stdbool.h>
#include <stdio.h>

/**
 ** @brief Converts a macro to a string
 **/
#define MACRO_TO_STRING(X) TO_STRING(X)
#define TO_STRING(X) #X

/**
 ** @brief Extracts the first argument from a list of arguments
 **/
#define ARGS_HEAD(...) ARGS_HEAD0(__VA_ARGS__, 0)
#define ARGS_HEAD0(_0, ...) _0

/**
 ** @brief Removes the first argument from a list of arguments
 **/
#define ARGS_TAIL(...) ARGS_TAIL0(__VA_ARGS__, 0)
#define ARGS_TAIL0(_0, ...) __VA_ARGS__

/**
 ** @brief Trace prints to debug log
 **/
#define TRACE_LOG(...)                    \
TRACE_LOG_AUX(                            \
    ARGS_HEAD(__VA_ARGS__) "%.0d",        \
    ARGS_TAIL(__VA_ARGS__)                \
)

/**
 ** @brief Allows multiple arguments to be printed in the same trace
 **/
#define TRACE_LOG_AUX(F, ...)                      \
do {                                               \
    if (debug_mode)                                \
        fprintf(                                   \
            debug_log,                             \
            "[%s %s] - %s:%s:%s - " F "\n",        \
            __DATE__,                              \
            __TIME__,                              \
            __FILE__,                              \
            __func__,                              \
            MACRO_TO_STRING(__LINE__),             \
            __VA_ARGS__                            \
        );                                         \
} while (false)


extern const char* DEBUG_LOG_FILEPATH;

extern bool debug_mode;
extern FILE* debug_log;

bool debug_log_open(const char* filepath);

#endif
