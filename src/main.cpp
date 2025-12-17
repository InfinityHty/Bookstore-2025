//
// Created by HTY on 2025/12/9.
//
#include<iostream>
#include<iomanip>
#include "../include/Account.h"
#include "../include/User.h"
#include "../include/Book.h"
#include "../include/Repository.h"
#include "../include/OperationLog.h"
#include<string>
#include<sstream>
#include<vector>
#include<array>
#include<set>
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
std::array<char,60> Change60(std::string input) {
    std::array<char,60> output{};
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
    OperationLog log;
    log.Initialize();
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
            //std::cerr << token << "\n";
        }
        int tokens_size = tokens.size();
        if (tokens_size == 0) {
            input.str("");
            input.clear();
            tokens.clear();
            continue;
        }
        bool valid = true;
        if (tokens[0] == "exit" || tokens[0] == "quit") exit(0);
        else if (tokens[0] == "su") {
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
        else if (tokens[0] == "logout") {
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size > 1) valid = false;
            else if (!account.LogOut()) valid = false;
            else {
                cur_user = account.CurrentUser();
                //cur_select_book = empty_book;
            }
        }
        else if (tokens[0] == "register") {
            if (tokens_size != 4) valid = false;
            else if (account.FindUser(tokens[1]) == true || account.ValidCheck(tokens[1]) == false) valid = false;
            else if (account.ValidCheck(tokens[2]) == false) valid = false;
            else {
                User new_user(tokens[1],tokens[3],tokens[2],1);
                account.AddNewAccount(new_user);
            }
        }
        else if (tokens[0] == "passwd") {
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
        else if (tokens[0] == "useradd") {
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
        else if (tokens[0] == "delete") {
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
        else if (tokens[0] == "show") {
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size == 1) {
                repo.ShowAll();
            }
            else {
                // 财务记录查询
                if (tokens[1] == "finance") {
                    if (cur_user.Privilege < 7) valid = false;
                    else {
                        if (tokens_size == 2) {
                            //std::cerr << log.trade_cnt;
                            log.ShowFinance(log.trade_cnt);
                        }
                        else {
                            int cnt = log.ComputeCount(tokens[2]);
                            if (cnt < 0 || cnt > log.trade_cnt) valid = false;
                            else if (cnt == 0) std::cout << "\n";
                            else log.ShowFinance(cnt);
                        }
                    }
                }
                else {
                    std::string type;
                    std::vector<std::string> index;
                    repo.Parser(tokens[1],type,index);
                    if (index.empty()) valid = false;
                    else if (type == "keyword" && index.size() > 1) valid = false;
                    else {
                        repo.PrintExistingBooks(type,index[0]);
                    }
                }
            }
        }
        else if (tokens[0] == "buy") {
            if (cur_user.Privilege < 1) valid = false;
            else if (tokens_size != 3) valid = false;
            else if (repo.FindBook(tokens[1]) == false) valid = false;
            else {
                int q = repo.ComputeQuantity(tokens[2]);
                if (q == -1 || q == 0) valid = false;
                else {
                    Book buy_book = repo.GetABook(tokens[1]);
                    if (buy_book.Quantity < q) valid = false;
                    else {
                        float charge = q * buy_book.Price;
                        buy_book.Quantity -= q;
                        repo.ChangeInfo(buy_book);
                        std::cout << std::fixed << std::setprecision(2) << charge << "\n";
                        log.NewInOut(charge);
                    }
                }
            }
        }
        else if (tokens[0] == "select") {
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
        else if (tokens[0] == "modify") {
            if (cur_user.Privilege < 3) valid = false;
            else if (cur_select_book == empty_book) valid = false;
            else {
                Book change_book = cur_select_book;
                std::set<std::string> has_op{};
                for (int j = 1; j < tokens_size; j++) {
                    std::string type;
                    std::vector<std::string> index;
                    repo.Parser(tokens[j],type,index);
                    if (index.empty()) {
                        valid = false;
                        break;
                    }
                    else if (type == "ISBN" && repo.FindBook(index[0])) {
                        valid = false;
                        break;
                    }
                    else if (has_op.find(index[0]) != has_op.end()) {
                        valid = false;
                        break;
                    }
                    else if (type == "keyword" && repo.RepeatKeywords(index)) {
                        valid = false;
                        break;
                    }
                    else {
                        if (type == "ISBN") {
                            change_book.ISBN = Change20(index[0]);
                        }
                        else if (type == "name") {
                            change_book.BookName = Change60(index[0]);
                        }
                        else if (type == "author") {
                            change_book.Author = Change60(index[0]);
                        }
                        else if (type == "keyword") {
                            change_book.Keyword = repo.GetKeywords(tokens[j]);
                        }
                        else if (type == "price") {
                            change_book.Price = repo.ComputeCost(index[0]);
                        }
                    }
                    if (valid) {
                        repo.DeleteBook(cur_select_book);
                        repo.AddNewBook(change_book);
                        cur_select_book = change_book;
                    }
                }
            }
        }
        else if (tokens[0] == "import") {
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
                    log.NewInOut((-1) * total_cost);
                }
            }
        }

        // =============================================
        // 日志系统
        else if (tokens[0] == "report") {
            if (cur_user.Privilege < 7) valid = false;
            else if (tokens_size != 2) valid = false;
            else {
                if (tokens[1] == "finance") {

                }
                if (tokens[1] == "employee") {

                }
            }
        }
        else if (tokens[0] == "log") {

        }
        else valid = false;

        if (valid == false) std::cout << "Invalid\n";
        input.str("");
        input.clear();
        tokens.clear();
    }
    return 0;
}