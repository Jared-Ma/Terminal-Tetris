#ifndef TRACE_ASSERT_H
#define TRACE_ASSERT_H
#include <stdbool.h>
#include <stdio.h>

#define MACRO_TO_STRING(X) TO_STRING(X)

#define TO_STRING(X) #X

#define ASSERT(condition)                                  \
    if (!(condition)) {                                    \
        printf(                                            \
            "%s:%s:%s Assertion (%s) failed.\n",           \
            __FILE__,                                      \
            __func__,                                      \
            MACRO_TO_STRING(__LINE__),                     \
            #condition                                     \
        );                                                 \
        return false;                                      \
    }                                                      \

#endif
