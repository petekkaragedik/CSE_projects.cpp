// to run  g++ hw4.cpp BSTStringStack.cpp StringStack.cpp -o main


#include <iostream>
#include <string>
#include "BSTStringStack.h"
using namespace std;

BSTStringStack::BSTStringStack(){
    root = nullptr;
}
// it basically does the same thing as clear member function
//so we might as well just use that
BSTStringStack::~BSTStringStack(){
    clear(root);
} 
// Method to print the tree in in-order traversal
void BSTStringStack::printInOrder() const{
    printInOrder(root);
    cout << endl;
}

// Helper function to insert a node into the BST and count nodes checked
int BSTStringStack::insert(BSTNode*& node, int id, const std::string& value){
    if (node == nullptr) {
        node = new BSTNode(id);  // creating the new node
        node->stack.push(value);  // pushing value to its stack
        return 1;  // we checked only 1 node
    }
    if (id == node->id) { // if we are gonna push a string to the same stack we're staring
        node->stack.push(value);
        return 1;  // checked 1
    //other cases done recursively
    } else if (id < node->id) {
        return 1 + insert(node->left, id, value);//checking left if its on the left
    } else { //checking right otherwise
        return 1 + insert(node->right, id, value);
    }
    
}

// Helper function to search for a node in the BST and count nodes checked
int BSTStringStack::search(BSTNode* node, int id, std::string& value){
    if(node == nullptr){
        return 0; //couldnt find node
    }if(id == node->id){
        if(node->stack.isEmpty()){
            value = "Stack is empty!!!";
        }else{
            value = node->stack.pop();
        }
    return 1; //node found by traversing 1 node
    }
    //recursive here to traverse through the tree
    else if(id < node->id){ //its on the left 
        return 1 + search(node->left, id, value);
    }else{ // its on the right
        return 1 + search(node->right, id, value);
    }
} 

// Helper function for in-order traversal
void BSTStringStack::printInOrder(BSTNode* node) const{
    if (node){
        printInOrder(node->left);
        cout <<"ID: " << node->id << " | Stack: ";
        node->stack.printStack();
        printInOrder(node->right);
    }
}

// Helper function to delete all nodes
// this is gonna happen recursively with post order traversal
void BSTStringStack::clear(BSTNode* node){
    
    if(node){
        clear(node->left);
        clear(node->right);
        delete node;
    }

}
// Helper function to copy all nodes
BSTStringStack::BSTNode* BSTStringStack::copyTree(const BSTNode* root) {
    //nothing to copy
    if (root == nullptr) {
        return nullptr;
    }
    //a new node with the same id as the curr root node
    BSTNode* newNode = new BSTNode(root->id);
    newNode->stack = root->stack;//copy the root
    //using recursion to copy left and right subtrees of bst
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    // root of the new copy of the bst
    return newNode;
}

BSTStringStack& BSTStringStack::operator=(const BSTStringStack& rhs) {
    if(this != &rhs){ // this is to avoid assigning to itself
        clear(root);
        root= copyTree(rhs.root);
    }
    return *this;
}

int BSTStringStack::operator<<(const std::pair<int, std::string>& rhs) {
    int id = rhs.first;
    string value = rhs.second;
    int numOfNodesChecked = insert(root, id, value);  //add node to bst
    return numOfNodesChecked; //insert returns the number of nodes checked anyways
}

int BSTStringStack::operator>>(std::pair<int, std::string>& rhs) {
    int id = rhs.first;
    string value;
    int numOfNodesChecked = search(root, id, value);
    if (value.empty()) { // if so, the node not found
        rhs.second = "Node is not in BST!!!";
    } else {// the returned value is rhs second
        rhs.second = value;
    }
    return numOfNodesChecked;
}
