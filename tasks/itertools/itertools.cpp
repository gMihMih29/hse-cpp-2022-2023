#include "itertools.h"

IteratorRange<RangeIterator> Range(size_t end) {
    return IteratorRange(RangeIterator(0, 1), RangeIterator(end, 1));
}

IteratorRange<RangeIterator> Range(size_t begin, size_t end) {
    return IteratorRange(RangeIterator(begin, 1), RangeIterator(end, 1));
}

IteratorRange<RangeIterator> Range(size_t begin, size_t end, size_t step) {
    return IteratorRange(RangeIterator(begin, step), RangeIterator(end, step));
}