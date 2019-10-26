//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACK_H
#define __CPPMINMAXSTACK_MINMAXSTACK_H

#include <memory>
#include <shared_mutex>
#include <thread>

template <typename T>
class MinMaxStack {
public:

    MinMaxStack();
    MinMaxStack(const MinMaxStack<T>& mmStack);
    MinMaxStack(MinMaxStack<T>&& mmStack) noexcept;

    MinMaxStack<T>& operator=(const MinMaxStack<T>& mmStack);

    bool     empty() const;
    const T& max() const;
    const T& min() const;
    void     pop();
    void     push(const T &data);
    size_t   size() const;
    const T& top() const;

private:

    bool emptyImpl() const;  // No lock in this method

    typedef std::shared_lock<std::shared_mutex> ReadLock_t;
    typedef std::lock_guard<std::shared_mutex>  WriteLock_t;

    struct Node {
        T                     data;
        std::shared_ptr<Node> dataNext;
        std::shared_ptr<Node> maxNext;
        std::shared_ptr<Node> minNext;

        explicit Node(const T& data): data(data), dataNext(nullptr), maxNext(nullptr), minNext(nullptr) {}
    };

    mutable std::shared_mutex  myMutex;

    std::shared_ptr<Node>      myTop;
    std::shared_ptr<Node>      myMaxTop;
    std::shared_ptr<Node>      myMinTop;

    size_t                     mySize;

};

#include "MinMaxStackImpl.h"

#endif //__CPPMINMAXSTACK_MINMAXSTACK_H
