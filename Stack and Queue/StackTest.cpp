#include <iostream>
#include "Stack.cpp"

int main() {
    Stack<int> stack;
    Stack<char> charStack;

    assert(stack.empty());

    for(size_t i = 0; i < 5; i++) {
        stack.push(i);
    }
    
    assert(!stack.empty());

    while (!stack.empty()) {
        std::cout << ' ' << stack.pop();
    }
    assert(stack.empty());
    
    assert(charStack.empty());

    for(size_t i = 0; i < 5; i++) {
        charStack.push('i');
    }
    
    assert(!charStack.empty());

    while (!charStack.empty()) {
        std::cout << ' ' << charStack.pop();
    }
}
