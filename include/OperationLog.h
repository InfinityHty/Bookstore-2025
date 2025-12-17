//
// Created by HTY on 2025/12/13.
//

#ifndef BOOKSTORE_2025_OPERATIONLOG_H
#define BOOKSTORE_2025_OPERATIONLOG_H
#include<string>
#include<array>
#include<vector>
class OperationLog {
private:
    struct WorkLog {
        std::array<char,30> UserID;
        int op_number;

    };
    std::string filename_trade = "trade.txt";
    //std::vector<float> trade{};
public:
    int trade_cnt;// 总交易笔数
    void Initialize();
    int ComputeCount(std::string);
    void ShowFinance(int cnt);
    void NewInOut(float num);
};
#endif //BOOKSTORE_2025_OPERATIONLOG_H