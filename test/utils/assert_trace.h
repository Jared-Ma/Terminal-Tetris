#ifndef TRACE_ASSERT_H
#define TRACE_ASSERT_H
#include <stdbool.h>
#include <stdio.h>

#define ASSERT(condition)                                  \
    if (!(condition)) {                                    \
        printf(                                            \
            "%s:%d: %s: Assertion (%s) failed.\n",         \
            __FILE__,                                      \
            __LINE__,                                      \
            __func__,                                      \
            #condition                                     \
        );                                                 \
        return false;                                      \
    }                                                      \

#endif
