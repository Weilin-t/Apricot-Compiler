/*****************************************************************/
/*!
\file   Asserts.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   23 September 2022
\brief  This file contains asserts behaviour

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#pragma once

#include <Windows.h>
#include "Logger.h"

// Disable assertions by commenting out the below line.
#define ML_ASSERTIONS_ENABLED

#ifdef ML_ASSERTIONS_ENABLED

#if _MSC_VER
#include <intrin.h>
#define DebugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

#define ML_ASSERT(expr, ...)                                                                                            \
    {                                                                                                                   \
        if (expr)                                                                                                      \
        {                                                                                                               \
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);                                               \
            Compiler_Logger::AssertionFailureReport(Compiler_Logger::LOG_LEVEL_ERROR, #expr, __FILE__, __LINE__,__VA_ARGS__ );  \
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);                                               \
            DebugBreak();                                                                                               \
        }                                                                                                               \
        else                                                                                                            \
        {                                                                                                               \
        }                                                                                                               \
    }

#define ML_WARN(expr, ...)                                                                                              \
    {                                                                                                                   \
        if (expr)                                                                                                      \
        {                                                                                                               \
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);                                                \
            Compiler_Logger::AssertionFailureReport(Compiler_Logger::LOG_LEVEL_WARN, #expr, __FILE__, __LINE__,__VA_ARGS__ );   \
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);                                                \
        }                                                                                                               \
        else                                                                                                            \
        {                                                                                                               \
        }                                                                                                               \
    }

#define ML_DEBUG(expr, ...)                                                                                             \
    {                                                                                                                   \
        if (expr)                                                                                                      \
        {                                                                                                               \
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);                                                \
            Compiler_Logger::AssertionFailureReport(Compiler_Logger::LOG_LEVEL_DEBUG, #expr, __FILE__, __LINE__,__VA_ARGS__ );  \
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);                                                \
        }                                                                                                               \
        else                                                                                                            \
        {                                                                                                               \
        }                                                                                                               \
    }                                                                                                                   

#else
    #define ML_ASSERT(expr)               // Does nothing at all
    #define ML_WARN(expr)
    #define ML_DEBUG(expr)
#endif 

