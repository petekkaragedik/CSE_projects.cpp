#ifndef BST_H
#define BST_H

#include "Stack.h"
#include <iostream>
using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        int startByte;   //starting memory location/address for the memory we allocated
        int size;        //size of the memry block we allocated
        Stack<T>* stack; //ptr to the stack of this particular node
        Node* left;      //usual BST implementation
        Node* right;

        Node(int start, int sz) // constructor with default initializzations
            : startByte(start), size(sz), stack(new Stack<T>(sz)), left(nullptr), right(nullptr) {}
        ~Node() {  //destructor of node also because we allocated new stack here too using new (have to return back)
            delete stack; 
        }
    };

    Node* root; // as usual BST, we need a root node

    void inorderTraversal(Node* node) const;

public:
    BST() : root(nullptr) {} //constructor with necessary initializaiton
    ~BST();

    bool insert(int start, int size);
    bool remove(int addr);
    Stack<T>* find(int addr);
    void inorder() const;
    BST<T>& operator+=(pair<int, int> alloc);
    BST<T>& operator-=(int byteNumber);
    Stack<T> *operator[](int addr);
};

#endif