/*****************************************************************/
/*!
\file   Logger.cpp

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   23 September 2022
\brief  This file contains definition for logger

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#include "Logger.h"

#include <Windows.h>
#include <stdio.h>

namespace Compiler_Logger
{
	/**
	 * \brief  Prints out assertion message.
	 *
	 * \param level			Level of logger
	 * \param expression	The expression being evaluated
	 * \param file			File name of where the assertion occurred
	 * \param line			Line number of where the assertion occurred
	 * \param message		Message to be printed out
	 * \param				Varadic arguments with respect to the message
	 */
	void AssertionFailureReport(LOG_LEVEL level, const char* expression, const char* file, int line, const char* message, ...)
	{
		const int BufferSize = 1024;
		char FinalMessage[BufferSize];

		SYSTEMTIME localTime;
		GetLocalTime(&localTime);

		int offset = sprintf_s(FinalMessage, "[%02d:%02d:%02d][%s]: In %s(%d): Assertion: %s, Message: ", localTime.wHour, 
			localTime.wMinute, localTime.wSecond, LOGS[level], file, line, expression);
		if (message != NULL)
		{
			va_list args;
			va_start(args, message);
			vsnprintf_s(FinalMessage + offset, (rsize_t)BufferSize - (rsize_t)offset, _TRUNCATE, message, args);
			va_end(args);
		}
		else
		{
			strcpy_s(FinalMessage + offset, (rsize_t)BufferSize - (rsize_t)offset, "No Error Message");
		}

		printf(FinalMessage);
		printf("\n");
	}
}
