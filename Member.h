#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include "Book.h"
using namespace std;

class Member {
private:
    string name;
    int memberId;
    bool isVIP;
    int borrowedBooks;
    Book** borrowedList;

public:
    Member(string n, int id, bool vip);
    ~Member();
    bool borrowOneBook(Book* book);
    void returnOneBook(int index);
    void displayBorrowedBooks();
};

#endif
