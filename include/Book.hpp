//
// Created by zcy on 2024/12/14.
//

#ifndef BOOK_HPP
#define BOOK_HPP
#include <cstring>
#include <iomanip>

#include "Storage/Unit.hpp"
#include "Directory.hpp"


struct Book_info {
  char ISBN[22] = {};
  char bookname[65] = {};
  char author[65] = {};
  char keyword[65] = {};
  int quantity = 0;
  double price = 0;

  bool operator<(const Book_info &other) const {
    return strcmp(ISBN, other.ISBN) < 0;
  }

  bool operator==(const Book_info &other) const {
    return strcmp(ISBN, other.ISBN) == 0 && strcmp(bookname, other.bookname) == 0 && strcmp(author, other.author) ==
           0 && strcmp(keyword, other.keyword) == 0 && price == other.price;
  }

  bool operator>(const Book_info &other) const {
    return operator<(other) ^ 1;
  }

  friend std::ostream &operator<<(std::ostream &os, const Book_info &that) {
    os << that.ISBN << '\t' << that.bookname << '\t' << that.author << '\t' << that.keyword << '\t' <<
        std::setprecision(2) << std::fixed << that.price <<
        '\t' << that.quantity;
    return os;
  }
};

class Book {
  Directory<Book_info> ISBN_storage_ = Directory<Book_info>("ISBN_storage");
  Directory<Book_info> name_storage_ = Directory<Book_info>("name_storage");
  Directory<Book_info> keyword_storage_ = Directory<Book_info>("book_storage");
  Directory<Book_info> author_storage_ = Directory<Book_info>("author_storage");

  void full_del(Book_info &target);

  void full_insert(Book_info &target);

  void copy(Book_info &target, Book_info &newinfo);

public:
  Book() = default;

  //type:0-all,1-ISBN,2-name,3-author,4-keyword
  void show(int type, string requirement = "");

  double buy(string ISBN, int quantity);

  void create(string ISBN);

  void modify(Book_info newinfo, string ISBN);

  void import(string ISBN, int quantity);
};


#endif //BOOK_HPP