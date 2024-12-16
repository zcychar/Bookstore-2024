#include <cmath>
#include <iostream>
#include <sstream>
#include "include/Book.hpp"
#include "include/Log.hpp"
#include "include/User.hpp"
#include "include/Utils.hpp"


void processLine(string &input, User &user, Log &log, Book &book) {
  auto processed = splitInput(input);
  if (processed.empty())return;
  string opt = processed[0];
  int current_level = user.getP();
  if (opt == "quit" || opt == "exit") {
    exit(0);
  }
  if (opt == "su") {
    if (processed.size() == 2) {
      if (!isValidString(processed[1], 30)) {
        throw std::exception();
      }
      user.login(processed[1]);
    } else if (processed.size() == 3) {
      if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30)) {
        throw std::exception();
      }
      user.login(processed[1], processed[2]);
    } else {
      throw std::exception();
    }
  } else if (opt == "logout") {
    if (current_level < 1 || processed.size() > 1) {
      throw std::exception();
    }
    user.logout();
  } else if (opt == "register") {
    if (processed.size() != 4) {
      throw std::exception();
    }
    if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30) || processed[3].size() > 30) {
      throw std::exception();
    }
    user.regist(processed[1], processed[2], processed[3]);
  } else if (opt == "passwd") {
    if (current_level < 1) {
      throw std::exception();
    }
    if (processed.size() == 3) {
      if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30)) {
        throw std::exception();
      }
      user.passwd(processed[1], processed[2]);
    } else if (processed.size() == 4) {
      if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30) || !isValidString(processed[3], 30)) {
        throw std::exception();
      }
      user.passwd(processed[1], processed[3], processed[2]);
    } else {
      throw std::exception();
    }
  } else if (opt == "useradd") {
    if (current_level < 3 || processed.size() != 5) {
      throw std::exception();
    }
    if (!isValidString(processed[1], 30) || !isValidString(processed[2], 30) || processed[4].size() > 30) {
      throw std::exception();
    }
    user.useradd(processed[1], processed[2], stringtoInt(processed[3]), processed[4]);
  } else if (opt == "delete") {
    if (current_level < 7 || processed.size() != 2 || !isValidString(processed[1], 30)) {
      throw std::exception();
    }
    user.del(processed[1]);
  } else if (opt == "show") {
    if (processed[1] == "finance") {
      if(processed.size()==2) {
        log.show(-1);
      }else if(processed.size()==3) {
        log.show(stringtoInt(processed[2]));
      }else {
        throw std::exception();
      }
    } else {
      //type:0-all,1-ISBN,2-name,3-author,4-keyword
      if (current_level < 1) {
        throw std::exception();
      }
      if (processed.size() == 1) {
        book.show(0);
      } else if (processed.size() == 2) {
        auto tmp = getInfo(processed[1]);
        book.show(tmp.first, tmp.second);
      }
    }
  } else if (opt == "buy") {
    if (processed.size() != 3 || current_level < 1 || processed[1].size() > 20) {
      throw std::exception();
    }
    auto price = book.buy(processed[1], stringtoInt(processed[2]));
    double spend=stringtoInt(processed[2])*1.0 * price;
    if(stringtoInt(processed[2])==0) {
      throw std::exception();
    }
    std::cout<<std::setprecision(2)<<std::fixed<<spend<<'\n';
    log.cashier(spend);
  } else if (opt == "select") {
    if (processed.size() != 2 || processed[1].size() > 20 || current_level < 3) {
      throw std::exception();
    }
    user.select(processed[1]);
    book.create(processed[1]);
  } else if (opt == "modify") {
    if (processed.size() == 1 || current_level < 3) {
      throw std::exception();
    }
    auto tmp = refreshInfo(processed);
    if(tmp.keyword[0]!=0) {
      parser(string(tmp.keyword));
    }
    auto old=user.getB();
    if(old.empty()) {
      throw std::exception();
    }
    book.modify(tmp, old);
    if(tmp.ISBN[0]!=0) {
      user.deep_select(string(tmp.ISBN),old);
    }
  } else if (opt == "import") {
    if (processed.size() != 3 || current_level < 3) {
      throw std::exception();
    }
    book.import(user.getB(), stringtoInt(processed[1]));
    log.cashier(-stringtoReal(processed[2]));
  } else {
    throw std::exception();
  }
}

int main() {
  Book book;
  Log log;
  bool flag=0;
  if (access("user_storage_dir.txt", F_OK) != 0) {
    flag=1;
  }
  User user;
  if(flag) {
    user.useradd("root","sjtu",7,"root",1);
  }
  while (true) {
    try {
      std::string input;
      getline(std::cin, input);
      if (input.empty())
        exit(0);
      processLine(input, user, log, book);
      // std::cout<<user.getP();
    } catch (std::exception &ex) {
      std::cout << "Invalid\n";
    }
  }
}