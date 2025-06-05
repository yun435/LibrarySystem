#ifndef PASS_H
#define PASS_H

#include <string>
using namespace std;

class PassManager {
private:
    string password;

public:
    PassManager();                     // 預設密碼為 "000000"
    bool changePassword();            // 進行密碼修改
    bool verifyPassword();            // 驗證密碼
};

#endif
