#include <iostream>
#include <string>
#include "BSTStringStack.h"
#include "StringStack.h"

int main() {
    //The BSTStringStack is a data structure that combines the properties of a Binary Search Tree (BST) 
    //and a Stack. Each node in this BST contains a id (which is an integer) and a linked-list based "stack" of strings (StringStack). 
    //This setup allows the BST to manage hierarchical relationships while each node can store multiple values in a stack format.
    BSTStringStack bstStringStack;

    // Inserting words into different BST nodes
    int nodesChecked; 

    //The operator << pushes a string to the stack of the BSTNode of a BSTStringStack object. 
    //  The id of the node is given as the first object in a pair (search for std::pair).
    //  The string to be pushed are given as the second object in a pair.
    //  If the BSTNode does not exist it needs to be created.
    //  The operator returns the number of nodes visited/checked in the BSTStringStack.
    nodesChecked = bstStringStack << std::make_pair(7, "CS204"); 
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(10, "world");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(15, "example");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(8, "is good");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(7, "to");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(10, "hello");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(8, "stack");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(18, "algorithm");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(1, "binary");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    nodesChecked = bstStringStack << std::make_pair(7, "welcome");
    std::cout << "Nodes checked during insertion: " << nodesChecked << std::endl;

    // Printing the BST InOrder order
    std::cout << "\nBST in-order traversal - the top appears first (i.e., printed from top to bottom):" << std::endl;
    bstStringStack.printInOrder();
    
    //The operator >> pops the string from the stack of a BSTNode inside a BSTStringStack object. 
    //  The id of the node is given as the first object in the pair operand.
    //  The string popped is outputted as the second object in the pair operand.
    //  If the BSTNode does not exist the string value is set to "Node is not in BST!!!".
    //  If the node is there but stack is empty, the string value is set to " Stack is empty!!!".
    //  The operator returns the number of nodes visited/checked in the BSTStringStack.
    std::cout << "Popping stack with id 10 three times from the first BST" << std::endl;
    std::pair<int, std::string> Q10(10, "");
    nodesChecked = bstStringStack >> Q10;
    std::cout << "Popped value: " << Q10.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;
    nodesChecked = bstStringStack >> Q10;
    std::cout << "Popped value: " << Q10.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;
    nodesChecked = bstStringStack >> Q10;
    std::cout << "Popped value: " << Q10.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;
    
    std::cout << "\nPopping stack with id -1 from the first BST" << std::endl;
    std::pair<int, std::string> QM1(-1, "");
    nodesChecked = bstStringStack >> QM1;
    std::cout << "Popped value: " << QM1.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;

    BSTStringStack bstStringStack2;
    bstStringStack2 = bstStringStack; //bstStringStack2 is assigned to bstStringStack.

    std::cout << "\nBST2 in-order traversal - the top appears first (i.e., printed from top to bottom):" << std::endl;
    bstStringStack2.printInOrder();

    std::cout << "Popping stack with id 10 from the second BST " << std::endl;
    nodesChecked = bstStringStack2 >> Q10;
    std::cout << "Popped value: " << Q10.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;

    std::cout << "\nPopping stack with id 7 four times from the second BST " << std::endl;
    std::pair<int, std::string> Q7(7, "");
    nodesChecked = bstStringStack2 >> Q7;
    std::cout << "Popped value: " << Q7.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;
    nodesChecked = bstStringStack2 >> Q7;
    std::cout << "Popped value: " << Q7.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;
    nodesChecked = bstStringStack2 >> Q7;
    std::cout << "Popped value: " << Q7.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;
    nodesChecked = bstStringStack2 >> Q7;
    std::cout << "Popped value: " << Q7.second << std::endl;
    std::cout << "Nodes checked during popping: " << nodesChecked << std::endl;

    std::cout << "\nBST in-order traversal - the top appears first (i.e., printed from top to bottom):" << std::endl;
    bstStringStack.printInOrder();

    std::cout << "BST2 in-order traversal - the top appears first (i.e., printed from top to bottom):" << std::endl;
    bstStringStack2.printInOrder();

    return 0;
}
