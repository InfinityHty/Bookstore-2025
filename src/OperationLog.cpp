//
// Created by HTY on 2025/12/16.
//
#include "OperationLog.h"
#include "Memory.h"
#include<iostream>
#include<iomanip>
MemoryRiver<float,1000> trade_db;
void OperationLog::Initialize() {
    trade_db.initialise(filename_trade);
}
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
        int index;
        float value = 0;
        trade_db.get_info(index,trade_cnt - i);
        trade_db.read(value,index);
        if (value > 0) income += value;
        else pay += (-1) * value;
    }
    std::cout << "+ " << std::fixed << std::setprecision(2) << income;
    std::cout << " - " << pay << "\n";
}
void OperationLog::NewInOut(float num) {
    trade_cnt++;
    int index = trade_db.write(num);
    trade_db.write_info(index,trade_cnt);
}