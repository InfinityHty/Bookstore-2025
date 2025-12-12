//
// Created by HTY on 2025/12/9.
//

#ifndef NEEDANALYSIS_MD_USER_H
#define NEEDANALYSIS_MD_USER_H
#include <cstring>
#include<string>
class User {
public:
    char UserID[35];
    char Username[35];
    char Password[35];
    int Privilege;
    User() {
        Privilege = 0;
    }
    User(std::string UserID,std::string User_name, std::string Password_,int privilege = 0): Privilege(privilege){
        int cnt = 0;
        memset(Username, 0, 35);
        memset(Password, 0, 35);
        while (User_name[cnt] != '\0') Username[cnt] = User_name[cnt],cnt++;
        cnt = 0;
        while (Password_[cnt] != '\0') Password[cnt] = Password_[cnt],cnt++;
    }
    void NewPassword(std::string new_password) {
        memset(Password, 0, 35);
        int cnt = 0;
        while (new_password[cnt] != '\0') Password[cnt] = new_password[cnt],cnt++;
    }
};
#endif //NEEDANALYSIS_MD_USER_H