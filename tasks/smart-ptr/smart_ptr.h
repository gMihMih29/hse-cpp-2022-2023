#pragma once

#include <string>

template <class T>
class ControlBlock {
private:
    T* ptr_;
    size_t cnt_shared_;
    size_t cnt_weak_;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
public:
    SharedPtr();

    SharedPtr(const WeakPtr<T>& rhs);

    SharedPtr(T*);

    T* Get();

    T operator*();

    void Reset(T*);

private:
    T* ptr_;
    ControlBlock* ctrl_block_;
};

template <class T>
class WeakPtr {
public:
    WeakPtr();

    WeakPtr(const SharedPtr<T>& rhs);

    SharedPtr Lock();

    bool IsExpired();
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& rhs) {
}
