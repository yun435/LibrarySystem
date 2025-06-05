#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"
#include"Pass.h"
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
        } else {
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
    system("chcp 65001 > nul");

    PassManager pass;
    // 第一次啟動修改密碼
    cout << "第一次啟動請輸入初始密碼進行修改。\n";
    if (pass.verifyPassword()) {
        pass.changePassword();  // 修改為新密碼
    } 

    string name, cardNumber;
    cout << "請輸入姓名：";
    getline(cin, name);

    pass.verifyPassword();
    
    cout << "請輸入8碼借書證卡號（開頭1為VIP, 0為一般）：";
    getline(cin, cardNumber);

    if (!isValidCardNumber(cardNumber)) {
        cout << "無效卡號，程式結束。\n";
        return 1;
    }
    bool isVIP = (cardNumber[0] == '1');
    Member* user = new Member(name, stoi(cardNumber), isVIP);

    vector<Category> categories = loadBooksByCategory("book.txt");

    char choice;
main_menu:
    do {
        cout << "\n選單：\n1. 借書\n2. 還書\n3. 顯示借閱書籍\n4. 離開\n選擇：";
        cin >> choice;
        cin.ignore();

        if (choice == '1') {
            cout << endl;
            for (int i = 0; i < categories.size(); i++) {
                cout << i + 1 << ". " << categories[i].name << endl;
            }
            int catIndex;
            cout << "選擇類別：";
            cin >> catIndex; cin.ignore();
            if (catIndex < 1 || catIndex > categories.size()) continue;

            Category& cat = categories[catIndex - 1];
            while (true) {
                cout << "\n" << cat.name << " 類別書籍：" << endl;
                for (int j = 0; j < cat.books.size(); j++) {
                    cout << j + 1 << ". " << cat.books[j]->getTitle() << " ("
                         << (cat.books[j]->checkBorrowed() ? "已借出" : "可借") << ")" << endl;
                }
                int bookIndex;
                cout << "選擇書籍編號：";
                cin >> bookIndex; cin.ignore();
                if (bookIndex < 1 || bookIndex > cat.books.size()) continue;

                Book* selected = cat.books[bookIndex - 1];
                cout << "\n書名：" << selected->getTitle() << endl;
                cout << "作者：" << selected->getAuthor() << endl;
                cout << "簡介：" << selected->getDescription() << endl;

                cout << "\n1. 借閱\n2. 返回上頁\n3. 返回類別選單\n選擇：";
                int act;
                cin >> act; cin.ignore();
                if (act == 1) {
                    if (user->borrowOneBook(selected)) {
                        cout << "成功借閱！" << endl;
                    } else {
                        cout << "借閱失敗！\n";
                        goto main_menu;
                    }
                    break;
                } else if (act == 2) {
                    continue;
                } else if (act == 3) {
                    break;
                }
            }
        } else if (choice == '2') {
            user->displayBorrowedBooks();
            int idx;
            cout << "輸入要還書的編號：";
            cin >> idx;
            user->returnOneBook(idx - 1);
        } else if (choice == '3') {
            user->displayBorrowedBooks();
        } else if (choice == '4') {
            break;
        } else {
            cout << "無效選擇！\n";
        }
    } while (choice != '4');

    for (Category& cat : categories)
        for (Book* b : cat.books) delete b;
    delete user;
    return 0;
}
