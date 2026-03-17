//Petek Karagedik 34042
#include <fstream>
#include <sstream>
#include "BinomialHeap.h"
#include "DaryHeap.h"
//just like the way we learned in 
void parse_file(const string& filename, Heap*& heap_ptr) {
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string command;
        iss >> command;
        if (command == "HEAP_TYPE") {
            string type;
            iss >> type;
            delete heap_ptr;
            if (type == "BINOMIAL") {
                heap_ptr = new BinomialHeap();
            } else if (type == "DARY") {
                int d;
                iss >> d;
                heap_ptr = new DaryHeap(d);
            }
        } 
        else if (command == "INSERT") {
            int id, pr;
            iss >> id >> pr;
            heap_ptr -> insert(id, pr);
        } 
        else if (command == "DECREASE_KEY") {
            int id, pr;
            iss >> id >> pr;
            heap_ptr -> decrease_key(id, pr);
        } 
        else if (command == "EXTRACT_MIN") {
            int result = heap_ptr -> extract_min();
            cout << "Extracted: " << result << endl;
        } 
        else if (command == "MERGE") {
            string merge_file;
            iss >> merge_file;
            Heap* other = nullptr;
            parse_file(merge_file, other);
            heap_ptr -> merge_with(*other);
            delete other;
        } 
        else if (command == "PRINT") {
            heap_ptr -> print_heap();
        }
    }
}