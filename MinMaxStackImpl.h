//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACKIMPL_H
#define __CPPMINMAXSTACK_MINMAXSTACKIMPL_H

#include <stack>

#include <internal/NonThreadSafeMinMaxStack.h>

template <typename  T>
MinMaxStack<T>::MinMaxStack(const MinMaxStack<T>& mmStack) : myInternalMinMaxStack(mmStack.myInternalMinMaxStack) {
}

template <typename T>
MinMaxStack<T>::MinMaxStack(MinMaxStack<T>&& mmStack) noexcept : myInternalMinMaxStack(std::move(mmStack.myInternalMinMaxStack)) {
}

template <typename T>
MinMaxStack<T>& MinMaxStack<T>::operator=(const MinMaxStack<T>& mmStack) {
    if (&mmStack == this) {
        return *this;
    }

    this->myInternalMinMaxStack = mmStack.myInternalMinMaxStack;
    return *this;
}

template <typename T>
bool MinMaxStack<T>::empty() const {
    ReadLock_t readLock(myMutex);

    return myInternalMinMaxStack.empty();
}

template <typename T>
const T& MinMaxStack<T>::max() const {
    ReadLock_t readLock(myMutex);

    return myInternalMinMaxStack.max();
}

template <typename T>
const T& MinMaxStack<T>::min() const {
    ReadLock_t readLock(myMutex);

    return myInternalMinMaxStack.min();
}

template <typename T>
void MinMaxStack<T>::pop() {
    WriteLock_t writeLock(myMutex);

    myInternalMinMaxStack.pop();
}

template <typename T>
void MinMaxStack<T>::push(const T& data) {
    WriteLock_t writeLock(myMutex);

    myInternalMinMaxStack.push(data);
}

template <typename T>
size_t MinMaxStack<T>::size() const {
    ReadLock_t readLock(myMutex);

    return myInternalMinMaxStack.size();
}

template <typename T>
const T& MinMaxStack<T>::top() const {
    ReadLock_t readLock(myMutex);

    return myInternalMinMaxStack.top();
}

#endif //__CPPMINMAXSTACK_MINMAXSTACKIMPL_H
