//
// Created by HTY on 2025/12/10.
//

#ifndef BOOKSTORE_2025_REPOSITORY_H
#define BOOKSTORE_2025_REPOSITORY_H
#include "Book.h"
#include<string>
class Repository {
public:
    void Initialize();
    bool FindBook(std::string isbn);
    void ChangeInfo(Book& book);
    int ComputeQuantity(std::string quantity);
    Book GetABook(std::string isbn);
    void AddNewBook(Book& book);
    float ComputeCost(std::string cost);
    void Parser(std::string line,std::string& type,std::string& index);
    void DeleteBook(Book& book);
    void ShowAll();
    void PrintExistingBooks(std::string& type,std::string& index);
    bool MultipleKeywords(std::string keyword);
private:
    std::string filename_isbn = "isbn.txt";
    std::string index_isbn = "index_isbn.txt";
    std::string filename_name = "name.txt";
    std::string index_name = "index_name.txt";
    std::string filename_author = "author.txt";
    std::string index_author = "index_author.txt";
    std::string filename_keyword = "keyword.txt";
    std::string index_keyword = "index_keyword.txt";
};
#endif //BOOKSTORE_2025_REPOSITORY_H