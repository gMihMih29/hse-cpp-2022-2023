#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    for (Iterator i = last - 1; i >= first; --i) {
        if (*i == val) {
            return i;
        }
    }
    return last;
}
