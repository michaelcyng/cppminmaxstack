//
// Created by Cho Yiu Ng on 23.09.19.
//

#ifndef __CPPMINMAXSTACK_MINMAXSTACKIMPL_H
#define __CPPMINMAXSTACK_MINMAXSTACKIMPL_H

template <typename  T>
MinMaxStack<T>::MinMaxStack(const MinMaxStack<T>& mmStack) : myDataStack(mmStack.myDataStack),
                                                             myMaxStack(mmStack.myMaxStack),
                                                             myMinStack(mmStack.myMinStack) {
}

template <typename T>
MinMaxStack<T>::MinMaxStack(MinMaxStack<T>&& mmStack) noexcept : myDataStack(std::move(mmStack.myDataStack)),
                                                                 myMaxStack(std::move(mmStack.myMaxStack)),
                                                                 myMinStack(std::move(mmStack.myMinStack)) {

}

template <typename T>
MinMaxStack<T>& MinMaxStack<T>::operator=(const MinMaxStack<T>& mmStack) {
    if (&mmStack == this) {
        return *this;
    }

    myDataStack = mmStack.myDataStack;
    myMaxStack = mmStack.myMaxStack;
    myMinStack = mmStack.myMinStack;
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

    return *myMaxStack.top();
}

template <typename T>
const T& MinMaxStack<T>::min() const {
    ReadLock_t readLock(myMutex);

    return *myMinStack.top();
}

template <typename T>
void MinMaxStack<T>::pop() {
    WriteLock_t writeLock(myMutex);

    if (emptyImpl()) {
        return;
    }

    if (*myMinStack.top() == *myDataStack.top()) {
        myMinStack.pop();
    }

    if (*myMaxStack.top() == *myDataStack.top()) {
        myMaxStack.pop();
    }

    myDataStack.pop();
}

template <typename T>
void MinMaxStack<T>::push(const T& data) {
    WriteLock_t writeLock(myMutex);

    auto pData = std::make_shared<T>(data);

    myDataStack.push(pData);

    if (myMinStack.empty() || data <= *myMinStack.top()) {
        myMinStack.push(pData);
    }

    if (myMaxStack.empty() || data >= *myMaxStack.top()) {
        myMaxStack.push(pData);
    }
}

template <typename T>
size_t MinMaxStack<T>::size() const {
    ReadLock_t readLock(myMutex);

    return myDataStack.size();
}

template <typename T>
const T& MinMaxStack<T>::top() const {
    ReadLock_t readLock(myMutex);

    return *myDataStack.top();
}

template <typename T>
bool MinMaxStack<T>::emptyImpl() const {
    return myDataStack.empty();
}

#endif //__CPPMINMAXSTACK_MINMAXSTACKIMPL_H
