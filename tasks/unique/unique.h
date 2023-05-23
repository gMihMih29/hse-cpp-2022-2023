#pragma once

#include <algorithm>

template <typename T>
T Unique(T begin, T end) {
    T unique_end = begin;
    ++begin;
    bool flag = begin != end;
    for (; begin < end; ++begin) {
        if (*unique_end != *begin) {
            ++unique_end;
            std::swap(*unique_end, *begin);
        }
    }
    return unique_end + (flag ? 1 : 0);
}