//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACK_H
#define __CPPMINMAXSTACK_MINMAXSTACK_H

#include <memory>
#include <shared_mutex>
#include <thread>

template <typename T>
class NonThreadSafeMinMaxStack;

template <typename T>
class MinMaxStack {
public:

    MinMaxStack() = default;
    MinMaxStack(const MinMaxStack<T>& mmStack);
    MinMaxStack(MinMaxStack<T>&& mmStack) noexcept;

    MinMaxStack<T>& operator=(const MinMaxStack<T>& mmStack);

    bool     empty() const;
    const T& max() const;
    const T& min() const;
    void     pop();
    void     push(const T &data);
    size_t   size() const;
    void     swap(MinMaxStack<T>& other);
    const T& top() const;

private:

    typedef std::shared_lock<std::shared_mutex> ReadLock_t;
    typedef std::lock_guard<std::shared_mutex>  WriteLock_t;

    static std::shared_mutex ourMutex;

    mutable std::shared_mutex   myMutex;
    NonThreadSafeMinMaxStack<T> myInternalMinMaxStack;
};

#include "MinMaxStackImpl.h"

#endif //__CPPMINMAXSTACK_MINMAXSTACK_H
