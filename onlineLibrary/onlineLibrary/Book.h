#pragma once
#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string description;
    bool isBorrowed;
public:
    Book(string t, string a, string d);
    string getTitle();
    string getAuthor();
    string getDescription();
    bool checkBorrowed();
    void borrowBook();
    void returnBook();
};

#endif
