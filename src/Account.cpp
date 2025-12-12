//
// Created by HTY on 2025/12/9.
//
#include "../include/Account.h"
#include "../include/DataMap.h"
#include "../include/User.h"
#include<string>
#include<cstring>
Database<char[35],User,1000> db;
bool Account::ValidCheck(std::string& s) {
    if (s.size() > 30) return false;
    else {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < 'A' || s[i] > 'Z') {
                if (s[i] < 'a' || s[i] > 'z') {
                    if (s[i] < '0' || s[i] > '9') {
                        if (s[i] != '_') return false;
                    }
                }
            }
        }
        return true;
    }
}
void Account::AddNewAccount(User& user) {
    db.Insert(user.UserID,user);
}
void Account::LogIn(User user) {
    LogInStack.push_back(user);
    current_user = user;
    login_number++;
}
User Account::GetUser(std::string id) {
    char tmp_id[35];
    memset(tmp_id,0,35);
    strcpy(tmp_id, id.c_str());
    return db.GetValue(tmp_id);
}
bool Account::LogOut() {
    if (LogInStack.empty()) return false;
    else {
        LogInStack.pop_back();
        current_user = LogInStack.back();
        return true;
    }
}
bool Account::FindUser(std::string id) {
    char tmp_id[35];
    memset(tmp_id,0,35);
    strcpy(tmp_id, id.c_str());
    return db.CheckExist(tmp_id);
}
User Account::CurrentUser() {
    return LogInStack.back();
}
bool Account::HasLogIn(std::string id) {
    for (auto it = LogInStack.begin(); it != LogInStack.end(); it++) {
        if (it->UserID == id) return true;
    }
    return false;
}
void Account::ChangeInfo(User user) {

}
void Account::DeleteAccount(User user) {
    db.Delete(user.UserID,user);
}