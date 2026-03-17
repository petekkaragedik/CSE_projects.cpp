//Petek Karagedik 34042
#ifndef DARY_HEAP_H
#define DARY_HEAP_H
#include "Heap.h"
#include "Task.h"
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class DaryHeap : public Heap {
private:
    vector<Task> heap;
    unordered_map<int, int> task_index;
    int d;

    void bubble_up(int idx);
    void bubble_down(int idx);
    int parent(int i) const { return (i - 1) / d; }
    int kthChild(int i, int k) const {  //returns the kth child
        return d * i + k; 
    }

public:
    DaryHeap(int d);

    void insert(int task_id, int priority) override;
    int extract_min() override;
    void decrease_key(int task_id, int new_priority) override;
    void merge_with(DaryHeap& other);
    void merge_with(Heap& other) override;
    void print_heap() const override;
};

#endif