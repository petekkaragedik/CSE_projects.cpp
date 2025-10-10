#include <iostream>
#include <string>
#include "book.h"
using namespace std;

// Constructor to initialize all attributes of the Book class
Book::Book(const string& titlee, const string& authorr, int yearr, int pagess)
{   title = titlee;
    author = authorr;
    year = yearr;
    pages = pagess;
}

// Getter methods to access the private attributes
string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

int Book::getPages() const {
    return pages;
}

// Method to print all information about the book
void Book::printInfo() const{
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Year: " << year << endl;
    cout << "Pages: " << pages << endl;
    cout << "-------------------" << endl;
    
}   // Prints the title, author, year, and pages of the book

