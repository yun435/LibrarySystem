#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"
#include "Pass.h"
using namespace std;

struct Category {
    string name;
    vector<Book*> books;
};

vector<Category> loadBooksByCategory(const string& filename) {
    vector<Category> categories;
    ifstream file(filename);
    string line;
    Category currentCategory;

    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '[' && line.back() == ']') {
            if (!currentCategory.name.empty()) categories.push_back(currentCategory);
            currentCategory = Category();
            currentCategory.name = line.substr(1, line.length() - 2);
        }
        else {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos) {
                string title = line.substr(0, pos1);
                string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string desc = line.substr(pos2 + 1);
                currentCategory.books.push_back(new Book(title, author, desc));
            }
        }
    }
    if (!currentCategory.name.empty()) categories.push_back(currentCategory);
    file.close();
    return categories;
}

bool isValidCardNumber(const string& cardNumber) {
    return cardNumber.length() == 8 && (cardNumber[0] == '1' || cardNumber[0] == '0');
}

int main() {

    PassManager pass;
    cout << "Please enter the initial password to change it.\n";
    if (pass.verifyPassword()) {
        pass.changePassword();
    }

    string name, cardNumber;
    cout << "Enter your name: ";
    getline(cin, name);

    pass.verifyPassword();

    cout << "Enter your 8-digit library card number (Starts with 1 for VIP, 0 for regular): ";
    getline(cin, cardNumber);

    if (!isValidCardNumber(cardNumber)) {
        cout << "Invalid card number. Program will exit.\n";
        return 1;
    }

    bool isVIP = (cardNumber[0] == '1');
    Member* user = new Member(name, stoi(cardNumber), isVIP);

    vector<Category> categories = loadBooksByCategory("book.txt");

    char choice;
main_menu:
    do {
        cout << "\nMenu:\n1. Borrow Book\n2. Return Book\n3. Show Borrowed Books\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == '1') {
            cout << endl;
            for (int i = 0; i < categories.size(); i++) {
                cout << i + 1 << ". " << categories[i].name << endl;
            }
            int catIndex;
            cout << "Select category: ";
            cin >> catIndex; cin.ignore();
            if (catIndex < 1 || catIndex > categories.size()) continue;

            Category& cat = categories[catIndex - 1];
            while (true) {
                cout << "\nBooks in " << cat.name << " category:\n";
                for (int j = 0; j < cat.books.size(); j++) {
                    cout << j + 1 << ". " << cat.books[j]->getTitle() << " ("
                        << (cat.books[j]->checkBorrowed() ? "Borrowed" : "Available") << ")" << endl;
                }
                int bookIndex;
                cout << "Select book number: ";
                cin >> bookIndex; cin.ignore();
                if (bookIndex < 1 || bookIndex > cat.books.size()) continue;

                Book* selected = cat.books[bookIndex - 1];
                cout << "\nTitle: " << selected->getTitle() << endl;
                cout << "Author: " << selected->getAuthor() << endl;
                cout << "Description: " << selected->getDescription() << endl;

                cout << "\n1. Borrow\n2. Go Back\n3. Return to Category Menu\nChoice: ";
                int act;
                cin >> act; cin.ignore();
                if (act == 1) {
                    if (user->borrowOneBook(selected)) {
                        cout << "Book borrowed successfully!\n";
                    }
                    else {
                        cout << "Borrowing failed.\n";
                        goto main_menu;
                    }
                    break;
                }
                else if (act == 2) {
                    continue;
                }
                else if (act == 3) {
                    break;
                }
            }
        }
        else if (choice == '2') {
            user->displayBorrowedBooks();
            int idx;
            cout << "Enter the number of the book to return: ";
            cin >> idx;
            user->returnOneBook(idx - 1);
        }
        else if (choice == '3') {
            user->displayBorrowedBooks();
        }
        else if (choice == '4') {
            break;
        }
        else {
            cout << "Invalid selection!\n";
        }
    } while (choice != '4');

    for (Category& cat : categories)
        for (Book* b : cat.books) delete b;
    delete user;
    return 0;
}
