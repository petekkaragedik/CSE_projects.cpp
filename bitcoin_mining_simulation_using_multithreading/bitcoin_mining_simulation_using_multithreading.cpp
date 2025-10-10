#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <mutex>
#include <vector>
#include <atomic>
using namespace std;

typedef unsigned int uint;

struct transaction {
    uint current; // current transaction ID
    uint prev; // hash of previous transaction
    uint rand; // random solution number
    thread::id threads_id;
    transaction* next; // pointer to the next transaction in the chain

    // Constructor
    transaction(uint curr, uint prev, uint rand, thread::id threadID, transaction* nxt = nullptr)
        : current(curr), prev(prev), rand(rand), threads_id(threadID), next(nxt) {}
};

struct transactionChain {
	//linkedlist of transactions - can add member functions like add
    transaction* head;

    transactionChain() : head(nullptr) {}

    void add(transaction* new_transaction) {
        if (!head) {
            head = new_transaction;
        } else {
            transaction* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new_transaction;
        }
    }
};

uint hashTransaction(transaction tran) {
    uint result = (tran.current << 16) ^ (tran.prev << 8) ^ (tran.rand << 1);
    std::hash<uint> uint_hash;
    return uint_hash(result);
}

bool transactionValidator(transactionChain& tChain, uint threshold) {
    transaction* temp = tChain.head->next;
    bool valid = true;

    while (temp != nullptr) {
        if (hashTransaction(*temp) > threshold)
            valid = false;
        temp = temp->next;
    }
    return valid;
}

void mine(transactionChain* chain, const vector<uint>* transaction_ids, uint threshold, mutex* mtx, atomic<int>* curr_trans_index, bool* starting_flag) {
    uint bitcoins = 0; // Private counter for bitcoins mined by this thread
    srand((hash<thread::id>()(this_thread::get_id())) ^ 2 % 10000);

    while (!(*starting_flag)) {
        this_thread::yield(); //yield lets other threads to execute while waiting
    }
	//start mining
    while (true) {
        int idx;
        {
            lock_guard<mutex> lock(*mtx);
            if (*curr_trans_index >= transaction_ids->size()) { //if this is true, all transactions are processed and therefore breaks
                break;
            }
            idx = (*curr_trans_index);
        }

        uint randomValue = rand();
        transaction* previousTransaction = chain->head;
        while (previousTransaction && previousTransaction->next) { //find the last transaction in the chain
            previousTransaction = previousTransaction->next;
        }
		uint previousHash; //if there is a previous transaction, its hash is the previous hash
		if(previousTransaction){
			previousHash = previousTransaction -> prev;
		}
		else{
			previousHash = 0;
		}
		//create a temporary transaction
        uint valueOfHash = hashTransaction(transaction((*transaction_ids)[idx], previousHash, randomValue, this_thread::get_id()));
        //is the transaction valid?
		if (valueOfHash < threshold) {
            transaction* new_transaction = new transaction((*transaction_ids)[idx], previousHash, randomValue, this_thread::get_id());

            {
                lock_guard<mutex> lock(*mtx); //locks the access to the chain
                if (*curr_trans_index == idx) {
                    chain->add(new_transaction);
                    (*curr_trans_index)++;
                    bitcoins++;
                }
            }
        }
    }

    {
		// to avoid mixed messages, maintain reach to cout
        lock_guard<mutex> lock(*mtx);
        cout << "Thread " << this_thread::get_id() << " has " << bitcoins << " bitcoin(s)" << endl;
    }
}

int main() {
    int miners;
    uint difficulty;
    string filename;

    cout << "Enter difficulty level (1-10): ";
    cin >> difficulty;

    uint threshold = (1 << (31 - difficulty));
    cout << "Threshold: " << threshold << endl;

    cout << "Enter the filename of the input file: ";
    cin >> filename;

    cout << "Enter the number of miners: ";
    cin >> miners;

    cout << "----------START---------" << endl;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return -1;
    }

    int number_of_transactions;
    file >> number_of_transactions;
    vector<uint> transaction_ids(number_of_transactions);
    for (int i = 0; i < number_of_transactions; i++) {
        file >> transaction_ids[i];
    }
    file.close();

	//to represent the blockchain
    transactionChain chain;
    transaction* mainTransaction = new transaction(0, 0, 0, this_thread::get_id(), nullptr);
    chain.add(mainTransaction);

	//shared variables
    mutex mtx;
    atomic<int> curr_trans_idx(0);
    bool starting_flag = false;

    vector<thread> threads;
    for (int i = 0; i < miners; ++i) {
	threads.push_back(thread(mine, &chain, &transaction_ids, threshold, &mtx, &curr_trans_idx, &starting_flag));
	} 
	
    starting_flag = true;

	//joins all threads to make sure that the main program waits for the threads' completion
	for (int i = 0; i < threads.size(); ++i) {
		threads[i].join();
	}
	//validate
    if (transactionValidator(chain, threshold)) {
        cout << "The transaction is valid." << endl;
    } else {
        cout << "The transaction is invalid." << endl;
    }

    return 0;
}