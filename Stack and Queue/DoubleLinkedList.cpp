#include <iostream>
#include <cassert>

template <typename T> struct node {
  T elem;
  node<T> *next = nullptr;
  node<T> *prev = nullptr;
};

template <typename T> class DoubleLinkedList {
public:

  void push_front(const T &e) {
    node<T> *ptmp = new node<T>{};
    ptmp->elem = e;
    if (empty()) {
      head = ptmp;
      tail = ptmp;
    } else {
      ptmp->next = head;
      ptmp->prev = nullptr;
      head->prev = ptmp;
      head = ptmp;
    }
  }

  T pop_front() {
    // Assume not empty
    assert(head != nullptr);
    T to_return = head->elem;

    // If only 1 element
    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      node<T> *tmp = head->next;
      tmp->prev = nullptr;
      delete head;
      head = tmp;
    }

    return to_return;
  }

  void push_back(const T &e) {
    node<T> *tmp = new node<T>{};
    tmp->elem = e;
    if (empty()) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tmp->prev = tail;
      tail = tmp;
    }
  }

  T pop_back() {
    // Assume not empty
    assert(tail != nullptr);
    T to_return = tail->elem;

    // If only 1 element
    if (head == tail) {
      delete tail;
      head = nullptr;
      tail = nullptr;
    } else {
      node<T> *tmp = tail->prev;
      tmp->next = nullptr;
      delete tail;
      tail = tmp;
    }

    return to_return;
  }

  bool empty() { return head == nullptr; }

private:
  node<T> *head = nullptr;
  node<T> *tail = nullptr;
};