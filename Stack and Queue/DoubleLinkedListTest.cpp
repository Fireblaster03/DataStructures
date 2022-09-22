#include <iostream>
#include "DoubleLinkedList.cpp"

int main() {
    DoubleLinkedList<int> DLL;
    
    assert(DLL.empty());

    DLL.push_front(5);
    DLL.push_front(11);
    assert(DLL.pop_back() == 5);
    DLL.push_back(9);
    DLL.push_back(11);
    assert(DLL.pop_front() == 11);
    assert(!DLL.empty());

    while (!DLL.empty()) {
        std::cout << ' ' << DLL.pop_front();
    }
}