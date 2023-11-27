#include "pch.h"

#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stacktrace>
#include <iostream>
#include <windows.h>

using namespace Squawk;

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

char* Log::AddStrInfo(char* str)
{
    const char* format = "Squawk Log: %s";
    size_t size = std::strlen(str) + std::strlen(format);

    char* buffer = (char*)realloc(str, size);
    if (buffer == NULL)
    {
        PrintWithColor("ERROR: Memory reallocation failed!", CONSOLE_COLOR_RED);
        free(str);
        return NULL;
    }

    sprintf_s(buffer, size, format, str);

    return buffer;
}

void Log::PrintAddInfo(char* str, int color)
{
    char* strResult = AddStrInfo(str);
    // str is realloc-ed

    if (strResult == NULL)
    {
        return;
    }

    PrintWithColor(strResult, color);
    free(strResult);
}

void Log::PrintFormatter(int color, const char* format, va_list args)
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

    PrintAddInfo(buffer, color);
}

void Log::Print(const char* str)
{
    Printf(str);
}

void Log::Printf(const char* format, ...)
{
    // Read args in the ellipsis ... parameter
    va_list args;
    va_start(args, format);
    PrintFormatter(CONSOLE_COLOR_WHITE, format, args);
    va_end(args);
}

void Log::Error(const char* err)
{
    Errorf(err);
}

void Log::Errorf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    PrintFormatter(CONSOLE_COLOR_RED, format, args);
    va_end(args);
}

void Log::Warn(const char* warn)
{
    Warnf(warn);
}

void Log::Warnf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    PrintFormatter(CONSOLE_COLOR_YELLOW, format, args);
    va_end(args);
}
