//
// Created by HTY on 2025/12/13.
//

#ifndef BOOKSTORE_2025_OPERATIONLOG_H
#define BOOKSTORE_2025_OPERATIONLOG_H
#include<string>
#include<array>
#include<vector>
#include "../include/User.h"
class OperationLog {
private:
    struct Record {
        User user;
        std::array<char,100> operation{};
    }record_;
    std::string filename_trade = "trade.txt";
    //std::vector<float> trade{};
public:
    int trade_cnt;// 总交易笔数
    int record_num; // 总有效操作条数
    void Initialize();
    int ComputeCount(std::string);
    void ShowFinance(int cnt);
    void NewInOut(long double num);
    void AddRecord(User user,std::string instruction);
    void ShowRecord();
    void ReportFinance();
    void ReportEmployee();
};
#endif //BOOKSTORE_2025_OPERATIONLOG_H