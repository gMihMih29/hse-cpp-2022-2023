#pragma once

#include <cstdint>
#include <vector>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

class RangeIterator {
public:
    RangeIterator(size_t value, size_t step) : value_(value), step_(step) {
    }

    RangeIterator& operator++() {
        value_ += step_;
        return *this;
    }

    size_t operator*() {
        return value_;
    }

    bool operator!=(const RangeIterator& other) const {
        return value_ < other.value_;
    }

private:
    size_t value_;
    size_t step_;
};

template <class T, class U>
class ZipIterator {
public:
    ZipIterator(T current_first, U current_second) : current_first_(current_first), current_second_(current_second) {
    }

    ZipIterator& operator++() {
        ++current_first_;
        ++current_second_;
        return *this;
    }

    const auto operator*() {
        return std::make_pair(*current_first_, *current_second_);
    }

    bool operator!=(const ZipIterator& other) {
        return current_first_ != other.current_first_ && current_second_ != other.current_second_;
    }

private:
    T current_first_;
    U current_second_;
};

// template <class T>
// class GroupIterator {
// public:
//     class ElemIterator {
//     public:
//         friend class GroupIterator;

//     public:
//         ElemIterator(T ptr, size_t cnt) : ptr_(ptr), cnt_(cnt), pos_(0) {
//         }

//         ElemIterator& operator++() {
//             ++pos_;
//             return *this;
//         }

//         const auto operator*() {
//             return *ptr_;
//         }

//         bool operator!=(const ElemIterator& other) {
//             return ptr_ != other.ptr_;
//         }

//     private:
//         T ptr_;
//         size_t cnt_;
//         size_t pos_;
//     };

// public:
//     GroupIterator(T begin, T end) : ptr_(begin), end_(end) {
//         size_t cnt = 0;
//         for (auto i = ptr_; i < end_ && *i == *ptr_; ++i) {
//             ++cur_elem_.cnt_;
//         }
//     }

//     GroupIterator& operator++() {
//         for (auto i = ptr_; i < end_ && *i != *ptr_; ++i, ++ptr_) {
//         }
//         cur_elem_.ptr_ = ptr_ cur_elem_.cnt = 0;
//         for (auto i = ptr_; i < end_ && *i == *ptr_; ++i) {
//             ++cur_elem_.cnt_;
//         }
//         return *this;
//     }

//     T begin() const {  // NOLINT
//         return ptr_;
//     }

//     T end() const {  // NOLINT
//         return end_;
//     }

//     const auto operator*() {
//         return cur_elem_;
//     }

//     bool operator!=(const GroupIterator& other) {
//         return ptr_ != other.ptr_;
//     }

// private:
//     ElemIterator cur_elem_;
//     T ptr_;
//     T end_;
// };

template <class T>
class ElemIterator {
public:
    ElemIterator(T value, size_t pos) : value_(value), pos_(pos) {
    }

    ElemIterator& operator++() {
        ++pos_;
        return *this;
    }

    T operator*() {
        return value_;
    }

    bool operator!=(const ElemIterator& other) const {
        return pos_ < other.pos_;
    }
private:
    T value_;
    size_t pos_;
};

template <class Iterator>
class GroupIterator {
public:
    GroupIterator(Iterator begin, Iterator end) : begin_(begin), pos_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

    auto operator*() const {
        size_t cnt = 0;
        for (Iterator i = pos_; i != end_ && *i == *pos_; ++i, ++cnt);
        return IteratorRange(ElemIterator(*pos_, 0), ElemIterator(*pos_, cnt));
    }

    GroupIterator& operator++() {
        Iterator i = pos_;
        for (; i != end_ && *i == *pos_; ++i);
        pos_ = i;
        return *this;
    }

    bool operator!=(const GroupIterator& other) const {
        return pos_ != other.pos_;
    }

private:
    Iterator begin_;
    Iterator pos_;
    Iterator end_;
};

IteratorRange<RangeIterator> Range(size_t end) {
    return IteratorRange(RangeIterator(0, 1), RangeIterator(end, 1));
}

IteratorRange<RangeIterator> Range(size_t begin, size_t end) {
    return IteratorRange(RangeIterator(begin, 1), RangeIterator(end, 1));
}

IteratorRange<RangeIterator> Range(size_t begin, size_t end, size_t step) {
    return IteratorRange(RangeIterator(begin, step), RangeIterator(end, step));
}

template <class IterableFirst, class IterableSecond>
auto Zip(const IterableFirst& cf, const IterableSecond& cu) {
    return IteratorRange(ZipIterator(cf.begin(), cu.begin()), ZipIterator(cf.end(), cu.end()));
}

template <class Container>
auto Group(const Container& container) {
    return IteratorRange(GroupIterator(container.begin(), container.end()),
                         GroupIterator(container.end(), container.end()));
}
