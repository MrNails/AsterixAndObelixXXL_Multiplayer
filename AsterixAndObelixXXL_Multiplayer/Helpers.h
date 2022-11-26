#pragma once
#include <string>
#include <memory>
#include <cassert>

inline static const char EMPTY_STRING[2] = { ' ', '\0' };

template<typename ... Args>
std::string StringFormat(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) return format;
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template<typename ... Args>
const char* StringFormat(const char* format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format, args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) return format;
    auto size = static_cast<size_t>(size_s);
    char* newStr = new char[size];
    std::snprintf(newStr, size, format, args ...);
    return newStr;
}

inline void DeleteStringAndSetNull(const char** str) {
    assert(str != nullptr);

    if (*str != nullptr && *str != EMPTY_STRING) {
        delete[] *str;
        *str = nullptr;
    }
}