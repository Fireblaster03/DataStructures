#include <iostream>
#include <vector>
#include <list>


template <typename T> struct node {
    T data;
    node<T> *next = nullptr;
    node<T> *prev = nullptr;
};

template <typename T> class hash_table_set {

    private:
    std::vector<node<T>*> store;   
    
    T hash_function(T data) const {

        std::hash<T> hash_func;
        return (hash_func(data) % 10);
    }
    

    size_t counter = 0;

    public:
    
    hash_table_set() {
        store.resize(10);
    }
    
    void insert(T data) {
        
        //hashTest.insert(data);
        
        T index = hash_function(data);

        if(store[index] != nullptr) {
            node<T>* currentNode = store[index];
            while(currentNode->next != nullptr) { 
                if(currentNode->data == data) {
                    return;
                }
                currentNode = currentNode->next;
            }
                node<T>* nextNode = new node<T>();
                nextNode->data = data;
                currentNode->next = nextNode;
                nextNode->next = nullptr;
                counter += 1;
        }
        else {
            node<T>* newNode = new node<T>();
            newNode->data = data;
            store[index] = newNode;
            counter += 1;
        }

    }

    bool contains(T data) const {
        T storedData = hash_function(data);
        if(store[storedData] == NULL) {
            return false;
        }
        // checks if head has data
        else if(store[storedData]->data == data) {
            return true;
        }
        // if head doesnt checks if any element has data
        else if(store[storedData]->data != data) {
            node<T>* currentNode = store[storedData];
            while(currentNode != nullptr) { 
                if(currentNode->data == data) {
                    return true;
                }
                currentNode = currentNode->next;
            }
            return false;
        }
    }

    size_t size() const {
        return counter;
    }

    void erase(T data) {
        
        T index = hash_function(data);
        
            node<T>* prevNode = nullptr;
            node<T>* currentNode = store[index];
            while(currentNode != nullptr) { 
                if(currentNode->data == data) {
                    if(prevNode == nullptr) {
                        store[index] = currentNode->next;
                    }
                    else {
                        prevNode->next = currentNode->next;
                    } 

                    counter -= 1;
                    delete currentNode;
                    return;
                }
                prevNode = currentNode;
                currentNode = currentNode->next;
            }
            
    }

    void for_each(auto fn) {
        
        for(int i = 0; i < store.size(); i++) {
            node<T>* currentNode = store[i];
            while(currentNode != nullptr) {
                fn(currentNode->data);
                currentNode = currentNode->next;
            }
        }

    }
}; 