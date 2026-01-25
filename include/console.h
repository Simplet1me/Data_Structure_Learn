#pragma once


#ifdef _WIN32
#include <windows.h>
#endif

#include "color.h"
#include <iostream>

inline void console_init() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
#endif
}


template <typename Tp>
inline void print(const Tp& value, color::Type c = color::Type::Default) {
    std::cout << color::to_ansi(c)
              << value
              << color::to_ansi(color::Type::Default)
              << std::endl;
}