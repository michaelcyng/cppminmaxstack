//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACKIMPL_H
#define __CPPMINMAXSTACK_MINMAXSTACKIMPL_H

#include <stack>

template <typename T>
MinMaxStack<T>::MinMaxStack(): myTop(nullptr), mySize(0) {
}

template <typename  T>
MinMaxStack<T>::MinMaxStack(const MinMaxStack<T>& mmStack) {
    auto mmTop = mmStack.myTop;
    std::stack<T> tempStack;
    while (mmTop != nullptr) {
        tempStack.push(mmTop->data);
        mmTop = mmTop->dataNext;
    }

    mySize = 0;
    myTop = nullptr;
    while(!tempStack.empty()) {
        push(tempStack.top());
        tempStack.pop();
    }
}

template <typename T>
MinMaxStack<T>::MinMaxStack(MinMaxStack<T>&& mmStack) noexcept : myTop(mmStack.myTop), mySize(mmStack.mySize) {
    mmStack.myTop = nullptr;
    mmStack.mySize = 0;
}

template <typename T>
MinMaxStack<T>& MinMaxStack<T>::operator=(const MinMaxStack<T>& mmStack) {
    if (&mmStack == this) {
        return *this;
    }

    auto mmTop = mmStack.myTop;
    std::stack<T> tempStack;
    while (mmTop != nullptr) {
        tempStack.push(mmTop->data);
        mmTop = mmTop->dataNext;
    }

    mySize = 0;
    myTop = nullptr;
    while(!tempStack.empty()) {
        push(tempStack.top());
        tempStack.pop();
    }

    return *this;
}

template <typename T>
bool MinMaxStack<T>::empty() const {
    ReadLock_t readLock(myMutex);

    return emptyImpl();
}

template <typename T>
const T& MinMaxStack<T>::max() const {
    ReadLock_t readLock(myMutex);

    return myMaxTop->data;
}

template <typename T>
const T& MinMaxStack<T>::min() const {
    ReadLock_t readLock(myMutex);

    return myMinTop->data;
}

template <typename T>
void MinMaxStack<T>::pop() {
    WriteLock_t writeLock(myMutex);

    if (emptyImpl()) {
        return;
    }

    myMinTop = myTop->minNext;
    myMaxTop = myTop->maxNext;
    myTop = myTop->dataNext;
    --mySize;
}

template <typename T>
void MinMaxStack<T>::push(const T& data) {
    WriteLock_t writeLock(myMutex);

    auto pData = std::make_shared<Node>(data);
    pData->dataNext = myTop;
    myTop = pData;

    if (emptyImpl()) {
        myMinTop = myTop;
        myMaxTop = myTop;
        ++mySize;
        return;
    }

    ++mySize;
    pData->maxNext = myMaxTop;
    pData->minNext = myMinTop;

    if (data >= myMaxTop->data) {
        myMaxTop = pData;
    }

    if (data <= myMinTop->data) {
        myMinTop = pData;
    }

}

template <typename T>
size_t MinMaxStack<T>::size() const {
    ReadLock_t readLock(myMutex);

    return mySize;
}

template <typename T>
const T& MinMaxStack<T>::top() const {
    ReadLock_t readLock(myMutex);

    return myTop->data;
}

template <typename T>
bool MinMaxStack<T>::emptyImpl() const {
    return (mySize == 0);
}

#endif //__CPPMINMAXSTACK_MINMAXSTACKIMPL_H
