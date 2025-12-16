//
// Created by HTY on 2025/12/9.
//
// 管理账户信息，实现文件存储和读写
#ifndef NEEDANALYSIS_MD_ACCOUNT_H
#define NEEDANALYSIS_MD_ACCOUNT_H
#include<string>
#include<vector>
#include "User.h"
class User;
class Book;
class Account {
public:
    void Initialize();
    bool ValidCheck(std::string& s);// 检查UserID，Password是否合法
    void AddNewAccount(User& user);
    void LogIn(User user);
    void ChangeInfo(User user);
    User GetUser(std::string id);
    bool LogOut();
    bool FindUser(std::string id);
    bool HasLogIn(std::string name);
    int GetLoginNumber() const {
        return login_number;
    }
    void DeleteAccount(User user);
    User CurrentUser();
private:
    std::string filename = "account.txt";
    std::string index_filename = "index_account.txt";
    std::vector<User> LogInStack;
    int login_number = 0;
    User current_user;
};
#endif //NEEDANALYSIS_MD_ACCOUNT_H