//
// Created by HTY on 2025/12/14.
//
#include "../include/Book.h"
#include<iomanip>
std::ostream& operator<<(std::ostream& os, const Book& book) {
    int cnt = 0;
    std::string isbn = book.ISBN.data();
    os << isbn << "\t" << book.BookName.data() << "\t" << book.Author.data() << "\t" << book.Keyword.data() << "\t";
    os << std::fixed << std::setprecision(2) << book.Price << "\t" << book.Quantity << "\n";
    return os;
}