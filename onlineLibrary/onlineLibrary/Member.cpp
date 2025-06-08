#include "Member.h"
#include <iostream>
using namespace std;

Member::Member(string n, int id, bool vip) {
    name = n;
    memberId = id;
    isVIP = vip;
    borrowedBooks = 0;
    int maxBooks = isVIP ? 5 : 3;
    borrowedList = new Book * [maxBooks];
    for (int i = 0; i < maxBooks; i++) borrowedList[i] = nullptr;
}

Member::~Member() {
    delete[] borrowedList;
}

bool Member::borrowOneBook(Book* book) {
    int maxBooks = isVIP ? 5 : 3;
    if (borrowedBooks < maxBooks && !book->checkBorrowed()) {
        for (int i = 0; i < maxBooks; i++) {
            if (borrowedList[i] == nullptr) {
                borrowedList[i] = book;
                book->borrowBook();
                borrowedBooks++;
                return true;
            }
        }
    }
    return false;
}

void Member::returnOneBook(int index) {
    int maxBooks = isVIP ? 5 : 3;
    if (index >= 0 && index < maxBooks && borrowedList[index] != nullptr) {
        borrowedList[index]->returnBook();
        borrowedList[index] = nullptr;
        borrowedBooks--;
    }
}

void Member::displayBorrowedBooks() {
    cout << name << "'s borrowed books:\n";
    int maxBooks = isVIP ? 5 : 3;
    bool hasBooks = false;
    for (int i = 0; i < maxBooks; i++) {
        if (borrowedList[i] != nullptr) {
            cout << i + 1 << ". " << borrowedList[i]->getTitle()
                << " by " << borrowedList[i]->getAuthor() << endl;
            hasBooks = true;
        }
    }
    if (!hasBooks) cout << "(No borrowed books)\n";
}
