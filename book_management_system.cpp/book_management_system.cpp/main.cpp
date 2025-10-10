#include <iostream>
#include <string>
#include "book.h"
#include <vector>
using namespace std;

vector <Book> info;

void sortBooks(vector<Book>& sortedInfo, long size) {
    for (int i = 1; i < size; ++i) {
        Book currentBook = sortedInfo[i];
        string authorOfBook = currentBook.getAuthor();
        int loc = i;

        while (loc > 0 && sortedInfo[loc - 1].getAuthor() > authorOfBook) {
            sortedInfo[loc] = sortedInfo[loc - 1];
            loc--;
        }
        sortedInfo[loc] = currentBook;
    }
}

int main() {
    
    while(true){
        string choice;
        cout << "Menu:" << endl;
        cout << "1. Add a new book" << endl;
        cout << "2. Display all books" << endl;
        cout << "3. Search for a book by title" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character left in the buffer
        
        if (choice == "1"){
            string titlee, authorr;
            int yearr, pagess;
            
            cout << "Enter title: ";
            getline(cin, titlee);

            cout << "Enter author: ";
            getline(cin, authorr);
            
            cout << "Enter year: ";
            cin >> yearr;
            
            cout << "Enter pages: ";
            cin >> pagess;
            cin.ignore(); // Clear the newline character left in the buffer
            
            Book infoofbook(titlee, authorr, yearr, pagess);
            info.push_back(infoofbook);
        }
        else if (choice == "2"){
            if (info.size() == 0){
                cout << "The book collection is currently empty. Please add some books first." << endl;
            }
            else{
                int i;
                long SIZE = info.size();
                sortBooks(info, SIZE);
                
                for (i = 0; i < SIZE; i++){
                    info[i].printInfo();
                }
            }
        }
        else if (choice == "3"){
            if (info.size() == 0){
                cout << "The book collection is currently empty. Please add some books first." << endl;
            } else {
                string search;
                bool found = false;
                cout << "Enter the title to search: ";
                getline(cin, search);

                for (size_t p = 0; p < info.size(); p++){
                    if (info[p].getTitle() == search){
                        found = true;
                        cout << "Title: " << info[p].getTitle() << endl;
                        cout << "Author: "<< info[p].getAuthor() << endl;
                        cout << "Year: "<< info[p].getYear() << endl;
                        cout << "Pages: "<< info[p].getPages() << endl;
                        break;
                    }
                }
                if (!found){
                    cout << "Book not found!" << endl;
                }
            }
        }
        else if (choice == "4"){
            cout << "Exiting..." << endl;
            break;
        }
        else{
            cout << "Option not valid." << endl;
        }
    }
    
    return 0;
}
