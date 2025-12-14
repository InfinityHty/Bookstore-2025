//
// Created by HTY on 2025/12/9.
//
#include<iostream>
#include "../include/Account.h"
#include "../include/User.h"
#include "../include/Book.h"
#include "../include/Repository.h"
#include<string>
#include<sstream>
#include<vector>
#include<array>
// 把string类型转成 std::array<char,30>
std::array<char,30> Change30(std::string input) {
    std::array<char,30> output{};
    int cnt = 0;
    while (input[cnt] != '\0') output[cnt] = input[cnt],cnt++;
    return output;
}
std::array<char,20> Change20(std::string input) {
    std::array<char,20> output{};
    int cnt = 0;
    while (input[cnt] != '\0') output[cnt] = input[cnt],cnt++;
    return output;
}
std::stringstream input;
int main() {
    User root_user("root","root","sjtu",7);
    Account account;
    account.Initialize();
    Repository repo;
    repo.Initialize();
    account.AddNewAccount(root_user);
    input.str("");
    input.clear();
    std::string instruction;
    std::vector<std::string> tokens;
    User cur_user;
    Book cur_select_book;
    Book empty_book("","","","",0,0);
    cur_user.Privilege = 0;
    while (std::getline(std::cin,instruction)) {
        input << instruction;
        // 账户系统
        // ====================================================
        std::string token;
        while (input >> token) {
            tokens.push_back(token);
            std::cerr << token << "\n";
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
                        if (Change30(tokens[2]) == new_user.Password) {
                            account.LogIn(new_user);
                            cur_user = new_user;
                        }
                        else valid = false;
                    }
                }
            }
        }
        if (tokens[0] == "logout") {
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size > 1) valid = false;
            else if (!account.LogOut()) valid = false;
            else {
                cur_user = account.CurrentUser();
                cur_select_book = empty_book;
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
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size < 3 || tokens_size > 4) valid = false;
            else if (account.FindUser(tokens[1]) == false) valid = false;
            else {
                // root用户
                if (cur_user.Privilege == 7) {
                    if (tokens_size == 3) {
                        if (account.ValidCheck(tokens[2]) == false) valid = false;
                        else {
                            User to_be_modify = account.GetUser(tokens[1]);
                            to_be_modify.NewPassword(tokens[2]);
                            account.ChangeInfo(to_be_modify);
                        }
                    }
                    else {
                        if (cur_user.Password != Change30(tokens[2]) || account.ValidCheck(tokens[3]) == false) valid = false;
                        else {
                            User to_be_modify = account.GetUser(tokens[1]);
                            to_be_modify.NewPassword(tokens[3]);
                            account.ChangeInfo(to_be_modify);
                        }
                    }
                }
                else {
                    if (tokens_size != 4) valid = false;
                    User to_be_modify = account.GetUser(tokens[1]);
                    if (to_be_modify.Password != Change30(tokens[2]) || account.ValidCheck(tokens[3]) == false) valid = false;
                    else {
                        to_be_modify.NewPassword(tokens[3]);
                        account.ChangeInfo(to_be_modify);
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
        // 先按照""中间没有空格处理
        if (tokens[0] == "show") {
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size == 1) {
                repo.ShowAll();
            }
            else {
                // 财务记录查询
                if (tokens[1] == "finance") {

                }
                else {
                    std::string type,index;
                    repo.Parser(tokens[1],type,index);
                    std::cerr << type << " " << index << "\n";
                    if (index.empty()) valid = false;
                    else if (type == "keyword" && repo.MultipleKeywords(index)) valid = false;
                    else {
                        repo.PrintExistingBooks(type,index);
                    }
                }
            }
        }
        if (tokens[0] == "buy") {
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size != 3) valid = false;
            else if (repo.FindBook(tokens[1]) == false) valid = false;
            else {
                int q = repo.ComputeQuantity(tokens[2]);
                if (q == -1) valid = false;
                else {
                    Book buy_book = repo.GetABook(tokens[2]);
                    if (buy_book.Quantity < q) valid = false;
                    else {
                        float charge = q * buy_book.Price;
                        buy_book.Quantity -= q;
                        repo.ChangeInfo(buy_book);
                        std::cout << charge << "\n";
                    }
                }
            }
        }
        if (tokens[0] == "select") {
            if (cur_user.Privilege < 3) valid = false;
            else if (tokens_size != 2) valid = false;
            else {
                if (repo.FindBook(tokens[1]) == true) {
                    cur_select_book = repo.GetABook(tokens[1]);
                }
                else {
                    Book new_book;
                    new_book.ISBN = Change20(tokens[1]);
                    repo.AddNewBook(new_book);
                    cur_select_book = new_book;
                }
            }
        }
        // TBD
        if (tokens[0] == "modify") {
            if (cur_user.Privilege < 3) valid = false;
        }
        if (tokens[0] == "import") {
            if (cur_user.Privilege < 3) valid = false;
            else if (tokens_size != 3) valid = false;
            else if (cur_select_book == empty_book) valid = false;
            else {
                int q = repo.ComputeQuantity(tokens[1]);
                float total_cost = repo.ComputeCost(tokens[2]);
                if (q == -1) valid = false;
                else if (total_cost < 0) valid = false;
                else {
                    cur_select_book.Quantity += q;
                    repo.ChangeInfo(cur_select_book);
                }
            }
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