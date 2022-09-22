#include <iostream>
#include "DoubleLinkedList.cpp"

template <typename T> class Stack {
    public:
    /*Stack() {
        newLink = new DoubleLinkedList<T>();
    }*/

    /*~Stack() {
        delete newLink;
    }*/

    void push(const T &e) {
        newLink.push_front(e);
    }

    T pop() {
        return newLink.pop_front();
    }

    T empty() {
        return newLink.empty();
    }

    private: 
    DoubleLinkedList<T> newLink;
};