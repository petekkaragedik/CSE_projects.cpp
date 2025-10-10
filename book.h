#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

// The Book class represents a book with a title, author, publication year, and number of pages.
class Book {
private:
    // Attributes of the Book class
    string title;   // Title of the book
    string author;  // Author of the book
    int year;       // Year the book was published
    int pages;      // Number of pages in the book

public:
    // Constructor to initialize all attributes of the Book class
    Book(const string& title, const string& author, int year, int pages);

    // Getter methods to access the private attributes
    string getTitle() const;    // Returns the title of the book
    string getAuthor() const;   // Returns the author of the book
    int getYear() const;        // Returns the publication year of the book
    int getPages() const;       // Returns the number of pages in the book

    // Method to print all information about the book
    void printInfo() const;   // Prints the title, author, year, and pages of the book Display the book's information.
};

#endif // BOOK_H
