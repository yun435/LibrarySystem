#include "Pass.h"
#include <iostream>
using namespace std;

PassManager::PassManager() {
    password = "000000";
}

bool PassManager::changePassword() {
    string newPass, confirmPass;
    cout << "�Эק��l�K�X�]�w�]�� 000000�^�G\n";
    cout << "�ק�K�X�G";
    getline(cin, newPass);
    cout << "�A���T�{�s�K�X�G";
    getline(cin, confirmPass);

    while (newPass != confirmPass) {
        cout << "�⦸�K�X���@�P�A�Э��s��J�C\n";
        cout << "�ק�K�X�G";
        getline(cin, newPass);
        cout << "�A���T�{�s�K�X�G";
        getline(cin, confirmPass);
    }

    password = newPass;
    cout << "�K�X�ק令�\�A�{���w�O��z���s�K�X�C\n\n";
    return true;
}

bool PassManager::verifyPassword() {
    string inputPass;
    do {
        cout << "�п�J�K�X�G";
        getline(cin, inputPass);
        if (inputPass != password) {
            cout << "�K�X���~�A�Э��s��J�C\n";
        }
    } while (inputPass != password);

    return true;
}
//�h���D���D�[����