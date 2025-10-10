#include "Stack.h"

template <typename T>
Stack<T>::~Stack() {    //destructor - deleting each node by traversing the stack
    while (topNode) {
        Node* temp = topNode;
        topNode = topNode->next;
        usedSize -= sizeof(T);
        delete temp;
    }
}

template <typename T>
bool Stack<T>::push(const Variable<T>& var) { //pushing var. to stack
    int typeSize = sizeof(T);
    if (usedSize + typeSize > totalSize) { //check if there is space left in the previously allocated memory
        cerr << "Error: Not enough space to push variable." << endl;
        return false;
    }
    topNode = new Node(var, topNode);
    usedSize += typeSize; //update usedSize accordingly
    return true;
}

template <typename T>
bool Stack<T>::pop(int address) { //popping a var. from stack
    if (!topNode || topNode->data.address != address) { //checking for unwanted conditions
        cerr << "Error: Cannot pop variable. Address mismatch." << endl;
        return false;
    }
    Node* temp = topNode; 
    topNode = topNode->next;
    usedSize -= sizeof(T); //removing top node and updating usedSize accordingly
    delete temp; 
    return true;
}

template <typename T>
void Stack<T>::display() const { //displaying stack by traversing with a loop
    Node* current = topNode; 
    while (current) {
        cout << "Variable from address " << current->data.address  << " to " << current->data.address + sizeof(T) - 1 << ", Type: " << typeid(T).name() << ", Value: " << current->data.value << endl;
        current = current->next;
    }
}

template <typename T>
Stack<T>& Stack<T>::operator<<(pair<int, T> value) {

    Variable<T> var;
    var.address = value.first;
    var.value= value.second;

    if(!push(var)){
        cout << "Error: Could not define variable at adress " << value.first << "." << endl;
    }

    cout << "Defined variable at address " << var.address << ": Type i, Value: " << var.value << "." << endl;
    return *this;

}

template <typename T>
Stack<T>& Stack<T>::operator>>(int addr) {

    if(!pop(addr)){
        cout << "Error: Could not undefine variable at address " << addr << "." << endl;
    }
    cout << "Undefined variable at address " << addr << "." << endl;
    return *this;

}

template<typename T> 
bool Stack<T>::operator!() const {

    bool flag = true;
    if(topNode == nullptr){
        flag = true;
    }else{
        flag = false;
    }

    return flag;
}

//we also need to add below statements to form our Stack class for different var. types
template class Stack<int>;
template class Stack<short>;
template class Stack<char>;

