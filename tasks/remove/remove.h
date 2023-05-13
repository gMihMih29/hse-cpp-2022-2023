#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T values_to_remove_iter = begin;
    for (; begin < end; ++begin) {
        if (*begin != value) {
            std::swap(*values_to_remove_iter, *begin);
            ++values_to_remove_iter;
        }
    }
    return values_to_remove_iter;
}
