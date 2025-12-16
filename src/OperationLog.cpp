//
// Created by HTY on 2025/12/16.
//
#include "OperationLog.h"
#include<iostream>
#include<iomanip>
int OperationLog::ComputeCount(std::string input) {
    int cnt = 0,output = 0;
    while (input[cnt] != '\0') {
        if (input[cnt] < '0' || input[cnt] > '9') return -1;
        output = output * 10 + (input[cnt] - '0');
        cnt++;
    }
    return output;
}
void OperationLog::ShowFinance(int cnt) {
    float income = 0,pay = 0;
    for (int i = 0; i < cnt; i++) {
        if (trade[trade_cnt - i - 1] > 0) income += trade[trade_cnt - i - 1];
        else pay += trade[trade_cnt - i - 1] * (-1);
    }
    std::cout << "+ " << std::fixed << std::setprecision(2) << income;
    std::cout << " - " << pay << "\n";
}
void OperationLog::NewInOut(float num) {
    trade.push_back(num);
    trade_cnt++;
}