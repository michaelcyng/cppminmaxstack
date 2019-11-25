//
// Created by Cho Yiu Ng on 25.11.19.
//

#ifndef MINMAXSTACK_NONTHREADSAFEMINMAXSTACKIMPL_H
#define MINMAXSTACK_NONTHREADSAFEMINMAXSTACKIMPL_H

#include <stack>

template <typename T>
NonThreadSafeMinMaxStack<T>::NonThreadSafeMinMaxStack(): myTop(nullptr), mySize(0) {
}

template <typename  T>
NonThreadSafeMinMaxStack<T>::NonThreadSafeMinMaxStack(const NonThreadSafeMinMaxStack<T>& mmStack) {
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
NonThreadSafeMinMaxStack<T>::NonThreadSafeMinMaxStack(NonThreadSafeMinMaxStack<T>&& mmStack) noexcept : myTop(mmStack.myTop), mySize(mmStack.mySize) {
    mmStack.myTop = nullptr;
    mmStack.mySize = 0;
}

template <typename T>
NonThreadSafeMinMaxStack<T>& NonThreadSafeMinMaxStack<T>::operator=(const NonThreadSafeMinMaxStack<T>& mmStack) {
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
bool NonThreadSafeMinMaxStack<T>::empty() const {
    return (mySize == 0);
}

template <typename T>
const T& NonThreadSafeMinMaxStack<T>::max() const {
    return myMaxTop->data;
}

template <typename T>
const T& NonThreadSafeMinMaxStack<T>::min() const {
    return myMinTop->data;
}

template <typename T>
void NonThreadSafeMinMaxStack<T>::pop() {
    if (empty()) {
        return;
    }

    myMinTop = myTop->minNext;
    myMaxTop = myTop->maxNext;
    myTop = myTop->dataNext;
    --mySize;
}

template <typename T>
void NonThreadSafeMinMaxStack<T>::push(const T& data) {
    auto pData = std::make_shared<Node>(data);
    pData->dataNext = myTop;
    myTop = pData;

    if (empty()) {
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
size_t NonThreadSafeMinMaxStack<T>::size() const {
    return mySize;
}

template <typename T>
const T& NonThreadSafeMinMaxStack<T>::top() const {
    return myTop->data;
}

#endif //MINMAXSTACK_NONTHREADSAFEMINMAXSTACKIMPL_H
