#include <iostream> 
#include "DoubleLinkedList.cpp"

template <typename T> class Queue {
    public:
    /*Queue() {
        newLink = new DoubleLinkedList<T>();
    }*/

    void enqueue(const T &e) {
        newLink.push_back(e);
    }

    T dequeue() {
        return newLink.pop_front();
    }

    T empty() {
        return newLink.empty();
    }
    private:
    DoubleLinkedList<T> newLink;
};