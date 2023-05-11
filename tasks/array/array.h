#pragma once

#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array();

    Array(size_t size);

    Array(std::initializer_list<T> list);

    Array(const Array& other);

    Array& operator=(const Array& other);

    ~Array();

    T& operator[](size_t index);

    const T& operator[](size_t index) const;

    size_t size() const; // NOLINT

    class Iterator {
    public:
        Iterator(T* current);

        Iterator& operator++();

        T& operator*();

        bool operator!=(const Iterator& other);

    private:
        T* current_;
    };

    Iterator begin() const; // NOLINT

    Iterator end() const; // NOLINT
};
