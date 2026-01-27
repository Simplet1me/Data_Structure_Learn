#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include "color.hpp"

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


template <typename T>
inline void println(const T& value, color::Type c = color::Type::Default) {
    std::cout << color::to_ansi(c)
              << value
              << color::to_ansi(color::Type::Default)
              << std::endl;
}

template <typename T>
inline void print(const T& value, color::Type c = color::Type::Default) {
    std::cout << color::to_ansi(c)
              << value
              << color::to_ansi(color::Type::Default);
}


template <typename T,size_t N>
inline void printArr(const T(&arr)[N],color::Type c = color::Type::Default){
    print("[");
    for(size_t i = 0;i < N;i++){
        print(arr[i],c);
        if (i != N-1){
            print(",");
        }
    }
    print("]");
    std::cout<<std::endl;
}

template <typename T>
inline void printVector(const std::vector<T>& vec,color::Type c = color::Type::Default){
    print("[");
    for(size_t i = 0;i < vec.size();i++){
        print(vec[i],c);
        if (i != vec.size()-1){
            print(",");
        }
    }
    print("]");
    std::cout<<std::endl;
}