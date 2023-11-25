#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include <stdarg.h>

namespace Squawk
{
	// Windows terminal color keys. WINDOWS ONLY
	constexpr auto CONSOLE_COLOR_RESET = 7;
	constexpr auto CONSOLE_COLOR_YELLOW = 14;
	constexpr auto CONSOLE_COLOR_WHITE = 15;
	constexpr auto CONSOLE_COLOR_RED = 12;

	static class Log
	{

	private:

		static void SetColor(int color);
		static void ResetColor();
		static void PrintWithColor(const char* str, int color);
		static char* AddStrInfo(char* str);
		static void PrintAddInfo(char* str, int color = CONSOLE_COLOR_RESET);
		static void PrintFormatter(int color, const char* format, va_list args);

	public:

		PERCHENGINECPP_API static void Print(const char* str);
		PERCHENGINECPP_API static void Printf(const char* format, ...);
		PERCHENGINECPP_API static void Error(const char* err);
		PERCHENGINECPP_API static void Errorf(const char* format, ...);
		PERCHENGINECPP_API static void Warn(const char* warn);
		PERCHENGINECPP_API static void Warnf(const char* format, ...);

	};

}
