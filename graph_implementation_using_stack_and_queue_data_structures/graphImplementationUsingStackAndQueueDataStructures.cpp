//Petek Karagedik 34042
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct node {
    int data;
    node* next;
    node(int val){ 
        data = val;
        next = nullptr; 
    }  
};

// implementing a linked list class to form my dynamic stack and queue structures
class linked_list {
public:
    node* head;
    node* tail;
    linked_list() {
        head = nullptr;
        tail = nullptr;
    }

    void push_node_back(int val) {
        node* newNode = new node(val);
        if (!tail) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    int pop_node_front() { // popping the first node
        if (!head){ 
            return -1;
        }
        node* temp = head;
        int val = temp->data; 
        head = head->next;
        if (!head){
             tail = nullptr;
        }
        delete temp;
        return val;
    }
    int pop_node_from_back() { // popping the node at the end of the list
        if (!head){ // empty list, cannot pop
            return -1;
        }
        if (head == tail) {
            int val = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            return val;
        }
        node* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        int val = tail->data;
        delete tail;
        tail = temp;
        tail->next = nullptr;
        return val;
    }

    bool is_list_empty() {
        return head == nullptr;
    }
};

// struct for graph edges
struct edgeOfGraph {
    int firstVertex;
    int secondVertex;
    edgeOfGraph(int v1, int v2){
        firstVertex = v1;
        secondVertex = v2;
    }
};

//to help with edge sort
bool edgeCompare(const edgeOfGraph& edge1, const edgeOfGraph& edge2) {
    if (edge1.firstVertex != edge2.firstVertex) {
        return edge1.firstVertex < edge2.firstVertex;
    }
    return edge1.secondVertex < edge2.secondVertex;
}

//to represent graph and have the graph as an object
class Graph {
private:
    vector<linked_list> neighbors_list; // vector of linked lists that will hold the edges of every single node in graph
    int size;

public:
    Graph(int vertices) : size(vertices), neighbors_list(vertices) {} // constructor
    int size_of_graph() const {
        return size;
    }
    // adds a new edge to the graph
    void edgeAdder(int from, int to) {
        neighbors_list[from].push_node_back(to); // adds "to " to the neighbors of "from"
    }
//removes the edge of graph
    void edgeRemover(int from, int to) {
        linked_list& list_of_froms_neighbors = neighbors_list[from]; // reference bc. we need to alter the original and we shouldnt deal with a copy
        node* temporary = list_of_froms_neighbors.head;
        node* previous = nullptr; //and previous to null (previous of temporary)
        
        while (temporary && temporary->data != to) {
            previous = temporary;
            temporary = temporary->next;
        } 
        if (temporary) { // node found
            if (previous) { // for ex. we want to skip 2: 1 -> 2 -> 3 in here we wanna make 1 -> 3
                previous->next = temporary->next; // connecting 1 to 3 in example
            } else { // temporary is head so we make head temporary -> next
                list_of_froms_neighbors.head = temporary->next;
            }
            
            if (!list_of_froms_neighbors.head) {
                list_of_froms_neighbors.tail = nullptr;
            }
            
            delete temporary;
        }
    }
// chekcs if edge exists
    bool doesEdgeExist(int from, int to) {
        node* nodeToCheck = neighbors_list[from].head;
        while (nodeToCheck) {
            if (nodeToCheck -> data == to){
                return true;
            }
            nodeToCheck = nodeToCheck -> next;
        }
        return false;
    }

