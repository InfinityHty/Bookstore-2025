//
// Created by HTY on 2025/12/10.
//

#ifndef BOOKSTORE_2025_REPOSITORY_H
#define BOOKSTORE_2025_REPOSITORY_H
#include "Book.h"
#include<string>
#include<vector>
class Repository {
public:
    void Initialize();
    bool FindBook(std::string isbn);
    void ChangeInfo(Book& book);
    int ComputeQuantity(std::string quantity);
    Book GetABook(std::string isbn);
    Book GetABook2(std::array<char,20> isbn);
    void AddNewBook(Book& book);
    double ComputeCost(std::string cost);
    void Parser(std::string line,std::string& type,std::vector<std::string>& index);
    void DeleteBook(Book& book);
    void ShowAll();
    void PrintExistingBooks(std::string& type,std::string& index);
    std::vector<std::string> MultipleKeywords(std::array<char,60> keyword);
    bool RepeatKeywords(std::vector<std::string> keywords);
    std::array<char,60> GetKeywords(std::string lines);
    void LogIn(Book& book);
    void LogOut();
    Book GetSelectedBook();
    void ChangeSelectedBook(Book& book);
    void ModifySelectedBook(Book& pre_book,Book& new_book);
private:
    std::string filename_isbn = "isbn.txt";
    std::string index_isbn = "index_isbn.txt";
    std::string filename_name = "name.txt";
    std::string index_name = "index_name.txt";
    std::string filename_author = "author.txt";
    std::string index_author = "index_author.txt";
    std::string filename_keyword = "keyword.txt";
    std::string index_keyword = "index_keyword.txt";
    std::vector<Book> selected_list{};
};
#endif //BOOKSTORE_2025_REPOSITORY_H