
#ifndef PASS_H
#define PASS_H

#include <string>
using namespace std;

class PassManager {
private:
    string password;

public:
    PassManager();                     // �w�]�K�X�� "000000"
    bool changePassword();            // �i��K�X�ק�
    bool verifyPassword();            // ���ұK�X
};

#endif
