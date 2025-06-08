#include "Pass.h"
#include <iostream>
using namespace std;

PassManager::PassManager() {
    password = "000000";
}

bool PassManager::changePassword() {
    string newPass, confirmPass;
    cout << "請修改初始密碼（預設為 000000）：\n";
    cout << "修改密碼：";
    getline(cin, newPass);
    cout << "再次確認新密碼：";
    getline(cin, confirmPass);

    while (newPass != confirmPass) {
        cout << "兩次密碼不一致，請重新輸入。\n";
        cout << "修改密碼：";
        getline(cin, newPass);
        cout << "再次確認新密碼：";
        getline(cin, confirmPass);
    }

    password = newPass;
    cout << "密碼修改成功，程式已記住您的新密碼。\n\n";
    return true;
}

bool PassManager::verifyPassword() {
    string inputPass;
    do {
        cout << "請輸入密碼：";
        getline(cin, inputPass);
        if (inputPass != password) {
            cout << "密碼錯誤，請重新輸入。\n";
        }
    } while (inputPass != password);

    return true;
}
//多選題解題加解釋