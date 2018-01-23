#pragma once

#define BUILD_C_STYLE_INTERFACE

#define QS_SDK_API

#ifdef _WIN32
#include <stdint.h>
#endif

typedef enum LogLevel
{
    None = 0,
    Fatal = 1,
    Error = 2,
    Warning = 3,
    Info = 4,
    Debug = 5,
    Verbose = 6
}LogLevel;
