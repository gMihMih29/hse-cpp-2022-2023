#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    int length = end - begin;
    for (int i = 0; i < length - 1; ++i) {
        for (int j = i + 1; j < length; ++j) {
            if (!comparator(*(begin + i), *(begin + j))) {
                std::swap(*(begin + i), *(begin + j));
            }
        }
    }
}
