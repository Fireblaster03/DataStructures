#include <cstddef>
#include <iostream>

template <typename T> struct node {
    T data;
    node<T> *next = nullptr;
    node<T> *prev = nullptr;
};

template <typename T> class naive_set {
    private:

    

    void insert(node<T> *rootPtr, T data) {
        if(rootPtr == nullptr) {
            node<T> *newNode = new node<T>{};
            newNode->data = data;
            rootPtr = newNode; 
            mainRoot = rootPtr;
        }
        else if(data < rootPtr->data) {
            if(rootPtr->prev == nullptr) {
                node<T> *ptmp = new node<T>{};
                ptmp->data = data;
                rootPtr->prev = ptmp;
                return;
            }
            insert(rootPtr->prev, data);
        }
        else if(data > rootPtr->data) {
            if(rootPtr->next == nullptr) {
                node<T> *ptmp = new node<T>{};
                ptmp->data = data;
                rootPtr->next = ptmp;
                return;
            }
            insert(rootPtr->next, data);
        }        
    }

    void in_order(node<T> *rootPtr, auto fn) {
        if(rootPtr == nullptr) {
            return;
        }
        in_order(rootPtr->prev, fn);
        fn(rootPtr->data);
        in_order(rootPtr->next, fn);
    }  

    size_t size_of_tree(node<T> *rootPtr) const {
        if(rootPtr == nullptr) {
            return 0;
        }
        return size_of_tree(rootPtr->prev) + 1 + size_of_tree(rootPtr->next);
    }

    bool contains(node<T> *rootPtr ,T data) const {
        if(rootPtr == nullptr) {
            return false;
        }
        else if(rootPtr->data == data) {
            return true;
        }
        else if(data < rootPtr->data) {
            return contains(rootPtr->prev, data);
        }

        else if(data > rootPtr->data) {
            return contains(rootPtr->next, data);
        }        
    }


    void erase(node<T> *rootPtr, T data) {
        
        node<T> *parentNode = new node<T>{};
        // finding node with data
        while (rootPtr != nullptr && rootPtr->data != data) {
            parentNode = rootPtr;
            if(rootPtr->data > data) {
                rootPtr = rootPtr->prev;
            }
            else if(data > rootPtr->data) {
                rootPtr = rootPtr->next;
            }
        }
        
        // if data isn't found
        if(rootPtr == nullptr) {
            return;
        }

        // leaf node
        if(rootPtr->prev == nullptr && rootPtr->next == nullptr) {
            if(parentNode->next == rootPtr) {
                delete rootPtr;
                parentNode->next = nullptr;
            }
            else if(parentNode->prev == rootPtr) {
                delete rootPtr;
                parentNode->prev = nullptr;
            }
        }

        // if connected to 1 node
        else if(rootPtr->prev != nullptr && rootPtr->next == nullptr) {
            node<T>* ptmp = new node<T> {};
            ptmp = rootPtr->prev;
            rootPtr->prev = nullptr;
            
            if(parentNode->next == rootPtr) {
                parentNode->next = ptmp;
                delete rootPtr;
            }
            else if(parentNode->prev == rootPtr) {
                parentNode->prev = ptmp;
                delete rootPtr;
            }
            else {
                mainRoot = ptmp;
            }
        }
        else if(rootPtr->prev == nullptr && rootPtr->next != nullptr) {
            node<T>* ptmp = new node<T> {};
            ptmp = rootPtr->next;
            rootPtr->next = nullptr;

            if(parentNode->next == rootPtr) { 
                parentNode->next = ptmp;
                delete rootPtr;
            }
            else if(parentNode->prev == rootPtr) {
                parentNode->prev = ptmp;
                delete rootPtr;
            }
            else {
                mainRoot = ptmp;
            }
        }
        // if connected to 2 nodes
        else if(rootPtr->prev != nullptr && rootPtr->next != nullptr) {
            node<T>* successor = rootPtr->next;
            node<T>* successorParent = rootPtr;

                while(successor->prev != nullptr) {
                    successorParent = successor;
                    successor = successor->prev;
                }
                rootPtr->data = successor->data;
                successorParent->prev = successor->next;
                //successor->prev = rootPtr->prev;
                //successorParent->prev = successor->next;
                //successor->next = nullptr;
                //erase(rootPtr->next, successor->data);
        }
    }

    public:

    node<T> *mainRoot = nullptr;

    void insert(T data) {
        insert(mainRoot, data);
    }

    bool contains(T data) const {
        return contains(mainRoot, data);
    }

    size_t size() const {
        return size_of_tree(mainRoot);
    }
    void erase(T data) {
        erase(mainRoot, data);
    }

    void for_each(auto fn) {
        in_order(mainRoot, fn);
    }
  
};
/*
int main() {
    naive_set<int> NS;

    NS.insert(4);
    NS.insert(2);
    NS.insert(5);
    NS.insert(1);
    NS.insert(3);


    //NS.erase(2);
    //NS.erase(5);
    //NS.erase(4);

    std::cout << NS.mainRoot->data << std::endl;

    std::cout << std::endl;
    std::cout << NS.contains(5) << std::endl;
    std::cout << NS.contains(2) << std::endl;
    std::cout << NS.size() << std::endl;
}*/