//Petek Karagedik 34042
#include <iostream>
#include "Heap.h"
using namespace std;

void parse_file(const string& filename, Heap*& heap_ptr);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./heap_scheduler <input_file>" << endl;
        return 1;
    }

    Heap* heap = nullptr;
    parse_file(argv[1], heap);
    delete heap;
    return 0;
}