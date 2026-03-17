//Petek Karagedik 34042
#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include "Heap.h"
#include "Task.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

class BinomialHeap : public Heap {
private:
    struct Node {
        Task task;
        int degree;
        Node* parent;
        Node* child;
        Node* sibling;

        Node(const Task& t)
            : task(t), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
    };

    Node* head;
    std::unordered_map<int, Node*> task_map;

    Node* merge_trees(Node* a, Node* b);
    Node* merge_root_lists(Node* h1, Node* h2);
    void link(Node* y, Node* z);
    void print_tree(Node* node, int depth = 0) const;
    void delete_all(Node* node);

public:
    BinomialHeap();
    ~BinomialHeap();

    void insert(int task_id, int priority) override;
    int extract_min() override;
    void decrease_key(int task_id, int new_priority) override;
    void merge_with(BinomialHeap& other);
    void merge_with(Heap& other) override;
    void print_heap() const override;
};

#endif