//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACK_H
#define __CPPMINMAXSTACK_MINMAXSTACK_H

#include <stack>
#include <thread>

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
    const T& top() const;

private:

    std::stack<T> myDataStack;
    std::stack<T> myMaxStack;
    std::stack<T> myMinStack;

    std::mutex    myMutex;

};

#include "MinMaxStackImpl.h"

#endif //__CPPMINMAXSTACK_MINMAXSTACK_H
