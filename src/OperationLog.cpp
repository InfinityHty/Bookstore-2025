//
// Created by HTY on 2025/12/16.
//
#include "OperationLog.h"
#include "Memory.h"
#include<fstream>
#include<iostream>
#include<iomanip>
MemoryRiver<long double,5000> trade_db;

void OperationLog::Initialize() {
    trade_db.initialise(filename_trade);
    trade_db.get_body_num(trade_cnt);
    fstream logfile;
    logfile.open("log.txt",std::ios::in | std::ios::binary);
    if (!logfile.good()) {
        logfile.open("log.txt",std::ios::out | std::ios::binary);
        record_num = 0;
    }
    else {
        logfile.seekg(0,std::ios::end);
        record_num = logfile.tellg() / sizeof(Record);
    }
    logfile.close();
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
    long double income = 0,pay = 0;
    for (int i = 0; i < cnt; i++) {
        int index;
        long double value = 0;
        trade_db.get_info(index,trade_cnt - i);
        trade_db.read(value,index);
        if (value > 0) income += value;
        else pay += (-1) * value;
    }
    std::cout << "+ " << std::fixed << std::setprecision(2) << income;
    std::cout << " - " << pay << "\n";
}
void OperationLog::NewInOut(long double num) {
    //std::cerr << trade_cnt << "\n";
    trade_cnt++;
    int index = trade_db.write(num);
    trade_db.write_info(index,trade_cnt);
}
void OperationLog::AddRecord(User user,std::string instruction) {
    record_.user = user;
    record_num++;
    std::array<char,100> tmp{};
    int cnt = 0;
    while (instruction[cnt] != '\0') tmp[cnt] = instruction[cnt],cnt++;
    record_.operation = tmp;
    fstream logfile;
    logfile.open("log.txt",std::ios::in | std::ios::out | std::ios::binary);
    logfile.seekp(0,std::ios::end);
    logfile.write(reinterpret_cast<char *>(&record_),sizeof(Record));
    logfile.close();
}
void OperationLog::ShowRecord() {
    fstream logfile;
    logfile.open("log.txt",std::ios::binary | std::ios::in);
    logfile.seekg(0,std::ios::beg);
    Record all_record[5000];
    logfile.read(reinterpret_cast<char *>(all_record),sizeof(Record) * record_num);
    for (int i = 0; i < record_num; i++) {
        int cnt = 0;
        User tmp_user = all_record[i].user;
        std::array<char,100> tmp_operation = all_record[i].operation;
        while (tmp_user.UserID[cnt] != '\0') std::cout << tmp_user.UserID[cnt++];
        std::cout << " " << "[" << tmp_user.Privilege << "]: ";
        cnt = 0;
        while (tmp_operation[cnt] != '\0') std::cout << tmp_operation[cnt++];
        std::cout << "\n";
    }
    logfile.close();
}
void OperationLog::ReportFinance() {
    for (int i = 1; i <= trade_cnt; i++) {
        int index;
        long double value;
        trade_db.get_info(index,i);
        trade_db.read(value,index);
        if (value > 0) std::cout << "earned " << value << "\n";
        else std::cout << "costed " << value << "\n";
    }
}
void OperationLog::ReportEmployee() {
    fstream logfile;
    logfile.open("log.txt",std::ios::binary | std::ios::in);
    logfile.seekg(0,std::ios::beg);
    Record all_record[5000];
    logfile.read(reinterpret_cast<char *>(all_record),sizeof(Record) * record_num);
    for (int i = 0; i < record_num; i++) {
        int cnt = 0;
        User tmp_user = all_record[i].user;
        std::array<char,100> tmp_operation = all_record[i].operation;
        if (tmp_user.Privilege == 3) {
            while (tmp_user.UserID[cnt] != '\0') std::cout << tmp_user.UserID[cnt++];
            std::cout << " : ";
            cnt = 0;
            while (tmp_operation[cnt] != '\0') std::cout << tmp_operation[cnt++];
            std::cout << "\n";
        }
    }
    logfile.close();
}