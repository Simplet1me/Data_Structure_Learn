#pragma once
#include <iostream>

namespace color {

inline constexpr const char* reset  = "\033[0m";
inline constexpr const char* red    = "\033[31m";
inline constexpr const char* green  = "\033[32m";
inline constexpr const char* yellow = "\033[33m";
inline constexpr const char* blue   = "\033[34m";

enum class Type {
    Red,
    Green,
    Yellow,
    Blue,
    Default
};

inline const char* to_ansi(Type c) {
    switch (c) {
    case Type::Red:    return red;
    case Type::Green:  return green;
    case Type::Yellow: return yellow;
    case Type::Blue:   return blue;
    default:           return reset;
    }
}

}
