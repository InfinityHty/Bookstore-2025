//
// Created by HTY on 2025/12/9.
//
#include<iostream>
#include "../include/Account.h"
#include "../include/User.h"
#include<string>
#include<sstream>
#include<vector>
std::stringstream input;
int main() {
    User root_user("*","root","sjtu",7);
    Account account;
    account.AddNewAccount(root_user);
    input.str("");
    input.clear();
    std::string instruction;
    std::vector<std::string> tokens;
    User cur_user;
    cur_user.Privilege = 0;
    while (std::getline(input,instruction)) {
        // 账户系统
        // ====================================================
        std::string token;
        while (input >> token) {
            tokens.push_back(token);
        }
        int tokens_size = tokens.size();
        if (tokens_size == 0) continue;
        bool valid = true;
        if (tokens[0] == "su") {
            if (tokens_size == 1) valid = false;
            else if (account.FindUser(tokens[1]) == false) valid = false;
            else {
                User new_user = account.GetUser(tokens[1]);
                if (cur_user.Privilege <= new_user.Privilege && tokens_size == 2) valid = false;
                else {
                    if (cur_user.Privilege > new_user.Privilege) {
                        account.LogIn(new_user);
                        cur_user = new_user;
                    }
                    else {
                        if (tokens[2] == new_user.Password) account.LogIn(new_user);
                        else valid = false;
                    }
                }
            }
        }
        if (tokens[0] == "logout") {
            if (tokens_size > 1) valid = false;
            else if (!account.LogOut()) valid = false;
            else {
                cur_user = account.CurrentUser();
            }
        }
        if (tokens[0] == "register") {
            if (tokens_size != 4) valid = false;
            else if (account.FindUser(tokens[1]) == true || account.ValidCheck(tokens[1]) == false) valid = false;
            else if (account.ValidCheck(tokens[2]) == false) valid = false;
            else {
                User new_user(tokens[1],tokens[3],tokens[2],1);
                account.AddNewAccount(new_user);
            }
        }
        if (tokens[0] == "passwd") {
            if (tokens_size < 3 || tokens_size > 4) valid = false;
            else if (account.FindUser(tokens[1]) == false) valid = false;
            else {
                if (cur_user.Privilege == 7) {
                    if (tokens_size == 3) {
                        if (account.ValidCheck(tokens[2]) == false) valid = false;
                        else {
                            cur_user.NewPassword(tokens[2]);
                            account.ChangeInfo(cur_user);
                        }
                    }
                    else {
                        if (cur_user.Password != tokens[2] || account.ValidCheck(tokens[3]) == false) valid = false;
                        else {
                            cur_user.NewPassword(tokens[3]);
                            account.ChangeInfo(cur_user);
                        }
                    }
                }
                else {
                    if (tokens_size != 4) valid = false;
                    if (cur_user.Password != tokens[2] || account.ValidCheck(tokens[3]) == false) valid = false;
                    else {
                        cur_user.NewPassword(tokens[3]);
                        account.ChangeInfo(cur_user);
                    }
                }
            }
        }
        if (tokens[0] == "useradd") {
            if (cur_user.Privilege < 3) valid = false;
            if (tokens_size != 5) valid = false;
            else if (account.ValidCheck(tokens[1]) == false || account.ValidCheck(tokens[2]) == false) valid = false;
            else if (account.FindUser(tokens[1]) == true) valid = false;
            else {
                std::string privilege = tokens[3];
                int p = privilege[0] - '0';
                if (privilege.size() > 1 || p != 0 && p != 1 && p != 3 && p != 7) valid = false;
                else if (p >= cur_user.Privilege) valid = false;
                else {
                    User new_user(tokens[1],tokens[4],tokens[2],p);
                    account.AddNewAccount(new_user);
                }
            }
        }
        if (tokens[0] == "delete") {
            if (cur_user.Privilege < 7) valid = false;
            else if (tokens_size != 2) valid = false;
            else {
                if (account.FindUser(tokens[1]) == false) valid = false;
                else if (account.HasLogIn(tokens[1]) == true) valid = false;
                else {
                    User old_user = account.GetUser(tokens[1]);
                    account.DeleteAccount(old_user);
                }
            }
        }
        // =============================================
        //图书系统
        if (tokens[0] == "show") {

        }
        if (tokens[0] == "buy") {

        }
        if (tokens[0] == "select") {

        }
        if (tokens[0] == "modify") {

        }
        if (tokens[0] == "import") {

        }
        // =============================================
        // 日志系统
        if (valid == false) std::cout << "Invalid\n";
        input.str("");
        input.clear();
        tokens.clear();
    }
    return 0;
}