//Petek Karagedik 34042
//!!!this has some problems, i had no chance to debug, binary heap works just well though
#include "DaryHeap.h"

DaryHeap::DaryHeap(int d_) : d(d_){
} //coonstructor
void DaryHeap::insert(int task_id, int priority) { // add a task
    Task t(task_id, priority);
    heap.push_back(t); //add to end
    int idx = heap.size() - 1; //get the index
    task_index[task_id] = idx; //update the map
    bubble_up(idx); //fix the heap
}
void DaryHeap::bubble_up(int idx) { //move up
    while (idx > 0 && heap[idx].priority < heap[parent(idx)].priority) {
        swap(task_index[heap[idx].task_id], task_index[heap[parent(idx)].task_id]);
        swap(heap[idx], heap[parent(idx)]);
        idx = parent(idx); //go up
    }
}
int DaryHeap::extract_min(){ //remove min
    if (heap.empty()){
        return -1; //check if empty
    } 
    int min_task_id = heap[0].task_id;
    task_index.erase(min_task_id); //remove from map
    heap[0] = heap.back(); //replace the root
    task_index[heap[0].task_id] = 0; //update map
    heap.pop_back(); //remove last
    bubble_down(0); // fix heap (order property)
    return min_task_id;
}
void DaryHeap::bubble_down(int idx){ //move down
    while (true) {
        int smallest = idx; //assume current
        for (int i = 1; i <= d; i++) { //check the children
            int child = kthChild(idx, i);
            if (child < heap.size() && heap[child].priority < heap[smallest].priority) {
                smallest = child; //updating the smallest
            }
        }
        if (smallest == idx) {
            break; //done
        }
        swap(task_index[heap[idx].task_id], task_index[heap[smallest].task_id]);
        swap(heap[idx], heap[smallest]);
        idx = smallest; //move down
    }
}
//lower priority
void DaryHeap::decrease_key(int task_id, int new_priority) { //merge the heaps
    if (task_index.find(task_id) == task_index.end()){
        return; //couldnt find
    }
    int idx = task_index[task_id];
    if (new_priority > heap[idx].priority){
        return; //invalid
    }
    heap[idx].priority = new_priority; //update
    bubble_up(idx); //fix the heap (order)
}
void DaryHeap::merge_with(DaryHeap& other) {
    for (auto& task : other.heap) {
        insert(task.task_id, task.priority); //insert all
    }
    other.heap.clear(); //clear other
    other.task_index.clear(); //clear map
}
//merge heaps but polymorphism version, got errors when i didnt do this
void DaryHeap::merge_with(Heap& other) {
    DaryHeap* otherPtr = dynamic_cast<DaryHeap*>(&other);
    if (otherPtr){
         merge_with(*otherPtr); //if same type
    }
}
void DaryHeap::print_heap() const{
    cout << "Heap:" << endl;
    for (const auto& task : heap) {
        cout << "TaskID: " << task.task_id << ", Priority: " << task.priority << endl;
    }
}