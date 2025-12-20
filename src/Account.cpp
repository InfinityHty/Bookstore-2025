//
// Created by HTY on 2025/12/9.
//
#include "../include/Account.h"
#include "../include/DataMap.h"
#include "../include/User.h"
#include<string>
#include<cstring>
Database<std::array<char,30>,User,1000> acc_db;
void Account::Initialize() {
    acc_db.Initialize(index_filename,filename);
}
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
    if (acc_db.CheckExist(user.UserID)) return;// root不重复插入
    acc_db.Insert(user.UserID,user);
    //std::cerr << db.CheckExist(user.UserID) << "\n";
}
void Account::LogIn(User user) {
    LogInStack.push_back(user);
    current_user = user;
    login_number++;
}
User Account::GetUser(std::string id) {
    std::array<char,30> user_id{};
    int cnt = 0;
    while (id[cnt] != '\0') user_id[cnt] = id[cnt],cnt++;
    return acc_db.GetValue(user_id);
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
    std::array<char,30> user_id{};
    int cnt = 0;
    while (id[cnt] != '\0') user_id[cnt] = id[cnt],cnt++;
    return acc_db.CheckExist(user_id);
}
User Account::CurrentUser() {
    return LogInStack.back();
}
bool Account::HasLogIn(std::string id) {
    std::array<char,30> user_id{};
    int cnt = 0;
    while (id[cnt] != '\0') user_id[cnt] = id[cnt],cnt++;
    for (auto it = LogInStack.begin(); it != LogInStack.end(); it++) {
        if (it->UserID == user_id) return true;
    }
    return false;
}
void Account::ChangeInfo(User user) {
    acc_db.ChangeInfo(user.UserID,user);
}
void Account::DeleteAccount(User user) {
    acc_db.Delete(user.UserID,user);
}