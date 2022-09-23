/*****************************************************************/
/*!
\file   Logger.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   23 September 2022
\brief  This file contains logger used by asserts

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#pragma once

namespace Compiler_Logger
{
	enum LOG_LEVEL {
		LOG_LEVEL_ADMIN = 0, //don't use
		LOG_LEVEL_WARN = 1,
		LOG_LEVEL_ERROR = 2,
		LOG_LEVEL_DEBUG = 3
	};

	static const char* LOGS[] = { "ADMIN", "WARNING", "ERROR", "DEBUG" };

	/**
	 * \brief  Prints out assertion message.
	 *
	 * \param level			Log level
	 * \param expression	The expression being evaluated
	 * \param file			File name of where the assertion occurred
	 * \param line			Line number of where the assertion occurred
	 * \param message		Message to be printed out
	 * \param				Varadic arguments with respect to the message
	 */
	void AssertionFailureReport(LOG_LEVEL level, const char* expression, const char* file, int line, const char* message = 0, ...);
}
