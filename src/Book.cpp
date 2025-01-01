//
// Created by zcy on 2024/12/14.
//

#include "../include/Book.hpp"
#include "../include/User.hpp"
#include "../include/Utils.hpp"
#include "../include/Storage/Unit.hpp"
#include <iostream>
BOOK_HPP

void Book::full_del(Book_info &target) {
  ISBN_storage_.del(Unit<Book_info>(target.ISBN, target));
  if (target.bookname[0] != 0) {
    name_storage_.del(Unit<Book_info>(target.bookname, target));
  }
  if (target.author[0] != 0) {
    author_storage_.del(Unit<Book_info>(target.author, target));
  }
  if (target.keyword[0] != 0) {
    auto words = parser(string(target.keyword));
    for (const auto &it : words) {
      keyword_storage_.del(Unit<Book_info>(it.c_str(), target));
    }
  }
}

void Book::copy(Book_info &target, Book_info &newinfo) {
  if (newinfo.ISBN[0] != 0) {
    memset(target.ISBN, 0, sizeof(target.ISBN));
    strcpy(target.ISBN, newinfo.ISBN);
  }
  if (newinfo.author[0] != 0) {
    memset(target.author, 0, sizeof(target.author));
    strcpy(target.author, newinfo.author);
  }
  if (newinfo.keyword[0] != 0) {
    memset(target.keyword, 0, sizeof(target.keyword));
    strcpy(target.keyword, newinfo.keyword);
  }
  if (newinfo.bookname[0] != 0) {
    memset(target.bookname, 0, sizeof(target.bookname));
    strcpy(target.bookname, newinfo.bookname);
  }
  if (newinfo.price != 0) {
    target.price = newinfo.price;
  }
}

void Book::full_insert(Book_info &target) {
  ISBN_storage_.insert(Unit<Book_info>(target.ISBN, target));
  if (target.bookname[0] != 0) {
    name_storage_.insert(Unit<Book_info>(target.bookname, target));
  }
  if (target.author[0] != 0) {
    author_storage_.insert(Unit<Book_info>(target.author, target));
  }
  if (target.keyword[0] != 0) {
    auto words = parser(string(target.keyword));
    for (const auto &it : words) {
      keyword_storage_.insert(Unit<Book_info>(it.c_str(), target));
    }
  }
}

void Book::create(string ISBN) {
  auto tmp = ISBN_storage_.find(Unit<Book_info>(ISBN.c_str()));
  if (tmp.empty()) {
    Book_info val;
    memset(val.ISBN, 0, sizeof(val.ISBN));
    strcpy(val.ISBN, ISBN.c_str());
    ISBN_storage_.insert(Unit<Book_info>(ISBN.c_str(), val));
  }
}

double Book::buy(string ISBN, int quantity) {
  auto tmp = ISBN_storage_.find(Unit<Book_info>(ISBN.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  auto target = tmp.front();
  if (target.quantity < quantity) {
    throw std::exception();
  }
  full_del(target);
  target.quantity -= quantity;
  full_insert(target);
  return target.price;
}

void Book::import(string ISBN, int quantity) {
  if (ISBN == "") {
    throw std::exception();
  }
  auto tmp = ISBN_storage_.find(Unit<Book_info>(ISBN.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  auto target = tmp.front();
  full_del(target);
  target.quantity += quantity;
  full_insert(target);
}

//分解为三步：删除原有记录，修改为正确单元，重新插入
void Book::modify(Book_info newinfo, string ISBN) {
  auto tmp = ISBN_storage_.find(Unit<Book_info>(ISBN.c_str()));
  if (tmp.empty()) {
    throw std::exception();
  }
  if (newinfo.ISBN[0] != 0) {
    auto safetycheck = ISBN_storage_.find(Unit<Book_info>(newinfo.ISBN));
    if (!safetycheck.empty()) {
      throw std::exception();
    }
  }
  auto target = tmp.front();
  full_del(target);
  copy(target, newinfo);
  full_insert(target);
}

void Book::show(int type, string requirement) {
  switch (type) {
    case 0: {
      ISBN_storage_.print_all();
      break;
    }
    case 1: {
      auto tmp = ISBN_storage_.find(Unit<Book_info>(requirement.c_str()));
      if (tmp.empty()) {
        std::cout << "\n";
      } else {
        std::cout << tmp.front() << '\n';
      }
      break;
    }
    case 2: {
      auto tmp = name_storage_.find(Unit<Book_info>(requirement.c_str()));
      if (tmp.empty()) {
        std::cout << "\n";
      } else {
        for (const auto &it : tmp) {
          std::cout << it << '\n';
        }
      }
      break;
    }
    case 3: {
      auto tmp = author_storage_.find(Unit<Book_info>(requirement.c_str()));
      if (tmp.empty()) {
        std::cout << "\n";
      } else {
        for (const auto &it : tmp) {
          std::cout << it << '\n';
        }
      }
      break;
    }
    case 4: {
      auto words = parser(requirement);
      if (words.size() > 1) {
        throw std::exception();
      }
      auto tmp = keyword_storage_.find(Unit<Book_info>(requirement.c_str()));
      if (tmp.empty()) {
        std::cout << "\n";
      } else {
        for (const auto &it : tmp) {
          std::cout << it << '\n';
        }
      }
      break;
    }
    default: {
      throw std::exception();
    }
  }
}