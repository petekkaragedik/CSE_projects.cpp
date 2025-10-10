#include <iostream>
#include <string>
#include "StringStack.h"
using namespace std;

StringStack::StringStack(){
    top = nullptr;
}
//the implementation and functionality is same with clear function 
//so we might as well just call it
StringStack::~StringStack(){
    clear();
}
void StringStack::push(const std::string& value){
    top = new StackNode(value, top);
}

string StringStack::pop(){
    if (top == nullptr) {
        return "Stack is empty!!!";
    } else {
        string value = top->data; //store value so you dont lose
        StackNode* temp = top; //dummy to keep top
        top = top->next;
        delete temp;
        return value; //return val
    }
}

bool StringStack::isEmpty() const{
    if(top == nullptr){
        return true;
    }else{
        return false;
    }
}
void StringStack::printStack() const{
    StackNode *curr = top;
    while(curr != nullptr){
        cout << curr ->data << " ";
        curr = curr ->next;
    }
    cout << endl;
}
void StringStack::clear(){
    while (top != nullptr) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}
// so that we could copy out BST safely without any segmentation faults
//because i got segmentation fault :)
StringStack& StringStack::operator=(const StringStack& rhs) {
    if (this != &rhs) {
        clear();  // clear to avoid memory leakage
        StackNode* current = rhs.top; //to traverse
        StackNode* last = nullptr;

        while (current) {
            StackNode* newNode = new StackNode(current->data);  // copy nodes

            if (last == nullptr) {
                top = newNode;  //top node
            } else {
                last->next = newNode;  //chaining one node to other from end
            }
            last = newNode;
            current = current->next;
        }
    }
    return *this;
}
