//
// Created by HTY on 2025/12/10.
//

#ifndef BOOKSTORE_2025_BOOK_H
#define BOOKSTORE_2025_BOOK_H
#include<array>
#include<string>
#include<iostream>
class Book {
public:
    std::array<char,20> ISBN{};
    std::array<char,60> BookName{};
    std::array<char,60> Author{};
    std::array<char,60> Keyword{};
    int Quantity = 0;// 库存数量
    float Price = 0;// 保留小数点后两位
    Book() = default;
    Book(std::string isbn,std::string bookname,std::string author,std::string keyword,int quantity,float price) : Quantity(quantity), Price(price){
        int cnt = 0;
        while (isbn[cnt] != '\0') ISBN[cnt] = isbn[cnt],cnt++;
        cnt = 0;
        while (bookname[cnt] != '\0') BookName[cnt] = bookname[cnt],cnt++;
        cnt = 0;
        while (author[cnt] != '\0') Author[cnt] = author[cnt],cnt++;
        cnt = 0;
        while (keyword[cnt] != '\0') Keyword[cnt] = keyword[cnt],cnt++;

    }
    bool operator==(const Book& book) const {
        return ISBN == book.ISBN;
    }
    bool operator<(const Book& book) const {
        return ISBN < book.ISBN;
    }
    bool operator>(const Book& book) const {
        return ISBN > book.ISBN;
    }
    bool operator<=(const Book& book) const {
        return ISBN <= book.ISBN;
    }
    bool operator>=(const Book& book) const {
        return ISBN >= book.ISBN;
    }
    friend std::ostream& operator<<(std::ostream& os, const Book& book);

};

#endif //BOOKSTORE_2025_BOOK_H