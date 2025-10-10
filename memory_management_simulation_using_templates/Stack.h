#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename T>
//given
// Structure to hold variable information
    struct Variable {
        int address;    // Memory address of the variable
        T value;       // Value of the variable
    };

template <typename T>
class Stack {
private:
    struct Node {
        Variable<T> data; //the variable is stored in the stack
        Node* next;
        Node(const Variable<T>& var, Node* nextNode = nullptr) 
            : data(var), next(nextNode) {}
    };

    Node* topNode;  //ptr to top node
    int totalSize;  //size of allocated memory in this stack (max size you can use)
    int usedSize;   //current used size in bytes (increment-decrement as we go)

public:
    Stack(int size) : topNode(nullptr), totalSize(size), usedSize(0) {} //constructor with default values initialized
    ~Stack();

    bool push(const Variable<T>& var);  //push
    bool pop(int address);              //pop
    void display() const;               //display
    Stack<T>& operator<<(pair<int, T> value);
    Stack<T>& operator>>(int addr);
    //While working on the project, i also realized that the ! operator is not 
    //defined on the Stack class and the compiler is giving me an error and telling me to overload it
    bool operator!() const;
};

#endif