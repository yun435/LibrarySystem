#include "Book.h"

Book::Book(string t, string a, string d) {
    title = t;
    author = a;
    description = d;
    isBorrowed = false;
}

string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
string Book::getDescription() { return description; }
bool Book::checkBorrowed() { return isBorrowed; }
void Book::borrowBook() { isBorrowed = true; }
void Book::returnBook() { isBorrowed = false; }
