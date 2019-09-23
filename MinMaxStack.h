//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACK_H
#define __CPPMINMAXSTACK_MINMAXSTACK_H

#include <stack>

template <typename T>
class MinMaxStack {
public:

    MinMaxStack();

    bool     empty() const;
    const T& max() const;
    const T& min() const;
    void     pop();
    void     push(const T &data);
    const T& top() const;

private:

    std::stack<T> myDataStack;
    std::stack<T> myMaxStack;
    std::stack<T> myMinStack;

};

#include "MinMaxStackImpl.h"

#endif //__CPPMINMAXSTACK_MINMAXSTACK_H
