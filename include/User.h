//
// Created by HTY on 2025/12/9.
//

#ifndef NEEDANALYSIS_MD_USER_H
#define NEEDANALYSIS_MD_USER_H
#include <cstring>
#include<string>
#include<array>
class User {
public:
    std::array<char,30> UserID{};
    std::array<char,30> Username{};
    std::array<char,30> Password{};
    int Privilege;
    User() {
        Privilege = 0;
    }
    User(std::string User_ID,std::string User_name, std::string Password_,int privilege = 0): Privilege(privilege){
        int cnt = 0;
        while (User_ID[cnt] != '\0') UserID[cnt] = User_ID[cnt],cnt++;
        cnt = 0;
        while (User_name[cnt] != '\0') Username[cnt] = User_name[cnt],cnt++;
        cnt = 0;
        while (Password_[cnt] != '\0') Password[cnt] = Password_[cnt],cnt++;
    }
    void NewPassword(std::string new_password) {
        int cnt = 0;
        for (int i = 0; i < 30; i++) Password[i] = '\0';
        while (new_password[cnt] != '\0') Password[cnt] = new_password[cnt],cnt++;
    }
    bool operator==(const User& other) const{
        return UserID == other.UserID;
    }
    bool operator <(const User& other) const{
        return UserID < other.UserID;
    }
    bool operator >(const User& other) const{
        return UserID > other.UserID;
    }
    bool operator <=(const User& other) const{
        return UserID <= other.UserID;
    }
    bool operator >=(const User& other) const{
        return UserID >= other.UserID;
    }
    bool operator !=(const User& other) const{
        return UserID != other.UserID;
    }
};
#endif //NEEDANALYSIS_MD_USER_H