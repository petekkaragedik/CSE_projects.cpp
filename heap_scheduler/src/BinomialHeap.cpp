//Petek Karagedik 34042
#include "BinomialHeap.h"
using namespace std;

BinomialHeap::BinomialHeap() : head(nullptr) { //constructor
}
BinomialHeap::~BinomialHeap() { //destructor
    delete_all(head);
}
//recursively deleting
void BinomialHeap::delete_all(Node* node) {
    if (node == nullptr){
        return;
    }
    delete_all(node->sibling);  //delete siblings
    delete_all(node->child); // delete children
    delete node; //delete self
}
void BinomialHeap::insert(int task_id, int priority) { //new task
    Task t(task_id, priority);
    BinomialHeap temp_heap;
    temp_heap.head = new Node(t);
    temp_heap.task_map[task_id] = temp_heap.head;
    this -> merge_with(temp_heap); //merge into the heap
}
int BinomialHeap::extract_min() { //remove smallest
    if (!head){ 
        return -1; //if we have an empty 
    }
    Node* previous_minimum = nullptr;
    Node* min_node = head;
    Node* prev = nullptr;
    Node* curr = head;
    int min_priority = INT_MAX;
    while (curr) { //finding the min. node
        if (curr->task.priority < min_priority) {
            min_priority = curr -> task.priority;
            min_node = curr;
            previous_minimum = prev;
        }
        prev = curr;
        curr = curr -> sibling;
    }
    if (previous_minimum) {
        previous_minimum -> sibling = min_node -> sibling;
    }// removing that min. node
    else head = min_node -> sibling;
    Node* child = min_node -> child;
    Node* reverseChild = nullptr;
    while (child) { //reverse the children here
        Node* next = child -> sibling;
        child -> sibling = reverseChild;
        child -> parent = nullptr;
        reverseChild = child;
        child = next;
    }
    BinomialHeap new_heap;
    new_heap.head = reverseChild;
    this -> merge_with(new_heap); //merge back
    int task_id = min_node -> task.task_id;
    task_map.erase(task_id); // remove from the map
    delete min_node; //delete the minimum
    return task_id;
}
void BinomialHeap::decrease_key(int task_id, int new_priority) { //lower priority
    if (task_map.find(task_id) == task_map.end()){
        return; //couldnt find
    }
    Node* node = task_map[task_id];
    if (new_priority > node -> task.priority) {
        return; //invalid
    }
    node -> task.priority = new_priority; //updating the priority
    Node* y = node;
    Node* z = y -> parent;
    while (z && y -> task.priority < z -> task.priority) { //BUBBLE UP operation here
        swap(task_map[y -> task.task_id], task_map[z -> task.task_id]);
        swap(y -> task, z -> task);
        y = z;
        z = y -> parent;
    }
}
void BinomialHeap::merge_with(BinomialHeap& other) { //merge two heaps
    head = merge_root_lists(head, other.head); //combine the roots
    other.head = nullptr;
    for (auto& pair : other.task_map) { //updating the map for every pair in others task map
    //auto for simplicity here
        task_map[pair.first] = pair.second;
    }
    if (!head){
        return;
    }
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = head -> sibling;
    while (next) { //merge same degree
        if (curr -> degree != next -> degree || (next -> sibling && next -> sibling -> degree == curr -> degree)) {
            prev = curr;
            curr = next;
        } 
        else {
            if (curr -> task.priority <= next -> task.priority) {
                curr -> sibling = next -> sibling;
                link(next, curr); //link trees
            } else {
                if (prev) prev -> sibling = next;
                else head = next;
                link(curr, next);//link trees
                curr = next;
            }
        }
        next = curr -> sibling;
    }
}
void BinomialHeap::merge_with(Heap& other) { //for polymorphism, otherwise i got errors
    BinomialHeap* other_ptr = dynamic_cast<BinomialHeap*>(&other);
    if (other_ptr) merge_with(*other_ptr);
}
void BinomialHeap::link(Node* y, Node* z) { //make y a chilld  of z
    y -> parent = z;
    y -> sibling = z -> child;
    z -> child = y;
    z -> degree++; //increase its degree naturally
}
BinomialHeap::Node* BinomialHeap::merge_root_lists(Node* h1, Node* h2) {
    if (!h1){
        return h2;
    }
    if (!h2){
        return h1;
    }
    Node* head;
    if (h1 -> degree <= h2 -> degree) { //pick small degree
        head = h1;
        h1 = h1 -> sibling;
    } else {
        head = h2;
        h2 = h2 -> sibling;
    }
    Node* tail = head;

    while (h1 && h2) { //merge the rest
        if (h1 -> degree <= h2 -> degree) {
            tail -> sibling = h1;
            h1 = h1 -> sibling;
        } else {
            tail -> sibling = h2;
            h2 = h2 -> sibling;
        }
        tail = tail -> sibling;
    }
    if (h1) { // add the leftovers
    tail->sibling = h1;
    } else {
    tail->sibling = h2;
    }
    return head;
}
void BinomialHeap::print_heap() const {
    cout << "Heap:" << endl;
    Node* curr = head;
    while (curr) {
        print_tree(curr);
        curr = curr -> sibling;
    }
}
void BinomialHeap::print_tree(Node* node, int depth) const { //helper function for print heap
    if (!node){
        return;
    }
    cout << "TaskID: " << node -> task.task_id << ", Priority: " << node -> task.priority << endl;
    print_tree(node->child, depth + 1);
    print_tree(node->sibling, depth);
}