    void graphDisplayer() {
        for (int i = 0; i < size; ++i) {
            cout << i << " ->  ";
            vector<int> neighbors;//a vector to keep neigbors of one node : i
            node* temp_node = neighbors_list[i].head;
            while (temp_node) {
                neighbors.push_back(temp_node->data);
                temp_node = temp_node->next;
            }
        // we want to remove duplicates
            vector<int> unique_neighbors;
            for (int j = 0; j < neighbors.size(); j++) {
                bool flag = false; // our flag
                for (int k = 0; k < unique_neighbors.size(); k++) {
                    if (neighbors[j] == unique_neighbors[k]) {
                        flag = true; // neighbor is in vector: duplicate!
                        break;
                    }
                }
                if (!flag) {
                    unique_neighbors.push_back(neighbors[j]); // add it as unique
                }
            }

            // sorting vector cleaned from duplicates
            for (int j = 0; j < unique_neighbors.size(); ++j) {
                for (int k = j + 1; k < unique_neighbors.size(); ++k) {
                    if (unique_neighbors[j] > unique_neighbors[k]) {
                        //not ordered, you have to swap places
                        int dummypass = unique_neighbors[j];
                        unique_neighbors[j] = unique_neighbors[k];
                        unique_neighbors[k] = dummypass;
                    }
                }
            }
            for (int j = 0; j < neighbors.size(); ++j) {
                cout << neighbors[j];
                if (j < neighbors.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }

    void BreadthFirstSearch(int starting_vertex) {
        vector<bool> visited_nodes(size, false); // a vector of boolean variables to mark the nodes visited
        linked_list queue;
        queue.push_node_back(starting_vertex); //pushing the starting value to the back of the queue
        visited_nodes[starting_vertex] = true;// and then marking the start as marked so that we dont get confused

        while (!queue.is_list_empty()) {// as long as the queue is not empty
            int curr_node = queue.pop_node_front(); // popping each node starting from front and assigning their values to curr_node
            cout << curr_node << " ";
            node * temp = neighbors_list[curr_node].head;
            while (temp) {
                if (!visited_nodes[temp->data]) { // if that neighbor has not been visited before
                    queue.push_node_back(temp->data); // push it to the queue
                    visited_nodes[temp->data] = true; // mark it as visited
                }
                temp = temp->next; //move forward to next neighbor
            }
        }
    }

    void DepthFirstSearch(int starting_vertex) {
        vector<bool> visited_nodes(size, false); // same logic as bfs above
        linked_list stack;
        stack.push_node_back(starting_vertex); // first node added to stack

        while (!stack.is_list_empty()) { // as long as not empty
            int curr_node = stack.pop_node_from_back(); // same logic, iterating over them
            if (!visited_nodes[curr_node]) { // if unmarked
                cout << curr_node << " ";
                visited_nodes[curr_node] = true; //mark
                node* temp = neighbors_list[curr_node].head; // get head of neighbors
                while (temp) { //traverse all neighbors
                    if (!visited_nodes[temp->data]) { //if not visited
                        stack.push_node_back(temp->data); // add to stack
                    }
                    temp = temp->next;//move to next neighbor
                }
            }
        }
    }
};
int printSelectionMenuAndReturnChoice() {
    cout << "1. Add an edge\n";
    cout << "2. Remove an edge\n";
    cout << "3. Display the graph\n";
    cout << "4. Depth-First Search\n";
    cout << "5. Breadth-First Search\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    string inputFileName;
    cout << "Enter the input file name: ";
    cin >> inputFileName;

    ifstream inputFile(inputFileName);
    while (!inputFile) {
        cout << "Could not open the file " << inputFileName << endl;
        cout << "Enter the input file name: ";
        cin >> inputFileName;
        inputFile.open(inputFileName);
    }

    vector<string> invalidLineVector;
    string readALine;
    bool isDuplicate = false;
    vector<edgeOfGraph> uniqueEdgesVectorToUse;
    //elimination loop
    while (getline(inputFile, readALine)) {
        istringstream iss(readALine);
        int x, y;
         isDuplicate = false;
        if (!(iss >> x >> y) || x < 0 || y < 0 || (iss.rdbuf()->in_avail() != 0)) { //in_avail() checks if any avaliable input in the stream
            invalidLineVector.push_back(readALine);
            continue; // so it doesnt do next line and move to next iteration
        }else{
            for (int i = 0; i < uniqueEdgesVectorToUse.size(); i++) {
                if (uniqueEdgesVectorToUse[i].firstVertex != x ||
                    uniqueEdgesVectorToUse[i].secondVertex != y) {
                }
                else{
                    isDuplicate = true;
                }
    }
        if(isDuplicate){
            invalidLineVector.push_back(to_string(x) + " " + to_string(y));
        }
        else{
            uniqueEdgesVectorToUse.push_back(edgeOfGraph(x,y));
        }
        }
    }
    sort(uniqueEdgesVectorToUse.begin(), uniqueEdgesVectorToUse.end(), edgeCompare); //from algorithm library to sort edges
    inputFile.close();

    if (!invalidLineVector.empty()) {
        cout << "These edges are illegal or repeated:" << endl;
        for (int i = 0; i < invalidLineVector.size(); ++i) {
            cout << invalidLineVector[i] << endl;
        }
    }else{
        cout << "There are no edges that are illegal or empty.";
    }
//finding # of nodes
    int max_vertex = 0;
    for (int i = 0; i < uniqueEdgesVectorToUse.size(); i++) {
        if (uniqueEdgesVectorToUse[i].firstVertex > max_vertex) {
            max_vertex = uniqueEdgesVectorToUse[i].firstVertex;
        }
        if (uniqueEdgesVectorToUse[i].secondVertex > max_vertex) {
            max_vertex = uniqueEdgesVectorToUse[i].secondVertex;
        }
    }
    Graph graph(max_vertex + 1); // +1 bc. nodes start from 0

//add each edge from vector to graph
    for (int i = 0; i < uniqueEdgesVectorToUse.size(); i++) {
        graph.edgeAdder(uniqueEdgesVectorToUse[i].firstVertex, uniqueEdgesVectorToUse[i].secondVertex);
    }
    int choice;
    cout << "Graph Menu:\n"; // only at the start
    while (true) {
        choice = printSelectionMenuAndReturnChoice();
        while (choice < 1 || choice > 6) {
            cout << "The entered number is not valid! Make another choice: ";
            cin >> choice;
        }
        if (choice == 1) {
            int from, to;
            cout << "Enter two nodes as two endings of the new edge ";
            while (true) {
                cin >> from >> to;
                if (from >= 0 && to >= 0 && from < graph.size_of_graph() && to < graph.size_of_graph()) {
                    graph.edgeAdder(from, to);
                    cout << "The new edge is added." << endl;
                    break;
                } else {
                    cout << "The entered node IDs are out or range, Enter two other IDs:" << endl;
                }
            }
        } else if (choice == 2) {
            int from, to;
            cout << "Enter two nodes as two endings of the edge ";
            while (true) {
                cin >> from >> to;
                if (from >= 0 && to >= 0 && from < graph.size_of_graph() && to < graph.size_of_graph()) {
                    if (graph.doesEdgeExist(from, to)) {
                        graph.edgeRemover(from, to);
                        cout << "The entered edge is removed." << endl;
                        break;
                    } else {
                        cout << "The entered edge does not exist in the graph! Enter two other node IDs:" << endl;
                    }
                } else {
                    cout << "The entered node IDs are out or range, Enter two other IDs:" << endl;
                }
            }
        } else if (choice == 3) {
            cout << "The graph has this structure: " << endl;
            graph.graphDisplayer();
        } else if (choice == 4) {
            int startNode;
            cout << "Please enter starting node: ";
            while (true) {
                cin >> startNode;
                if (startNode >= 0 && startNode < graph.size_of_graph()) {
                    cout << "Depth-First Search starting from node " << startNode << ": ";
                    graph.DepthFirstSearch(startNode);
                    cout << endl;
                    break;
                } else {
                    cout << "The entered node number is out of range, enter a valid one: " << endl;
                }
            }
        } else if (choice == 5) {
            int startNode;
            cout << "Please enter starting node: ";
            while (true) {
                cin >> startNode;
                if (startNode >= 0 && startNode < graph.size_of_graph()) {
                    cout << "Breadth-first search starting from node " << startNode << ": ";
                    graph.BreadthFirstSearch(startNode);
                    cout << endl;
                    break;
                } else {
                    cout << "The entered node number is out of range, enter a valid one: " << endl;
                }
            }
        } else if (choice == 6) {
            cout << "Program Exiting..." << endl;
            break;
        }
}
    return 0;
}
