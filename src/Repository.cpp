//
// Created by HTY on 2025/12/10.
//
#include "../include/Repository.h"
#include "../include/DataMap.h"
#include "../include/Book.h"
#include<vector>
Database<std::array<char,20>,Book,1000> isbn_db;// 存放ISBN和Book结构体的映射
Database<std::array<char,60>,std::array<char,20>,1000> name_isbn_map;// BookName到ISBN的映射
Database<std::array<char,60>,std::array<char,20>,1000> author_isbn_map;// Author到ISBN的映射
Database<std::array<char,60>,std::array<char,20>,1000> keyword_isbn_map;// Keyword到ISBN的映射
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
    keyword_isbn_map.Insert(book.Keyword,book.ISBN);
}
float Repository::ComputeCost(std::string cost) {

}
void Repository::Parser(std::string line,std::string& type,std::string& index) {
    if (line[0] == '-') {
        int cnt = 1,prev_len = 0;
        while (line[cnt] != '=') type[cnt] = line[cnt],cnt++;
        if (type == "ISBN") {
            cnt++;
            prev_len = cnt;
            while (line[cnt] != '\0') index[cnt - prev_len] = line[cnt],cnt++;
        }
        else if (type == "name") {
            cnt += 2;
            prev_len = cnt;
            while (line[cnt] != '"') index[cnt - prev_len] = line[cnt],cnt++;
        }
        else if (type == "author") {
            cnt += 2;
            prev_len = cnt;
            while (line[cnt] != '"') index[cnt - prev_len] = line[cnt],cnt++;
        }
        else if (type == "keyword") {
            cnt += 2;
            prev_len = cnt;
            while (line[cnt] != '"') index[cnt - prev_len] = line[cnt],cnt++;
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
bool Repository::MultipleKeywords(std::string keyword) {
    int cnt = 0;
    while (keyword[cnt] != '\0') {
        if (keyword[cnt] == '|' && keyword[cnt + 1] != '\0') return false;
        cnt++;
    }
    return false;
}
void Repository::DeleteBook(Book& book) {
    name_isbn_map.Delete(book.BookName,book.ISBN);
    author_isbn_map.Delete(book.Author,book.ISBN);
    keyword_isbn_map.Delete(book.Keyword,book.ISBN);
    isbn_db.Delete(book.ISBN,book);
}