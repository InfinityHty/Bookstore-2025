//
// Created by HTY on 2025/12/10.
//
#include "../include/Repository.h"
#include "../include/DataMap.h"
#include "../include/Book.h"
#include<vector>
#include<cmath>
#include<set>
Database<std::array<char,20>,Book,500> isbn_db;// 存放ISBN和Book结构体的映射
Database<std::array<char,60>,std::array<char,20>,500> name_isbn_map;// BookName到ISBN的映射
Database<std::array<char,60>,std::array<char,20>,500> author_isbn_map;// Author到ISBN的映射
Database<std::array<char,60>,std::array<char,20>,500> keyword_isbn_map;// Keyword到ISBN的映射
void Repository::Initialize() {
    isbn_db.Initialize(index_isbn,filename_isbn);
    name_isbn_map.Initialize(index_name,filename_name);
    author_isbn_map.Initialize(index_author,filename_author);
    keyword_isbn_map.Initialize(index_keyword,filename_keyword);
}
int Repository::ComputeQuantity(std::string quantity) {
    int q = 0,cnt = 0;
    while (quantity[cnt] != '\0') {
        if (quantity[cnt] < '0' || quantity[cnt] > '9') return -1;
        q = q * 10 + (quantity[cnt] - '0');
        cnt++;
    }
    return q;
}
bool Repository::FindBook(std::string isbn) {
    std::array<char,20> isbn_{};
    int cnt = 0;
    while (isbn[cnt] != '\0') isbn_[cnt] = isbn[cnt],cnt++;
    return isbn_db.CheckExist(isbn_);
}
void Repository::ChangeInfo(Book& book) {
    isbn_db.ChangeInfo(book.ISBN,book);
}
Book Repository::GetABook(std::string isbn) {
    std::array<char,20> isbn_{};
    int cnt = 0;
    while (isbn[cnt] != '\0') isbn_[cnt] = isbn[cnt],cnt++;
    return isbn_db.GetValue(isbn_);
}
void Repository::AddNewBook(Book& book) {
    isbn_db.Insert(book.ISBN,book);
    name_isbn_map.Insert(book.BookName,book.ISBN);
    author_isbn_map.Insert(book.Author,book.ISBN);
    // 每个keyword分别插入一遍
    std::vector<std::string> keywords = MultipleKeywords(book.Keyword);
    for (auto it = keywords.begin(); it != keywords.end(); it++) {
        int cnt = 0;
        std::array<char,60> keyword_{};
        while ((*it)[cnt] != '\0') keyword_[cnt] = (*it)[cnt],cnt++;
        keyword_isbn_map.Insert(keyword_,book.ISBN);
    }
    //keyword_isbn_map.Insert(book.Keyword,book.ISBN);
}
float Repository::ComputeCost(std::string cost) {
    int dot_pos = 0,cnt = 0;
    long long price = 0;
    while (cost[cnt] != '\0') {
        if (cost[cnt] == '.') {
            dot_pos = cost.size() - 1 - cnt;
            cnt++;
        }
        else {
            price = price * 10 + (cost[cnt] - '0');
            cnt++;
        }
    }
    float ans = price * 1.0 / pow(10,dot_pos);
    return ans;
}
// 拆分
void Repository::Parser(std::string line,std::string& type,std::vector<std::string>& index) {
    if (line[0] == '-') {
        int cnt = 1;
        //std::cerr << line << "\n";
        //type = line;
        while (line[cnt] != '=') {
            type.push_back(line[cnt]);
            cnt++;
        }
        if (type == "ISBN") {
            cnt++;
            std::string tmp;
            while (line[cnt] != '\0') tmp.push_back(line[cnt]),cnt++;
            index.push_back(tmp);
        }
        else if (type == "name") {
            cnt += 2;
            std::string tmp;
            while (line[cnt] != '"') tmp.push_back(line[cnt]),cnt++;
            index.push_back(tmp);
        }
        else if (type == "author") {
            cnt += 2;
            std::string tmp;
            while (line[cnt] != '"') tmp.push_back(line[cnt]),cnt++;
            index.push_back(tmp);
        }
        else if (type == "keyword") {
            cnt += 2;
            std::string tmp;
            while (line[cnt] != '"') {
                if (line[cnt] == '|') {
                    index.push_back(tmp);
                    tmp.clear();
                    cnt++;
                }
                else {
                    tmp.push_back(line[cnt]);
                    cnt++;
                }
            }
            index.push_back(tmp);
        }
        else if (type == "price") {
            cnt++;
            std::string tmp;
            while (line[cnt] != '\0') tmp.push_back(line[cnt]),cnt++;
            index.push_back(tmp);
        }
    }
}
void Repository::ShowAll() {
    isbn_db.ShowAll();
}
void Repository::PrintExistingBooks(std::string& type,std::string& index) {
    if (type == "ISBN") {
        int cnt = 0;
        std::array<char,20> isbn_{};
        while (index[cnt] != '\0') isbn_[cnt] = index[cnt],cnt++;
        isbn_db.Find(isbn_);
        if (isbn_db.CheckExist(isbn_) == false) std::cout << "\n";
    }
    else if (type == "name") {
        int cnt = 0;
        bool exist = false;
        std::array<char,60> bookname_{};
        //std::cerr << index << "\n";
        while (index[cnt] != '\0') bookname_[cnt] = index[cnt],cnt++;
        std::vector<std::array<char,20>> ISBNs = name_isbn_map.ReturnValues(bookname_);
        for (auto it = ISBNs.begin(); it != ISBNs.end(); it++) {
            isbn_db.Find((*it));
            if (isbn_db.CheckExist((*it)) == true) exist = true;
        }
        if (exist == false) std::cout << "\n";
    }
    else if (type == "author") {
        int cnt = 0;
        bool exist = false;
        std::array<char,60> author_{};
        while (index[cnt] != '\0') author_[cnt] = index[cnt],cnt++;
        std::vector<std::array<char,20>> ISBNs = author_isbn_map.ReturnValues(author_);
        for (auto it = ISBNs.begin(); it != ISBNs.end(); it++) {
            isbn_db.Find((*it));
            if (isbn_db.CheckExist((*it)) == true) exist = true;
        }
        if (exist == false) std::cout << "\n";
    }
    else if (type == "keyword") {
        int cnt = 0;
        bool exist = false;
        std::array<char,60> keyword_{};
        while (index[cnt] != '\0') keyword_[cnt] = index[cnt],cnt++;
        std::vector<std::array<char,20>> ISBNs = keyword_isbn_map.ReturnValues(keyword_);
        for (auto it = ISBNs.begin(); it != ISBNs.end(); it++) {
            isbn_db.Find((*it));
            if (isbn_db.CheckExist((*it)) == true) exist = true;
        }
        if (exist == false) std::cout << "\n";
    }
}
std::vector<std::string> Repository::MultipleKeywords(std::array<char,60> keyword) {
    int cnt = 0;
    std::vector<std::string> keywords{};
    std::string tmp_keyword{};
    while (keyword[cnt] != '\0') {
        if (keyword[cnt] == '|' && keyword[cnt + 1] != '\0') {
            keywords.push_back(tmp_keyword);
            tmp_keyword.clear();
            cnt++;
        }
        else {
            tmp_keyword.push_back(keyword[cnt]);
            cnt++;
        }
    }
    keywords.push_back(tmp_keyword);
    return keywords;
}
bool Repository::RepeatKeywords(std::vector<std::string> keywords) {
    std::set<std::string> has_keyword{};
    for (auto it = keywords.begin(); it != keywords.end(); it++) {
        if (has_keyword.find(*it) != has_keyword.end()) {
            return true;
        }
        else has_keyword.insert(*it);
    }
    return false;
}
void Repository::DeleteBook(Book& book) {
    name_isbn_map.Delete(book.BookName,book.ISBN);
    author_isbn_map.Delete(book.Author,book.ISBN);
    std::vector<std::string> keywords = MultipleKeywords(book.Keyword);
    for (auto it = keywords.begin(); it != keywords.end(); it++) {
        int cnt = 0;
        std::array<char,60> keyword_{};
        while ((*it)[cnt] != '\0') keyword_[cnt] = (*it)[cnt],cnt++;
        keyword_isbn_map.Delete(keyword_,book.ISBN);
    }
    isbn_db.Delete(book.ISBN,book);
}
std::array<char,60> Repository::GetKeywords(std::string lines) {
    std::array<char,60> keyword_{};
    int cnt = 10;
    while (lines[cnt] != '"') {
        keyword_[cnt - 10] = lines[cnt];
        cnt++;
    }
    return keyword_;
}