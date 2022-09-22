#include <iostream>
#include "Queue.cpp"

int main() {
    Queue<int> queue;
    assert(queue.empty());

    for(size_t i = 0; i < 5; i++) {
        queue.enqueue(i);
    }
    
    assert(!queue.empty());

    while (!queue.empty()) {
        std::cout << ' ' << queue.dequeue();
    }
    assert(queue.empty());

    Queue<char> charQueue;
    assert(charQueue.empty());

    for(size_t i = 0; i < 5; i++) {
        charQueue.enqueue('i');
    }
    
    assert(!charQueue.empty());

    while (!charQueue.empty()) {
        std::cout << ' ' << charQueue.dequeue();
    }
    assert(charQueue.empty());
}