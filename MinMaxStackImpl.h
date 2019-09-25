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
bool MinMaxStack<T>::empty() const {
    return myDataStack.empty();
}

template <typename T>
const T& MinMaxStack<T>::max() const {
    return myMaxStack.top();
}

template <typename T>
const T& MinMaxStack<T>::min() const {
    return myMinStack.top();
}

template <typename T>
void MinMaxStack<T>::pop() {
    if (empty()) {
        return;
    }

    if (myMinStack.top() == myDataStack.top()) {
        myMinStack.pop();
    }

    if (myMaxStack.top() == myDataStack.top()) {
        myMaxStack.pop();
    }

    myDataStack.pop();
}

template <typename T>
void MinMaxStack<T>::push(const T& data) {
    myDataStack.push(data);

    if (myMinStack.empty() || data <= myMinStack.top()) {
        myMinStack.push(data);
    }

    if (myMaxStack.empty() || data >= myMaxStack.top()) {
        myMaxStack.push(data);
    }
}

template <typename T>
const T& MinMaxStack<T>::top() const {
    return myDataStack.top();
}

#endif //__CPPMINMAXSTACK_MINMAXSTACKIMPL_H
