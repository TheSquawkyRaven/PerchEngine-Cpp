#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stacktrace>
#include <iostream>
#include <windows.h>



void Log::SetColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Log::ResetColor()
{
    SetColor(CONSOLE_COLOR_RESET);
}

void Log::PrintWithColor(const char* str, int color)
{
    SetColor(color);
    // This is the only print function call in this class
    std::cout << str << std::endl;
    ResetColor();
}

char* Log::FormatPrintStr(char* str)
{
    const char* format = "String: %s";
    size_t size = std::strlen(str) + std::strlen(format);

    char* buffer = (char*)realloc(str, size);
    if (buffer == NULL)
    {
        PrintWithColor("ERROR: Memory reallocation failed!", CONSOLE_COLOR_RED);
        free(str);
        return NULL;
    }

    size_t neededSize = sprintf_s(buffer, size, format, str);

    return buffer;
}

void Log::FormatPrintResult(char* str, int color)
{
    char* strResult = FormatPrintStr(str);
    // str is realloc-ed

    if (strResult == NULL)
    {
        return;
    }

    PrintWithColor(strResult, color);
    free(strResult);
}

void Log::FPrint(int color, const char* format, va_list args)
{
    // Create a buffer with initial size of 256
    size_t size = 256;
    char* buffer = (char*)malloc(size * sizeof(char));
    if (buffer == NULL)
    {
        PrintWithColor("ERROR: Memory allocation failed!", CONSOLE_COLOR_RED);
        return;
    }

    size_t neededSize = vsnprintf(buffer, size, format, args);

    if (neededSize > size)
    {
        size = neededSize + 1;
        char* newBuffer = (char*)realloc(buffer, size);
        if (newBuffer == NULL)
        {
            PrintWithColor("ERROR: Memory reallocation failed!", CONSOLE_COLOR_RED);
            free(buffer);
            return;
        }
        buffer = newBuffer;

        vsnprintf(buffer, size, format, args);
    }

    FormatPrintResult(buffer, color);
}

void Log::Print(const char* str)
{
    FormatPrintResult((char*)str, CONSOLE_COLOR_WHITE);
}

void Log::Printf(const char* format, ...)
{
    // Read args in the ellipsis ... parameter
    va_list args;
    va_start(args, format);
    FPrint(CONSOLE_COLOR_WHITE, format, args);
    va_end(args);
}

void Log::Error(const char* err)
{
    FormatPrintResult((char*)err, CONSOLE_COLOR_RED);
}

void Log::Errorf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    FPrint(CONSOLE_COLOR_RED, format, args);
    va_end(args);
}

void Log::Warn(const char* warn)
{
    FormatPrintResult((char*)warn, CONSOLE_COLOR_YELLOW);
}

void Log::Warnf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    FPrint(CONSOLE_COLOR_YELLOW, format, args);
    va_end(args);
}
