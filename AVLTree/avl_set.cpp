#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

template <typename T> struct node {
    T data;
    node<T> *next = nullptr;
    node<T> *prev = nullptr;
    int height; 
};

template <typename T> class avl_set {
    private:
    // A utility function to get the
    // height of the tree
    int height(node<T> *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }
    
    // A utility function to get maximum
    // of two integers
    T max(T a, T b)
    {
        return (a > b)? a : b;
    }
    
    /* Helper function that allocates a
    new node with the given key and
    NULL left and right pointers. */
    node<T>* newNode(T data)
    {
        node<T>* theNode = new node<T>{};
        theNode->data = data;
        theNode->prev = nullptr;
        theNode->next = nullptr;
        theNode->height = 1; // new node is initially
                        // added at leaf
        return theNode;
    }
    
    // A utility function to right
    // rotate subtree rooted with y
    // See the diagram given above.
    node<T> *rightRotate(node<T> *y)
    {
        node<T> *x = y->prev;
        node<T> *T2 = x->next;
    
        // Perform rotation
        x->next = y;
        y->prev = T2;
    
        // Update heights
        y->height = max(height(y->prev),
                        height(y->next)) + 1;
        x->height = max(height(x->prev),
                        height(x->next)) + 1;
    
        // Return new root
        return x;
    }
    
    // A utility function to left
    // rotate subtree rooted with x
    // See the diagram given above.
    node<T> *leftRotate(node<T> *x)
    {
        node<T> *y = x->next;
        node<T> *T2 = y->prev;
    
        // Perform rotation
        y->prev = x;
        x->next = T2;
    
        // Update heights
        x->height = max(height(x->prev),   
                        height(x->next)) + 1;
        y->height = max(height(y->prev),
                        height(y->next)) + 1;
    
        // Return new root
        return y;
    }
    
    // Get Balance factor of node N
    int getBalance(node<T> *N)
    {
        if (N == nullptr)
            return 0;
        return height(N->prev) - height(N->next);
    }
    
    // Recursive function to insert a key
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    node<T>* insert(node<T>* node, T data)
    {
        /* 1. Perform the normal BST insertion */
        if (node == nullptr)
            return(newNode(data));
    
        if (data < node->data)
            node->prev = insert(node->prev, data);
        else if (data > node->data)
            node->next = insert(node->next, data);
        else // Equal keys are not allowed in BST
            return node;
    
        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->prev),
                            height(node->next));
    
        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);
    
        // If this node becomes unbalanced, then
        // there are 4 cases
    
        // Left Left Case
        if (balance > 1 && data < node->prev->data)
            return rightRotate(node);
    
        // Right Right Case
        if (balance < -1 && data > node->next->data)
            return leftRotate(node);
    
        // Left Right Case
        if (balance > 1 && data > node->prev->data)
        {
            node->prev = leftRotate(node->prev);
            return rightRotate(node);
        }
    
        // Right Left Case
        if (balance < -1 && data < node->next->data)
        {
            node->next = rightRotate(node->next);
            return leftRotate(node);
        }
    
        /* return the (unchanged) node pointer */
        return node;
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
        return false;       
    }

    size_t size_of_tree(node<T> *rootPtr) const {
        if(rootPtr == nullptr) {
            return 0;
        }
        return size_of_tree(rootPtr->prev) + 1 + size_of_tree(rootPtr->next);
    }

    void in_order(node<T> *rootPtr, auto fn) {
        if(rootPtr == nullptr) {
            return;
        }
        in_order(rootPtr->prev, fn);
        fn(rootPtr->data);
        in_order(rootPtr->next, fn);
    }

    node<T>* minValueNode(node<T>* theNode)
    {
        node<T>* current = theNode;
    
        /* loop down to find the leftmost leaf */
        while (current->prev != NULL)
            current = current->prev;
    
        return current;
    }

    node<T>* erase(node<T>* root, T data)
    {
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == NULL)
            return root;
 
        // If the key to be deleted is smaller than
        // the root's key, then it lies in left subtree
        if (data < root->data)
            root->prev = erase(root->prev, data);
 
        // If the key to be deleted is greater than the
        // root's key, then it lies in right subtree
        else if (data > root->data)
            root->next = erase(root->next, data);
 
        // if key is same as root's key, then this is the node
        // to be deleted
        else
        {
        // node with only one child or no child
        if( (root->prev == NULL) ||
            (root->next == NULL) )
        {
            node<T> *temp = root->prev ?
                         root->prev :
                         root->next;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            root = temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            node<T>* temp = minValueNode(root->next);
 
            // Copy the inorder successor's
            // data to this node
            root->data = temp->data;
 
            // Delete the inorder successor
            root->next = erase(root->next, temp->data);
            }
        }
 
        // If the tree had only one node then return
        if (root == NULL)
            return root;
 
        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = max(height(root->prev), height(root->next)) + 1;
 
        // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
        // this node became unbalanced)
        int balance = getBalance(root);
 
        // If this node becomes unbalanced, then there are 4 cases
        // Left Left Case
        if (balance > 1 && getBalance(root->prev) >= 0)
            return rightRotate(root);
 
        // Left Right Case
        if (balance > 1 && getBalance(root->prev) < 0)
        {
            root->prev = leftRotate(root->prev);
            return rightRotate(root);
        }
 
        // Right Right Case
        if (balance < -1 && getBalance(root->next) <= 0)
            return leftRotate(root);
 
        // Right Left Case
        if (balance < -1 && getBalance(root->next) > 0)
        {
            root->next = rightRotate(root->next);
            return leftRotate(root);
        }
 
        return root;
    }

    public:

    node<T> *mainRoot = NULL;

    void insert(T data) {
        mainRoot = insert(mainRoot, data);
    }

    bool contains(T data) const {
        return contains(mainRoot, data);
    }

    size_t size() const {
        return size_of_tree(mainRoot);
    }
    node<T>* erase(T data) {
        erase(mainRoot, data);
    }

    void for_each(auto fn) {
        in_order(mainRoot, fn);
    }
};

