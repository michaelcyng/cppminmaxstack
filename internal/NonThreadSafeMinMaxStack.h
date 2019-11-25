//
// Created by Cho Yiu Ng on 25.11.19.
//

#ifndef MINMAXSTACK_NONTHREADSAFEMINMAXSTACK_H
#define MINMAXSTACK_NONTHREADSAFEMINMAXSTACK_H

template <typename T>
class NonThreadSafeMinMaxStack {
public:

    NonThreadSafeMinMaxStack();
    NonThreadSafeMinMaxStack(const NonThreadSafeMinMaxStack<T>& mmStack);
    NonThreadSafeMinMaxStack(NonThreadSafeMinMaxStack<T>&& mmStack) noexcept;

    NonThreadSafeMinMaxStack<T>& operator=(const NonThreadSafeMinMaxStack<T>& mmStack);

    [[nodiscard]] bool     empty() const;
                  const T& max() const;
                  const T& min() const;
                  void     pop();
                  void     push(const T &data);
    [[nodiscard]] size_t   size() const;
                  const T& top() const;

private:

    struct Node {
        T                     data;
        std::shared_ptr<Node> dataNext;
        std::shared_ptr<Node> maxNext;
        std::shared_ptr<Node> minNext;

        explicit Node(const T& data): data(data), dataNext(nullptr), maxNext(nullptr), minNext(nullptr) {}
    };

    std::shared_ptr<Node>      myTop;
    std::shared_ptr<Node>      myMaxTop;
    std::shared_ptr<Node>      myMinTop;

    size_t                     mySize;

};

#include "internal/NonThreadSafeMinMaxStackImpl.h"


#endif //MINMAXSTACK_NONTHREADSAFEMINMAXSTACK_H
