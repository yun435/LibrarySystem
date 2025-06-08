#include "Pass.h"
#include <iostream>
using namespace std;

PassManager::PassManager() {
    password = "000000";
}

bool PassManager::changePassword() {
    string newPass, confirmPass;
    cout << "Please change the default password (default is 000000):\n";
    cout << "Enter new password: ";
    getline(cin, newPass);
    cout << "Confirm new password: ";
    getline(cin, confirmPass);

    while (newPass != confirmPass) {
        cout << "Passwords do not match, please try again.\n";
        cout << "Enter new password: ";
        getline(cin, newPass);
        cout << "Confirm new password: ";
        getline(cin, confirmPass);
    }

    password = newPass;
    cout << "Password changed successfully. The program has remembered your new password.\n\n";
    return true;
}

bool PassManager::verifyPassword() {
    string inputPass;
    do {
        cout << "Please enter your password: ";
        getline(cin, inputPass);
        if (inputPass != password) {
            cout << "Incorrect password. Please try again.\n";
        }
    } while (inputPass != password);

    return true;
}
