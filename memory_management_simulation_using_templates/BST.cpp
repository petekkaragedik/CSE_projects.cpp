#include "BST.h"

template <typename T>
BST<T>::~BST() { //destructor - used remove here for a recursive solution, no need to do it from scratch
    while (root) { //traverse and remove 
        remove(root->startByte);
    }
}

template <typename T> //insert a memory block into bst
bool BST<T>::insert(int start, int size) {
    Node** current = &root;
    int end = start + size - 1; //ending address
    while (*current) { //traversing properly to reach wanted location
        int nodeStart = (*current)->startByte;
        int nodeEnd = nodeStart + (*current)->size - 1;
        // check for overlap
        if ((start >= nodeStart && start <= nodeEnd) || (end >= nodeStart && end <= nodeEnd) ||(nodeStart >= start && nodeStart <= end)) {
            cerr << "Error: Memory overlap." << endl;
            return false;
        }

        if (start < (*current)->startByte)
            current = &(*current)->left;
        else if (start > (*current)->startByte)
            current = &(*current)->right;
        else {
            std::cerr << "Error: Memory overlap." << endl;
            return false;
        }
    }
    *current = new Node(start, size); // adding the new node with "new" of course
    cout << "Allocated " << size << " bytes starting at byte " << start << "." << endl;
    return true;
}

template <typename T>
bool BST<T>::remove(int addr) { //removing a memory block from bst
    Node** current = &root; //ptr to root to keep track while traversing

    while (*current){
        int start = (*current) -> startByte; // finding starting and end indexes
        int end = start + (*current) -> size -1;

        if (addr >= start && addr <= end){ // if valid
            Node * toBeDeleted = *current;

            if (toBeDeleted -> left && toBeDeleted -> right){
                // node with two children situation
                Node ** ptr_parent = &toBeDeleted -> right; //to keep the parent node
                Node * ptr = *ptr_parent;

                while (ptr -> left){
                    ptr_parent = &ptr -> left;
                    ptr = *ptr_parent;
                }

                toBeDeleted -> startByte = ptr -> startByte;
                toBeDeleted -> size = ptr -> size;
                delete ptr;
            }
            else{
                // node with one or no children situation
                Node* child;
                if(child == toBeDeleted -> left){
                    child = toBeDeleted -> left;
                }else{
                    child = toBeDeleted -> right;
                }
                *current = child;
                delete toBeDeleted;
            }
            return true;
        }
        //if no match: continue
        if (addr < start){
            current = &(*current) -> left;
        }
        else{
            current = &(*current) -> right;
        }

    }
    return false; // not found

}

template <typename T>
Stack<T>* BST<T>::find(int addr) { //finding a stack by starting location
    Node* current = root; //a node and this also has its stack in it
    while (current) {
        if (addr >= current ->startByte && addr < current ->startByte + current -> size) { // if within the range
            return current->stack;
        }
        if (addr < current->startByte) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr; //not found
}
//inorder traversal function - to display
//helper func. for inorder()
template <typename T>
void BST<T>::inorderTraversal(Node* node) const {
    if (!node) {
        return;
    }
    inorderTraversal(node->right); //recursive calls - classic in order traversal implementation
    cout << "Memory allocation starting at byte " << node->startByte << " with size " << node->size << " bytes:" << endl;
    cout << "Stack starting at byte " << node -> startByte << ":" << endl ;

    node->stack->display();
    inorderTraversal(node->left);
}
//NOTE FOR THE inorderTraversal function --> when i did it like the usual in order
//traversal implementation, it displayed the allocations in reverse order from what was wanted
//so i modified it in a way that it does "reverse" inorder traversal

template <typename T>
void BST<T>::inorder() const {
    inorderTraversal(root);
}

template <typename T>
BST<T>& BST<T>::operator+=(std::pair<int, int> alloc) {

    int start = alloc.first;
    int size = alloc.second;

    if (!insert(start, size)){
        cerr << "Error: Could not allocate memory starting at " << start << "." << endl;
    }
    return *this;
}

template <typename T>
BST<T>& BST<T>::operator-=(int byteNumber) {

    if (!remove(byteNumber)){
        cerr << "Error: Could not deallocate memory at " << byteNumber << "." << endl;
    }

    cout << "Deallocated memory containing byte " << byteNumber << "." << endl; 
    return *this;
}

template <typename T>
Stack<T>* BST<T>::operator[](int addr) {

    Stack<T>* stack = find(addr);
    if(!stack) {
        return nullptr;
    }

    return stack; 
}

//we also need to add below statements to form our BST class for different var. types
template class BST<int>;
template class BST<short>;
template class BST<char>;
